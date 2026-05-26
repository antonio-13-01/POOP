#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <algorithm>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "RailBookApp.h"
#include "SessionManager.h"
#include "Client.h"
#include "Logger.h"

// ============================================================
//  Sesiuni per socket — fiecare client are propriul IUser*
// ============================================================
std::map<SOCKET, IUser*> activeSessions;
std::mutex sessionMutex;

// ============================================================
//  Utilitare
// ============================================================
std::vector<std::string> splitPacket(const std::string& s, const std::string& delim) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string temp = s;
    size_t found;
    while ((found = temp.find(delim)) != std::string::npos) {
        tokens.push_back(temp.substr(0, found));
        temp = temp.substr(found + delim.size());
    }
    tokens.push_back(temp);
    return tokens;
}

void sendMsg(SOCKET client, const std::string& msg) {
    std::string toSend = msg + "\n";
    send(client, toSend.c_str(), (int)toSend.size(), 0);
}

IUser* getSession(SOCKET sock) {
    std::lock_guard<std::mutex> lock(sessionMutex);
    auto it = activeSessions.find(sock);
    return (it != activeSessions.end()) ? it->second : nullptr;
}

void setSession(SOCKET sock, IUser* user) {
    std::lock_guard<std::mutex> lock(sessionMutex);
    activeSessions[sock] = user;
}

void clearSession(SOCKET sock) {
    std::lock_guard<std::mutex> lock(sessionMutex);
    activeSessions.erase(sock);
}

// ============================================================
//  Normalizare categorie client (Qt trimite in romana/engleza)
// ============================================================
std::string normalizeCategory(const std::string& cat) {
    if (cat == "Adult Standard" || cat == "Adult") return "Adult";
    if (cat == "Student")                           return "Student";
    if (cat == "Elev" || cat == "Pupil")            return "Pupil";
    if (cat == "Pensionar" || cat == "Pensioner")   return "Pensioner";
    return "Adult";
}

Client::ClientType categoryToClientType(const std::string& category) {
    if (category == "Student")  return Client::ClientType::Student;
    if (category == "Pupil")    return Client::ClientType::Elev;
    if (category == "Pensioner")return Client::ClientType::Pensionar;
    return Client::ClientType::Adult;
}

// ============================================================
//  HANDLER PRINCIPAL — proceseaza un pachet primit
// ============================================================
std::string handlePacket(const std::string& packet, SOCKET clientSock, RailBookApp& app) {
    auto parts = splitPacket(packet, "###");
    if (parts.empty() || parts[0].empty()) return "ERR###PACHET_GOL";

    std::string cmd = parts[0];

    // ── LOGIN ──────────────────────────────────────────────
    // Client: LOGIN###email###parola
    // Server: OK_LOGIN###ADMIN/OPERATOR/PASAGER###sold###nr_notificari
    //      sau ERR_LOGIN###Motiv
    if (cmd == "LOGIN") {
        if (parts.size() < 3) return "ERR_LOGIN###Date incomplete";

        std::string email = parts[1];
        std::string password = parts[2];

        auto& db = DatabaseManager::getInstance();
        nanodbc::statement stmt(db.getConnection());
        nanodbc::prepare(stmt,
            "SELECT users_id, users_password, is_blocked "
            "FROM dbo.Users WHERE users_email = ?");
        stmt.bind(0, email.c_str());
        auto result = nanodbc::execute(stmt);

        if (!result.next()) return "ERR_LOGIN###Email sau parola incorecta";

        int id = result.get<int>(0);
        std::string hash = result.get<std::string>(1);
        bool blocked = result.get<int>(2) != 0;

        if (!SecurityUtils::VerifyPassword(password, hash))
            return "ERR_LOGIN###Email sau parola incorecta";

        if (blocked) return "ERR_LOGIN###Contul este blocat";

        IUser* user = UserFactory::LoadUserFromDB(id);
        if (!user) return "ERR_LOGIN###Eroare incarcare utilizator";

        setSession(clientSock, user);

        std::string role = "PASAGER";
        if (user->getUserType() == IUser::UserType::Admin)    role = "ADMIN";
        if (user->getUserType() == IUser::UserType::Operator) role = "OPERATOR";

        float credit = 0.0f;
        try { credit = ReservationFactory::getUserCredit(id); }
        catch (...) {}

        Logger::getInstance().log("[LOGIN] User " + email + " conectat.");

        auto notif = Logger::getInstance().getLogsFor(std::to_string(id));
        std::string notifStr = notif.empty() ? "0" : std::to_string(notif.size());

        return "OK_LOGIN###" + role + "###" + std::to_string(credit) + "###" + notifStr;
    }


    // ── LOGOUT ────────────────────────────────────────────
    if (cmd == "LOGOUT") {
        IUser* user = getSession(clientSock);
        if (user) {
            Logger::getInstance().log("[LOGOUT] User deconectat (socket " + std::to_string(clientSock) + ")");
            delete user;
        }
        clearSession(clientSock);
        return "OK_LOGOUT";
    }

    // ── SIGNUP / REGISTER ─────────────────────────────────
    // Client: REGISTER###Nume###Prenume###email###parola###Categorie###IC
    if (cmd == "SIGNUP" || cmd == "REGISTER") {
        if (parts.size() < 6) return "ERR_SIGNUP###Date incomplete";

        std::string lastName = parts[1];
        std::string firstName = parts[2];
        std::string email = parts[3];
        std::string password = parts[4];
        std::string category = normalizeCategory(parts[5]);
        std::string ic = (parts.size() > 6 && parts[6] != "NONE") ? parts[6] : "";

        // Valabilitate — goala pentru Adult, poate fi completata ulterior
        std::string valability = (parts.size() > 7) ? parts[7] : "";

        bool ok = app.userSignUp(lastName, firstName, email, password,
            "Client", category, valability, ic);
        if (ok) return "OK_SIGNUP";
        return "ERR_SIGNUP###Email deja inregistrat sau date invalide";
    }

    // ── SEARCH_ROUTES / SSEARCH ───────────────────────────
    // Client: SSEARCH###Plecare###Destinatie###Data###ORA sau PRET
    // Server: TRAINS_LIST###nr|tip|HH:MM|HH:MM|pret###...
    if (cmd == "SEARCH_ROUTES" || cmd == "SSEARCH") {
        if (parts.size() < 4) return "ERR_SEARCH###Date incomplete";

        std::string plecare = parts[1];
        std::string destinatie = parts[2];
        std::string sortBy = (parts.size() > 4) ? parts[4] : "ORA";

        // Gasim ID statii dupa nume
        int startId = -1, endId = -1;
        for (auto* route : app.getRoutes()) {
            for (auto* stop : route->getStops()) {
                if (stop->getStation()) {
                    if (stop->getStation()->getName() == plecare)    startId = stop->getStationId();
                    if (stop->getStation()->getName() == destinatie) endId = stop->getStationId();
                }
            }
        }

        if (startId == -1 || endId == -1) return "ERR_SEARCH###Statii negasite";

        auto paths = app.searchItineraries(startId, endId, 2);
        if (paths.empty()) return "TRAINS_LIST###";

        struct TrenResult {
            std::string nr, tip;
            int plecareMins, sosireMins;
            float pret;
            int seat_id; // primul loc disponibil
        };
        std::vector<TrenResult> rezultate;

        auto minsToHHMM = [](int m) -> std::string {
            char buf[6];
            snprintf(buf, sizeof(buf), "%02d:%02d", m / 60, m % 60);
            return std::string(buf);
            };

        for (auto& path : paths) {
            if (path.size() != 1) continue; // doar directe deocamdata
            ITrain* t = path[0];
            Route* route = app.getRouteById(t->getRouteId());
            if (!route) continue;

            int dep = -1, arr = -1;
            for (auto* stop : route->getStops()) {
                if (stop->getStationId() == startId) dep = stop->getDepartureMinutes();
                if (stop->getStationId() == endId)   arr = stop->getArrivalMinutes();
            }
            if (dep == -1 || arr == -1) continue;

            float pret = app.calculateFare(t, startId, endId);

            // Primul seat_id disponibil
            int firstSeat = -1;
            for (auto* w : t->getWagons()) {
                // Seat-urile sunt in wagon — dam primul wagon/seat ca referinta
                firstSeat = w->getId(); // wagon_id ca placeholder
                break;
            }

            rezultate.push_back({ t->getNumber(), app.trainTypeToString(t->getType()),
                                   dep, arr, pret, firstSeat });
        }

        // Sortare
        if (sortBy == "PRET" || sortBy == "1") {
            std::sort(rezultate.begin(), rezultate.end(),
                [](const TrenResult& a, const TrenResult& b) { return a.pret < b.pret; });
        }
        else {
            std::sort(rezultate.begin(), rezultate.end(),
                [](const TrenResult& a, const TrenResult& b) { return a.plecareMins < b.plecareMins; });
        }

        std::string response = "TRAINS_LIST";
        for (auto& r : rezultate) {
            response += "###" + r.nr + "|" + r.tip + "|"
                + minsToHHMM(r.plecareMins) + "|"
                + minsToHHMM(r.sosireMins) + "|"
                + std::to_string(r.pret) + "|"
                + std::to_string(r.seat_id);
        }
        return response;
    }

    // ── BUY_TICKET ────────────────────────────────────────
    // Client: BUY_TICKET###seat_id###begin_stop###end_stop###pret###data###categorie
    // Server: OK_BUY###ticket_id  sau  ERR_BUY###Motiv
    if (cmd == "BUY_TICKET") {
        if (parts.size() < 7) return "ERR_BUY###Date incomplete";

        IUser* user = getSession(clientSock);
        if (!user) return "ERR_BUY###Nu esti autentificat";

        try {
            int seat_id = std::stoi(parts[1]);
            int begin_stop = std::stoi(parts[2]);
            int end_stop = std::stoi(parts[3]);
            float base_fare = std::stof(parts[4]);
            std::string date = parts[5];
            std::string catStr = normalizeCategory(parts[6]);
            Client::ClientType clientType = categoryToClientType(catStr);

            int ticket_id = ReservationFactory::bookSeat(
                user->getId(), seat_id, begin_stop, end_stop,
                base_fare, date, clientType);

            return "OK_BUY###" + std::to_string(ticket_id);
        }
        catch (const SeatTakenException& e) {
            return std::string("ERR_BUY###LOC_OCUPAT###") + e.what();
        }
        catch (const InsufficientFundsException& e) {
            return std::string("ERR_BUY###FONDURI###") + e.what();
        }
        catch (const std::exception& e) {
            return std::string("ERR_BUY###") + e.what();
        }
    }

    // ── CANCEL_TICKET ─────────────────────────────────────
    // Client: CANCEL_TICKET###ticket_id
    // Server: OK_CANCEL  sau  ERR_CANCEL###Motiv
    if (cmd == "CANCEL_TICKET") {
        if (parts.size() < 2) return "ERR_CANCEL###Date incomplete";

        IUser* user = getSession(clientSock);
        if (!user) return "ERR_CANCEL###Nu esti autentificat";

        int ticket_id = std::stoi(parts[1]);
        bool ok = ReservationFactory::cancelTicket(ticket_id, user->getId());
        return ok ? "OK_CANCEL" : "ERR_CANCEL###Bilet invalid sau deja anulat";
    }

    // ── GET_TICKETS ───────────────────────────────────────
    // Client: GET_TICKETS
    // Server: TICKETS_LIST###id|seat|begin|end|fare|status|date###...
    if (cmd == "GET_TICKETS") {
        IUser* user = getSession(clientSock);
        if (!user) return "ERR###Nu esti autentificat";

        auto tickets = ReservationFactory::getUserTickets(user->getId());
        if (tickets.empty()) return "TICKETS_LIST###";

        std::string response = "TICKETS_LIST";
        for (auto& t : tickets) {
            response += "###" + std::to_string(t.ticket_id) + "|"
                + std::to_string(t.seat_id) + "|"
                + std::to_string(t.begin_stop_info_id) + "|"
                + std::to_string(t.end_stop_info_id) + "|"
                + std::to_string(t.fare) + "|"
                + t.status + "|"
                + t.journey_date;
        }
        return response;
    }

    // ── GET_CREDIT ────────────────────────────────────────
    if (cmd == "GET_CREDIT") {
        IUser* user = getSession(clientSock);
        if (!user) return "ERR###Nu esti autentificat";

        float credit = ReservationFactory::getUserCredit(user->getId());
        return "OK_CREDIT###" + std::to_string(credit);
    }

    // ── GET_NOTIFICATIONS ─────────────────────────────────
    if (cmd == "GET_NOTIFICATIONS") {
        IUser* user = getSession(clientSock);
        if (!user) return "ERR###Nu esti autentificat";

        auto notif = Logger::getInstance().getLogsFor(std::to_string(user->getId()));
        if (notif.empty()) return "NOTIF_LIST###";

        std::string response = "NOTIF_LIST";
        for (auto& n : notif) {
            response += "###" + n;
        }
        return response;
    }

    return "ERR###COMANDA_NECUNOSCUTA";
}

// ============================================================
//  CLIENT HANDLER — ruleaza intr-un thread separat
// ============================================================
void handleClient(SOCKET clientSock, RailBookApp& app) {
    char buffer[4096];
    std::cout << "[SERVER] Client conectat: socket " << clientSock << std::endl;

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(clientSock, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) {
            std::cout << "[SERVER] Client deconectat: socket " << clientSock << std::endl;
            break;
        }

        std::string packet(buffer, bytes);
        // Eliminam \n si \r de la sfarsit
        while (!packet.empty() && (packet.back() == '\n' || packet.back() == '\r'))
            packet.pop_back();

        std::cout << "[RECV] " << packet << std::endl;
        std::string response = handlePacket(packet, clientSock, app);
        std::cout << "[SEND] " << response << std::endl;
        sendMsg(clientSock, response);
    }

    // Cleanup sesiune la deconectare
    IUser* user = getSession(clientSock);
    if (user) delete user;
    clearSession(clientSock);
    closesocket(clientSock);
}

// ============================================================
//  BUCLA PRINCIPALA A SERVERULUI
// ============================================================
void runServer(RailBookApp& app, int port) {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock == INVALID_SOCKET) {
        std::cerr << "[SERVER] Eroare creare socket!" << std::endl;
        return;
    }

    // Permite reutilizarea portului rapid dupa restart
    int opt = 1;
    setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(serverSock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "[SERVER] Eroare bind pe portul " << port << std::endl;
        closesocket(serverSock);
        WSACleanup();
        return;
    }

    listen(serverSock, 10);
    std::cout << "[SERVER] RailBook Server pornit pe portul " << port << std::endl;
    std::cout << "[SERVER] Asteapta conexiuni..." << std::endl;

    // Accept loop — cate un thread per client
    while (true) {
        SOCKET clientSock = accept(serverSock, nullptr, nullptr);
        if (clientSock == INVALID_SOCKET) continue;

        // Lansam thread separat pentru fiecare client
        std::thread(handleClient, clientSock, std::ref(app)).detach();
    }

    closesocket(serverSock);
    WSACleanup();
}