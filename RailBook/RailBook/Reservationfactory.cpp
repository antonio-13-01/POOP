#define _CRT_SECURE_NO_WARNINGS
#include "ReservationFactory.h"
#include "Logger.h"
#include <stdexcept>
#include <sstream>
#include <ctime>

// Adult    ->  0% reducere
// Student  -> 50% reducere
// Elev     -> 100% reducere (gratuit)
// Pensionar-> 30% reducere
float ReservationFactory::calculateFinalFare(float base_fare, Client::ClientType clientType)
{
    switch (clientType) {
    case Client::ClientType::Elev:
        return 0.0f;              // -100%
    case Client::ClientType::Student:
        return base_fare * 0.50f; // -50%
    case Client::ClientType::Pensionar:
        return base_fare * 0.70f; // -30%
    case Client::ClientType::Adult:
    default:
        return base_fare;         // 0% reducere
    }
}

// Un loc e disponibil daca NU exista niciun bilet activ pentru acea zi
bool ReservationFactory::isSeatAvailable(int seat_id, const std::string& journey_date)
{
    auto& db = DatabaseManager::getInstance();

    nanodbc::statement stmt(db.getConnection());
    nanodbc::prepare(stmt,
        "SELECT COUNT(*) FROM Ticket "
        "WHERE seat_id = ? "
        "  AND journey_date = ? "
        "  AND ticket_status <> 'Anulat'");

    stmt.bind(0, &seat_id);
    stmt.bind(1, journey_date.c_str());

    auto result = nanodbc::execute(stmt);
    if (result.next()) {
        return result.get<int>(0) == 0;
    }
    return false;
}

float ReservationFactory::getUserCredit(int users_id)
{
    auto& db = DatabaseManager::getInstance();

    nanodbc::statement stmt(db.getConnection());
    nanodbc::prepare(stmt,
        "SELECT client_credit FROM dbo.Users WHERE users_id = ?");
    stmt.bind(0, &users_id);

    auto result = nanodbc::execute(stmt);
    if (result.next()) {
        return result.get<float>(0);
    }
    throw std::runtime_error("Utilizatorul cu ID " + std::to_string(users_id) + " nu a fost gasit.");
}

bool ReservationFactory::updateUserCredit(int users_id, float new_credit, nanodbc::connection& conn)
{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt,
        "UPDATE dbo.Users SET client_credit = ? WHERE users_id = ?");
    stmt.bind(0, &new_credit);
    stmt.bind(1, &users_id);
    nanodbc::execute(stmt);
    return true;
}

int ReservationFactory::insertTicket(int users_id, int seat_id,
    int begin_stop_info_id, int end_stop_info_id,
    float fare, const std::string& journey_date,
    nanodbc::connection& conn)
{
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt,
        "SET NOCOUNT ON; "
        "INSERT INTO Ticket (users_id, seat_id, begin_stop_info_id, end_stop_info_id, "
        "                    fare, ticket_status, journey_date) "
        "VALUES (?, ?, ?, ?, ?, 'Activ', ?); "
        "SELECT CAST(SCOPE_IDENTITY() AS INT);"
    );

    stmt.bind(0, &users_id);
    stmt.bind(1, &seat_id);
    stmt.bind(2, &begin_stop_info_id);
    stmt.bind(3, &end_stop_info_id);
    stmt.bind(4, &fare);
    stmt.bind(5, journey_date.c_str());

    auto result = nanodbc::execute(stmt);
    if (result.next()) {
        return result.get<int>(0);
    }
    return -1;
}

// -----------------------------------------------------------------------
// FIX #6: verificare rezervare dubla pe interval orar (cerinta 3.4)
// -----------------------------------------------------------------------
bool ReservationFactory::hasConflictingReservation(int users_id, const std::string& journey_date,
    int begin_stop_info_id, int end_stop_info_id)
{
    auto& db = DatabaseManager::getInstance();

    // Obtinem minutele de plecare/sosire ale noii rezervari
    nanodbc::statement stopStmt(db.getConnection());
    nanodbc::prepare(stopStmt,
        "SELECT departure_minutes FROM StopInfo WHERE stop_info_id = ?");
    stopStmt.bind(0, &begin_stop_info_id);
    auto stopRes = nanodbc::execute(stopStmt);
    if (!stopRes.next()) return false;
    int newDep = stopRes.get<int>(0);

    nanodbc::statement arrStmt(db.getConnection());
    nanodbc::prepare(arrStmt,
        "SELECT arrival_minutes FROM StopInfo WHERE stop_info_id = ?");
    arrStmt.bind(0, &end_stop_info_id);
    auto arrRes = nanodbc::execute(arrStmt);
    if (!arrRes.next()) return false;
    int newArr = arrRes.get<int>(0);

    // Cautam rezervari active ale aceluiasi user in aceeasi zi
    nanodbc::statement ticketStmt(db.getConnection());
    nanodbc::prepare(ticketStmt,
        "SELECT t.begin_stop_info_id, t.end_stop_info_id "
        "FROM Ticket t "
        "WHERE t.users_id = ? AND t.journey_date = ? AND t.ticket_status = 'Activ'");
    ticketStmt.bind(0, &users_id);
    ticketStmt.bind(1, journey_date.c_str());
    auto ticketRes = nanodbc::execute(ticketStmt);

    while (ticketRes.next()) {
        int existingBegin = ticketRes.get<int>(0);
        int existingEnd = ticketRes.get<int>(1);

        // Obtinem orele rezervarii existente
        nanodbc::statement exDepStmt(db.getConnection());
        nanodbc::prepare(exDepStmt,
            "SELECT departure_minutes FROM StopInfo WHERE stop_info_id = ?");
        exDepStmt.bind(0, &existingBegin);
        auto exDepRes = nanodbc::execute(exDepStmt);
        if (!exDepRes.next()) continue;
        int exDep = exDepRes.get<int>(0);

        nanodbc::statement exArrStmt(db.getConnection());
        nanodbc::prepare(exArrStmt,
            "SELECT arrival_minutes FROM StopInfo WHERE stop_info_id = ?");
        exArrStmt.bind(0, &existingEnd);
        auto exArrRes = nanodbc::execute(exArrStmt);
        if (!exArrRes.next()) continue;
        int exArr = exArrRes.get<int>(0);

        // Verificam overlap: daca intervalele [exDep, exArr] si [newDep, newArr] se suprapun
        if (newDep < exArr && newArr > exDep) {
            return true; // conflict detectat
        }
    }
    return false;
}

int ReservationFactory::bookSeat(
    int users_id,
    int seat_id,
    int begin_stop_info_id,
    int end_stop_info_id,
    float base_fare,
    const std::string& journey_date,
    Client::ClientType clientType)
{
    // 1. Verifica disponibilitatea locului
    if (!isSeatAvailable(seat_id, journey_date)) {
        Logger::getInstance().log("[REZERVARE] Loc " + std::to_string(seat_id) + " indisponibil.");
        throw SeatTakenException("Locul selectat nu mai este disponibil pentru aceasta data.");
    }

    // 2. FIX #6: Verifica conflict de orar pentru acelasi utilizator
    if (hasConflictingReservation(users_id, journey_date, begin_stop_info_id, end_stop_info_id)) {
        Logger::getInstance().log("[REZERVARE] Conflict orar detectat pentru user " +
            std::to_string(users_id) + " pe data " + journey_date);
        throw SeatTakenException("Ai deja o rezervare activa in acelasi interval orar pentru aceasta data.");
    }

    // 3. Calculeaza pretul final cu reducere
    float final_fare = calculateFinalFare(base_fare, clientType);

    // 4. Verifica creditul utilizatorului
    float credit = 0.0f;
    try {
        credit = getUserCredit(users_id);
    }
    catch (const std::exception& e) {
        throw DatabaseTransactionException(e.what());
    }

    if (credit < final_fare) {
        Logger::getInstance().log("[REZERVARE] Credit insuficient pentru user " + std::to_string(users_id));
        throw InsufficientFundsException("Credit insuficient. Necesar: " + std::to_string(final_fare) +
            " RON, disponibil: " + std::to_string(credit) + " RON.");
    }

    // 5. Scade creditul + insereaza biletul intr-o tranzactie atomica
    auto& conn = DatabaseManager::getInstance().getConnection();

    try {
        nanodbc::just_execute(conn, "BEGIN TRANSACTION");

        float new_credit = credit - final_fare;
        if (!updateUserCredit(users_id, new_credit, conn)) {
            nanodbc::just_execute(conn, "ROLLBACK");
            throw DatabaseTransactionException("Eroare la actualizarea creditului.");
        }

        int ticket_id = insertTicket(users_id, seat_id,
            begin_stop_info_id, end_stop_info_id,
            final_fare, journey_date, conn);

        if (ticket_id == -1) {
            nanodbc::just_execute(conn, "ROLLBACK");
            Logger::getInstance().log("[REZERVARE] ROLLBACK — inserare bilet esuata pentru user " +
                std::to_string(users_id));
            throw DatabaseTransactionException("Eroare la inserarea biletului. Tranzactie anulata.");
        }

        nanodbc::just_execute(conn, "COMMIT");

        Logger::getInstance().log("[REZERVARE] Bilet " + std::to_string(ticket_id) +
            " creat pentru user " + std::to_string(users_id) +
            " | Loc " + std::to_string(seat_id) +
            " | Pret: " + std::to_string(final_fare) + " RON");

        return ticket_id;
    }
    catch (const std::exception& e) {
        try { nanodbc::just_execute(conn, "ROLLBACK"); }
        catch (...) {}
        Logger::getInstance().log("[REZERVARE] ROLLBACK exceptie: " + std::string(e.what()));
        throw DatabaseTransactionException(std::string("Eroare tranzactie: ") + e.what());
    }
}

// -----------------------------------------------------------------------
// FIX #3: cancelTicket — regula 100% daca > 24h, 50% daca <= 24h
// -----------------------------------------------------------------------
bool ReservationFactory::cancelTicket(int ticket_id, int users_id)
{
    auto& conn = DatabaseManager::getInstance().getConnection();

    try {
        // Verifica ca biletul apartine userului, e activ, si ia data calatoriei
        nanodbc::statement checkStmt(conn);
        nanodbc::prepare(checkStmt,
            "SELECT fare, CONVERT(varchar, journey_date, 23), "
            "       begin_stop_info_id "
            "FROM Ticket "
            "WHERE ticket_id = ? AND users_id = ? AND ticket_status = 'Activ'");
        checkStmt.bind(0, &ticket_id);
        checkStmt.bind(1, &users_id);

        auto checkResult = nanodbc::execute(checkStmt);
        if (!checkResult.next()) {
            Logger::getInstance().log("[ANULARE] Bilet " + std::to_string(ticket_id) +
                " nu e activ sau nu apartine userului " + std::to_string(users_id));
            return false;
        }

        float fare = checkResult.get<float>(0);
        std::string dateStr = checkResult.get<std::string>(1); // "YYYY-MM-DD"
        int beginStopId = checkResult.get<int>(2);

        // Obtinem ora de plecare a trenului (in minute de la miezul noptii)
        nanodbc::statement stopStmt(conn);
        nanodbc::prepare(stopStmt,
            "SELECT departure_minutes FROM StopInfo WHERE stop_info_id = ?");
        stopStmt.bind(0, &beginStopId);
        auto stopRes = nanodbc::execute(stopStmt);

        int departureMinutes = 0;
        if (stopRes.next()) {
            departureMinutes = stopRes.get<int>(0);
        }

        // Calculam diferenta in minute intre momentul actual si plecarea trenului
        int an = std::stoi(dateStr.substr(0, 4));
        int luna = std::stoi(dateStr.substr(5, 2));
        int zi = std::stoi(dateStr.substr(8, 2));

        time_t t = time(nullptr);
        tm* acum = localtime(&t);

        // Construim un tm pentru momentul plecarii trenului
        tm departureTm = {};
        departureTm.tm_year = an - 1900;
        departureTm.tm_mon = luna - 1;
        departureTm.tm_mday = zi;
        departureTm.tm_hour = departureMinutes / 60;
        departureTm.tm_min = departureMinutes % 60;
        departureTm.tm_sec = 0;
        departureTm.tm_isdst = -1;

        time_t departureTime = mktime(&departureTm);
        double diffSeconds = difftime(departureTime, t);
        double diffOre = diffSeconds / 3600.0;

        // Regula livrabil: > 24h => 100%, <= 24h => 50%
        float refund;
        std::string motivRefund;
        if (diffOre > 24.0) {
            refund = fare;          // 100%
            motivRefund = "100%";
        }
        else {
            refund = fare * 0.50f;  // 50%
            motivRefund = "50%";
        }

        nanodbc::just_execute(conn, "BEGIN TRANSACTION");

        // Marcheaza biletul ca anulat
        nanodbc::statement cancelStmt(conn);
        nanodbc::prepare(cancelStmt,
            "UPDATE Ticket SET ticket_status = 'Anulat' WHERE ticket_id = ?");
        cancelStmt.bind(0, &ticket_id);
        nanodbc::execute(cancelStmt);

        // Restituie creditul calculat
        float current_credit = getUserCredit(users_id);
        updateUserCredit(users_id, current_credit + refund, conn);

        nanodbc::just_execute(conn, "COMMIT");

        Logger::getInstance().log("[ANULARE] Bilet " + std::to_string(ticket_id) +
            " anulat. Restituire: " + motivRefund +
            " (" + std::to_string(refund) + " RON) -> user " + std::to_string(users_id) +
            " | Ore pana la plecare: " + std::to_string((int)diffOre));
        return true;
    }
    catch (const std::exception& e) {
        try { nanodbc::just_execute(conn, "ROLLBACK"); }
        catch (...) {}
        Logger::getInstance().log("[ANULARE] Eroare: " + std::string(e.what()));
        return false;
    }
}

// Anulare tren + restituire pasagerilor afectati + compensatie extra
int ReservationFactory::cancelTrainAndRefundAll(int train_id, float compensatie_extra)
{
    auto& conn = DatabaseManager::getInstance().getConnection();
    int count = 0;

    try {
        nanodbc::statement findStmt(conn);
        nanodbc::prepare(findStmt,
            "SELECT t.ticket_id, t.users_id, t.fare "
            "FROM Ticket t "
            "JOIN Seat s ON t.seat_id = s.seat_id "
            "JOIN Wagon w ON s.wagon_id = w.wagon_id "
            "WHERE w.train_id = ? AND t.ticket_status = 'Activ'");
        findStmt.bind(0, &train_id);

        auto result = nanodbc::execute(findStmt);

        struct TicketRefund { int ticket_id, users_id; float fare; };
        std::vector<TicketRefund> toRefund;

        while (result.next()) {
            toRefund.push_back({
                result.get<int>(0),
                result.get<int>(1),
                result.get<float>(2)
                });
        }

        if (toRefund.empty()) {
            Logger::getInstance().log("[ANULARE TREN] Trenul " + std::to_string(train_id) +
                " nu are bilete active.");
            return 0;
        }

        nanodbc::just_execute(conn, "BEGIN TRANSACTION");

        nanodbc::statement trainStmt(conn);
        nanodbc::prepare(trainStmt,
            "UPDATE Train SET train_status = 'Anulat' WHERE train_id = ?");
        trainStmt.bind(0, &train_id);
        nanodbc::execute(trainStmt);

        for (const auto& tr : toRefund) {
            nanodbc::statement cancelStmt(conn);
            nanodbc::prepare(cancelStmt,
                "UPDATE Ticket SET ticket_status = 'Anulat' WHERE ticket_id = ?");
            int tid = tr.ticket_id;
            cancelStmt.bind(0, &tid);
            nanodbc::execute(cancelStmt);

            // Restituire 100% + compensatie (anulare de catre operator = full refund)
            float current = getUserCredit(tr.users_id);
            float refund = tr.fare + compensatie_extra;
            updateUserCredit(tr.users_id, current + refund, conn);

            // Logam cu ID-ul userului pentru sistemul de notificari
            Logger::getInstance().log("[ANULARE TREN] Bilet " + std::to_string(tr.ticket_id) +
                " anulat | User " + std::to_string(tr.users_id) +
                " | Restituit: " + std::to_string(refund) + " RON" +
                " | [NOTIF:" + std::to_string(tr.users_id) + "]");
            count++;
        }

        nanodbc::just_execute(conn, "COMMIT");

        Logger::getInstance().log("[ANULARE TREN] Tren " + std::to_string(train_id) +
            " anulat. Total bilete afectate: " + std::to_string(count));
    }
    catch (const std::exception& e) {
        try { nanodbc::just_execute(conn, "ROLLBACK"); }
        catch (...) {}
        Logger::getInstance().log("[ANULARE TREN] Eroare ROLLBACK: " + std::string(e.what()));
        count = -1;
    }

    return count;
}

std::vector<TicketInfo> ReservationFactory::getUserTickets(int users_id)
{
    auto& db = DatabaseManager::getInstance();
    std::vector<TicketInfo> tickets;

    // FIX #5: JOIN cu StopInfo si Station pentru a returna nume statii
    nanodbc::statement stmt(db.getConnection());
    nanodbc::prepare(stmt,
        "SELECT t.ticket_id, t.seat_id, t.begin_stop_info_id, t.end_stop_info_id, "
        "       t.fare, t.ticket_status, CONVERT(varchar, t.journey_date, 23), "
        "       s1.station_name AS begin_station, s2.station_name AS end_station "
        "FROM Ticket t "
        "LEFT JOIN StopInfo si1 ON t.begin_stop_info_id = si1.stop_info_id "
        "LEFT JOIN Station s1  ON si1.station_id = s1.station_id "
        "LEFT JOIN StopInfo si2 ON t.end_stop_info_id = si2.stop_info_id "
        "LEFT JOIN Station s2  ON si2.station_id = s2.station_id "
        "WHERE t.users_id = ? "
        "ORDER BY t.journey_date DESC");
    stmt.bind(0, &users_id);

    auto result = nanodbc::execute(stmt);
    while (result.next()) {
        TicketInfo t;
        t.ticket_id = result.get<int>(0);
        t.seat_id = result.get<int>(1);
        t.begin_stop_info_id = result.get<int>(2);
        t.end_stop_info_id = result.get<int>(3);
        t.fare = result.get<float>(4);
        t.status = result.get<std::string>(5);
        t.journey_date = result.get<std::string>(6);
        t.begin_station_name = result.is_null(7) ? "N/A" : result.get<std::string>(7);
        t.end_station_name = result.is_null(8) ? "N/A" : result.get<std::string>(8);
        tickets.push_back(t);
    }
    return tickets;
}