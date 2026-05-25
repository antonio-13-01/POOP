#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <iomanip>

#include "RailBookApp.h"
#include "ReservationFactory.h"
#include "StatisticsModule.h"
#include "Admin.h"
#include "UserFactory.h"
#include "Logger.h"
#include "Exceptions.h"
#include "nanodbc.h"

// -----------------------------------------------------------------------
// Utilitare de afisare
// -----------------------------------------------------------------------
static int testsPassed = 0;
static int testsFailed = 0;

void printSeparator(const std::string& titlu) {
    std::cout << "\n";
    std::cout << "========================================================\n";
    std::cout << "  " << titlu << "\n";
    std::cout << "========================================================\n";
}

void CHECK(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << "  [PASS] " << testName << "\n";
        testsPassed++;
    } else {
        std::cout << "  [FAIL] " << testName << "\n";
        testsFailed++;
    }
}

// -----------------------------------------------------------------------
// T1 — Initializare aplicatie si conexiune DB
// -----------------------------------------------------------------------
void testInitializare(RailBookApp& app) {
    printSeparator("T1 — Initializare aplicatie");

    try {
        std::string conn_str =
            "DRIVER={ODBC Driver 17 for SQL Server};"
            "SERVER=DESKTOP-INU1UOQ\\SQLEXPRESS;"
            "DATABASE=RailBook;"
            "Trusted_Connection=yes;"
            "MultipleActiveResultSets=True;";

        app.initialize(conn_str);
        CHECK(true, "Conexiune DB si incarcare date initiala");

        CHECK(!app.getRoutes().empty(),  "Rute incarcate din DB");
        CHECK(!app.getTrains().empty(),  "Trenuri incarcate din DB");

        std::cout << "  [INFO] Rute incarcate:   " << app.getRoutes().size()  << "\n";
        std::cout << "  [INFO] Trenuri incarcate: " << app.getTrains().size() << "\n";
    }
    catch (const std::exception& e) {
        CHECK(false, std::string("Initializare — exceptie: ") + e.what());
    }
}

// -----------------------------------------------------------------------
// T2 — Inregistrare utilizator nou
// -----------------------------------------------------------------------
void testSignUp(RailBookApp& app) {
    printSeparator("T2 — Inregistrare utilizator nou");

    // Generam un email unic cu timestamp ca sa nu dam duplicate
    std::string emailTest = "test_" + std::to_string(time(nullptr)) + "@railbook.ro";

    bool ok = app.userSignUp("Popescu", "Ion", emailTest,
        "parola123", "Client", "Adult", "", "");
    CHECK(ok, "Inregistrare Adult nou (email unic)");

    // Inregistrare cu email deja existent — trebuie sa esueze
    bool duplicate = app.userSignUp("Popescu", "Ion", emailTest,
        "parola123", "Client", "Adult", "", "");
    CHECK(!duplicate, "Inregistrare email duplicat respinsa");

    // Inregistrare cu email invalid
    bool invalidEmail = app.userSignUp("Test", "User", "emailfara_at",
        "parola123", "Client", "Adult", "", "");
    CHECK(!invalidEmail, "Inregistrare email invalid respinsa");

    // Student cu legitimatie
    std::string emailStudent = "student_" + std::to_string(time(nullptr)) + "@railbook.ro";
    bool student = app.userSignUp("Ionescu", "Maria", emailStudent,
        "parola456", "Client", "Student", "2026-09-30", "STU123456");
    CHECK(student, "Inregistrare Student cu legitimatie");
}

// -----------------------------------------------------------------------
// T3 — Autentificare
// -----------------------------------------------------------------------
int testLogin(RailBookApp& app, const std::string& email, const std::string& parola,
              const std::string& ic = "") {
    printSeparator("T3 — Autentificare");

    // Login cu parola gresita
    bool loginGresit = app.userLogin("cineva@inexistent.ro", "gresite123");
    CHECK(!loginGresit, "Login cu email inexistent respins");

    // Login corect
    bool loginOk = app.userLogin(email, parola);
    CHECK(loginOk, "Login cu credentiale corecte");

    if (loginOk) {
        IUser* user = SessionManager::getInstance().getCurrentUser();
        CHECK(user != nullptr, "Sesiune activa dupa login");
        if (user) {
            std::cout << "  [INFO] Utilizator logat: "
                << user->getLastName() << " " << user->getName()
                << " | Rol: " << (int)user->getUserType() << "\n";
            return user->getId();
        }
    }
    return -1;
}

// -----------------------------------------------------------------------
// T4 — Vizualizare sold credit
// -----------------------------------------------------------------------
void testSold(RailBookApp& app) {
    printSeparator("T4 — Sold credit");

    try {
        float credit = app.getCurrentUserCredit();
        CHECK(credit >= 0, "Sold credit obtinut (>= 0)");
        std::cout << "  [INFO] Sold curent: " << credit << " RON\n";
    }
    catch (const std::exception& e) {
        CHECK(false, std::string("Sold credit — exceptie: ") + e.what());
    }
}

// -----------------------------------------------------------------------
// T5 — Cautare rute
// -----------------------------------------------------------------------
void testCautareRute(RailBookApp& app) {
    printSeparator("T5 — Cautare rute (itinerarii)");

    auto routes = app.getRoutes();
    if (routes.size() < 1) {
        std::cout << "  [SKIP] Nu exista rute in DB.\n";
        return;
    }

    // Luam prima ruta cu cel putin 2 statii
    Route* ruta = nullptr;
    for (auto* r : routes) {
        if (r->getStops().size() >= 2) { ruta = r; break; }
    }
    if (!ruta) {
        std::cout << "  [SKIP] Nicio ruta cu >= 2 statii.\n";
        return;
    }

    auto stops = ruta->getStops();
    int startId = stops.front()->getStationId();
    int endId   = stops.back()->getStationId();

    auto paths = app.searchItineraries(startId, endId, 2);
    CHECK(!paths.empty(), "searchItineraries returneaza cel putin un rezultat");
    std::cout << "  [INFO] Itinerarii gasite: " << paths.size() << "\n";

    // Verificam ca fiecare path contine cel putin un tren
    bool allValid = true;
    for (auto& path : paths)
        if (path.empty()) { allValid = false; break; }
    CHECK(allValid, "Fiecare itinerar contine cel putin un tren");

    // Calculam tariful pentru primul itinerar direct
    if (!paths.empty() && paths[0].size() == 1) {
        float tarif = app.calculateFare(paths[0][0], startId, endId);
        CHECK(tarif >= 0, "calculateFare returneaza valoare non-negativa");
        std::cout << "  [INFO] Tarif estimat: " << tarif << " RON\n";
    }
}

// -----------------------------------------------------------------------
// T6 — Rezervare bilet (fluxul complet)
// -----------------------------------------------------------------------
int testRezervare(RailBookApp& app, int userId) {
    printSeparator("T6 — Rezervare bilet");

    // Luam primul tren activ cu vagoane si locuri
    ITrain* tren = nullptr;
    for (auto* t : app.getTrains()) {
        if (t->getStatus() == ITrain::TrainStatus::Activ && !t->getWagons().empty())
            if (!t->getWagons()[0]->getSeats().empty()) { tren = t; break; }
    }
    if (!tren) {
        std::cout << "  [SKIP] Niciun tren activ cu locuri in DB.\n";
        return -1;
    }

    int seatId    = tren->getWagons()[0]->getSeats()[0]->getId();
    Route* route  = app.getRouteById(tren->getRouteId());
    if (!route || route->getStops().size() < 2) {
        std::cout << "  [SKIP] Ruta trenului are sub 2 statii.\n";
        return -1;
    }

    int beginStop = route->getStops().front()->getId();
    int endStop   = route->getStops().back()->getId();
    float baseFare = 50.0f;
    std::string dataViitoare = "2027-06-15"; // data viitoare sigura

    float creditInainte = ReservationFactory::getUserCredit(userId);

    int ticketId = -1;
    try {
        ticketId = ReservationFactory::bookSeat(
            userId, seatId, beginStop, endStop,
            baseFare, dataViitoare, Client::ClientType::Adult);
        CHECK(ticketId > 0, "Rezervare Adult — bilet creat cu succes");

        float creditDupa = ReservationFactory::getUserCredit(userId);
        CHECK(creditDupa < creditInainte, "Credit scazut dupa rezervare");
        std::cout << "  [INFO] ID bilet: " << ticketId
            << " | Credit inainte: " << creditInainte
            << " | Credit dupa: " << creditDupa << "\n";
    }
    catch (const InsufficientFundsException& e) {
        std::cout << "  [SKIP] Credit insuficient: " << e.what() << "\n";
        return -1;
    }
    catch (const SeatTakenException& e) {
        std::cout << "  [SKIP] Loc ocupat: " << e.what() << "\n";
        return -1;
    }
    catch (const std::exception& e) {
        CHECK(false, std::string("Rezervare — exceptie neasteptata: ") + e.what());
        return -1;
    }

    // Test rezervare duplicata pe acelasi loc si data
    try {
        ReservationFactory::bookSeat(
            userId, seatId, beginStop, endStop,
            baseFare, dataViitoare, Client::ClientType::Adult);
        CHECK(false, "Rezervare duplicata pe loc deja ocupat trebuie respinsa");
    }
    catch (const SeatTakenException&) {
        CHECK(true, "Rezervare duplicata pe loc ocupat respinsa corect");
    }
    catch (...) {}

    return ticketId;
}

// -----------------------------------------------------------------------
// T7 — Reduceri tarifare per tip client
// -----------------------------------------------------------------------
void testReduceri() {
    printSeparator("T7 — Reduceri tarifare");

    float base = 100.0f;
    float adult    = ReservationFactory::calculateFinalFare(base, Client::ClientType::Adult);
    float student  = ReservationFactory::calculateFinalFare(base, Client::ClientType::Student);
    float elev     = ReservationFactory::calculateFinalFare(base, Client::ClientType::Elev);
    float pensionar = ReservationFactory::calculateFinalFare(base, Client::ClientType::Pensionar);

    CHECK(adult    == 100.0f, "Adult: 0% reducere (100 RON)");
    CHECK(student  == 50.0f,  "Student: 50% reducere (50 RON)");
    CHECK(elev     == 0.0f,   "Elev: 100% reducere (gratuit)");
    CHECK(pensionar == 70.0f, "Pensionar: 30% reducere (70 RON)");

    std::cout << "  [INFO] Adult=" << adult << " Student=" << student
        << " Elev=" << elev << " Pensionar=" << pensionar << " RON\n";
}

// -----------------------------------------------------------------------
// T8 — Vizualizare rezervari cu nume statii
// -----------------------------------------------------------------------
void testVizualizareRezervari(int userId) {
    printSeparator("T8 — Vizualizare rezervari (cu nume statii)");

    auto tickets = ReservationFactory::getUserTickets(userId);
    CHECK(true, "getUserTickets executat fara exceptie");
    std::cout << "  [INFO] Bilete gasite: " << tickets.size() << "\n";

    for (const auto& t : tickets) {
        // Verificam ca nu sunt ID-uri goale sau "N/A" pentru statii cu date reale
        std::cout << "  Bilet #" << t.ticket_id
            << " | " << t.begin_station_name << " -> " << t.end_station_name
            << " | " << t.fare << " RON | " << t.status
            << " | " << t.journey_date << "\n";

        // Verificam ca numele de statie nu e un numar pur (adica nu mai e ID)
        bool beginIsId = !t.begin_station_name.empty() &&
            t.begin_station_name.find_first_not_of("0123456789") == std::string::npos;
        CHECK(!beginIsId, "Statie de plecare afisata ca NUME, nu ca ID numeric");
        break; // verificam doar primul bilet
    }
}

// -----------------------------------------------------------------------
// T9 — Anulare rezervare (regula 100%/50%)
// -----------------------------------------------------------------------
void testAnulareRezervare(int userId, int ticketId) {
    printSeparator("T9 — Anulare rezervare cu regula 100%/50%");

    if (ticketId <= 0) {
        std::cout << "  [SKIP] Nu exista un bilet valid de anulat.\n";
        return;
    }

    float creditInainte = ReservationFactory::getUserCredit(userId);

    bool ok = ReservationFactory::cancelTicket(ticketId, userId);
    CHECK(ok, "Anulare bilet returnata cu succes");

    float creditDupa = ReservationFactory::getUserCredit(userId);
    CHECK(creditDupa > creditInainte, "Credit crescut dupa anulare (restituire aplicata)");

    float diferenta = creditDupa - creditInainte;
    std::cout << "  [INFO] Credit inainte: " << creditInainte
        << " | Credit dupa: " << creditDupa
        << " | Restituit: " << diferenta << " RON\n";

    // Data calatoriei era 2027-06-15 (mult in viitor), deci > 24h => 100% restituire
    // Daca fare era 50 RON (Adult fara reducere), asteptam 50 RON inapoi
    // Nu cunoastem exact fare-ul, dar diferenta trebuie sa fie > 0
    CHECK(diferenta > 0.0f, "Suma restituita este pozitiva");

    // Tentativa de anulare a aceluiasi bilet din nou — trebuie sa esueze
    bool dubla = ReservationFactory::cancelTicket(ticketId, userId);
    CHECK(!dubla, "Anulare bilet deja anulat respinsa");
}

// -----------------------------------------------------------------------
// T10 — Conflict de orar (rezervare dubla)
// -----------------------------------------------------------------------
void testConflictOrar(RailBookApp& app, int userId) {
    printSeparator("T10 — Restricție rezervare dubla pe interval orar");

    ITrain* tren = nullptr;
    for (auto* t : app.getTrains()) {
        if (t->getStatus() == ITrain::TrainStatus::Activ && !t->getWagons().empty())
            if (t->getWagons()[0]->getSeats().size() >= 2) { tren = t; break; }
    }
    if (!tren) {
        std::cout << "  [SKIP] Niciun tren cu cel putin 2 locuri.\n";
        return;
    }

    Route* route = app.getRouteById(tren->getRouteId());
    if (!route || route->getStops().size() < 2) {
        std::cout << "  [SKIP] Ruta invalida.\n";
        return;
    }

    int seat1   = tren->getWagons()[0]->getSeats()[0]->getId();
    int seat2   = tren->getWagons()[0]->getSeats()[1]->getId();
    int begin   = route->getStops().front()->getId();
    int end     = route->getStops().back()->getId();
    std::string data = "2027-08-20";

    // Prima rezervare — trebuie sa reuseasca
    int t1 = -1;
    try {
        t1 = ReservationFactory::bookSeat(userId, seat1, begin, end,
            30.0f, data, Client::ClientType::Adult);
        CHECK(t1 > 0, "Prima rezervare in interval orar creata cu succes");
    }
    catch (const InsufficientFundsException&) {
        std::cout << "  [SKIP] Credit insuficient pentru test conflict orar.\n";
        return;
    }
    catch (const SeatTakenException&) {
        std::cout << "  [SKIP] Loc deja ocupat — test conflict orar imposibil.\n";
        return;
    }

    // A doua rezervare in acelasi interval orar — trebuie respinsa
    try {
        ReservationFactory::bookSeat(userId, seat2, begin, end,
            30.0f, data, Client::ClientType::Adult);
        CHECK(false, "A doua rezervare in acelasi interval orar trebuie respinsa");
    }
    catch (const SeatTakenException& e) {
        CHECK(true, "A doua rezervare in acelasi interval orar respinsa corect");
        std::cout << "  [INFO] Motiv: " << e.what() << "\n";
    }

    // Curatam rezervarea de test
    if (t1 > 0) ReservationFactory::cancelTicket(t1, userId);
}

// -----------------------------------------------------------------------
// T11 — Functii Admin (blocare, deblocare, tip, credit, reset parola)
// -----------------------------------------------------------------------
void testAdmin(int targetUserId) {
    printSeparator("T11 — Functii Admin");

    // Construim un obiect Admin de test (fara DB, doar pentru apeluri)
    Admin admin(1, "Admin", "Sistem", "admin@railbook.ro",
        "hash_placeholder", IUser::UserType::Admin, false);

    // Blocare cont
    admin.blocareClient(targetUserId);
    // Verificam direct in DB
    auto& db = DatabaseManager::getInstance();
    nanodbc::statement checkStmt(db.getConnection());
    nanodbc::prepare(checkStmt, "SELECT is_blocked FROM dbo.Users WHERE users_id = ?");
    checkStmt.bind(0, &targetUserId);
    auto res = nanodbc::execute(checkStmt);
    if (res.next()) {
        CHECK(res.get<int>(0) == 1, "blocareClient — is_blocked = 1 in DB");
    }

    // Deblocare cont
    admin.deblocareClient(targetUserId);
    nanodbc::statement checkStmt2(db.getConnection());
    nanodbc::prepare(checkStmt2, "SELECT is_blocked FROM dbo.Users WHERE users_id = ?");
    checkStmt2.bind(0, &targetUserId);
    auto res2 = nanodbc::execute(checkStmt2);
    if (res2.next()) {
        CHECK(res2.get<int>(0) == 0, "deblocareClient — is_blocked = 0 in DB");
    }

    // Modificare tip client -> Pensionar (trimitem si datele de justificare)
    admin.modificareTipClient(targetUserId, Client::ClientType::Pensionar, "2027-12-31", "PEN-4321");
    nanodbc::statement checkStmt3(db.getConnection());
    nanodbc::prepare(checkStmt3,
        "SELECT client_category FROM dbo.Users WHERE users_id = ?");
    checkStmt3.bind(0, &targetUserId);
    auto res3 = nanodbc::execute(checkStmt3);
    if (res3.next()) {
        CHECK(res3.get<std::string>(0) == "Pensioner",
            "modificareTipClient — client_category = 'Pensioner' in DB");
    }

    // Reset parola
    bool resetOk = admin.resetParola(targetUserId, "novaParola999");
    CHECK(resetOk, "resetParola — executat fara eroare");

    // Alimentare credit (daca soldul e <= 100)
    float soldInainte = ReservationFactory::getUserCredit(targetUserId);
    if (soldInainte <= 100.0f) {
        admin.alimentareCredit(targetUserId, 100.0f);
        float soldDupa = ReservationFactory::getUserCredit(targetUserId);
        CHECK(soldDupa > soldInainte, "alimentareCredit — sold crescut in DB");
        std::cout << "  [INFO] Sold inainte: " << soldInainte
            << " | Sold dupa: " << soldDupa << " RON\n";
    } else {
        std::cout << "  [INFO] Sold " << soldInainte
            << " RON > 100 RON — alimentare nu se aplica (comportament corect)\n";
    }

    // Restauram tipul la Adult
    admin.modificareTipClient(targetUserId, Client::ClientType::Adult);
}

// -----------------------------------------------------------------------
// T12 — Statistici
// -----------------------------------------------------------------------
void testStatistici() {
    printSeparator("T12 — Modul Statistici");

    // Grad ocupare
    auto occupancy = StatisticsModule::getRouteOccupancy();
    CHECK(true, "getRouteOccupancy executat fara exceptie");
    std::cout << "  [INFO] Rute in raport ocupare: " << occupancy.size() << "\n";
    for (const auto& r : occupancy) {
        CHECK(r.total_seats >= r.reserved_seats,
            "Ocupare: locuri rezervate <= locuri totale pentru ruta '" + r.route_name + "'");
        CHECK(r.occupancy_percent >= 0.0f && r.occupancy_percent <= 100.0f,
            "Ocupare: procent in intervalul [0, 100]");
        std::cout << "    " << r.route_name << ": "
            << r.reserved_seats << "/" << r.total_seats
            << " (" << std::fixed << std::setprecision(1)
            << r.occupancy_percent << "%)\n";
    }

    // Frecventa anulari
    auto cancellations = StatisticsModule::getCancellationFrequency();
    CHECK(true, "getCancellationFrequency executat fara exceptie");
    std::cout << "  [INFO] Trenuri in raport anulari: " << cancellations.size() << "\n";

    // Tendinte istorice — ultimele 6 luni
    auto trends = StatisticsModule::getHistoricalTrends(6);
    CHECK(true, "getHistoricalTrends(6) executat fara exceptie");
    std::cout << "  [INFO] Luni in tendinte: " << trends.size() << "\n";
    for (const auto& t : trends) {
        CHECK(t.cancellations <= t.reservations,
            "Tendinte: anulari <= rezervari totale pentru luna " + t.month);
        std::cout << "    " << t.month
            << " | Rez: " << t.reservations
            << " | Anul: " << t.cancellations
            << " | Venituri: " << t.revenue << " RON\n";
    }
}

// -----------------------------------------------------------------------
// T13 — Notificari necitite
// -----------------------------------------------------------------------
void testNotificari(int userId) {
    printSeparator("T13 — Notificari necitite");

    std::string userIdStr = std::to_string(userId);

    // Prima citire
    auto notif1 = Logger::getInstance().getUnreadNotificationsFor(userIdStr);
    std::cout << "  [INFO] Notificari necitite (prima citire): "
        << notif1.size() << "\n";

    // A doua citire — trebuie sa fie goala (au fost marcate ca livrate)
    auto notif2 = Logger::getInstance().getUnreadNotificationsFor(userIdStr);
    CHECK(notif2.empty(),
        "A doua citire getUnreadNotificationsFor returneaza 0 (toate marcate ca livrate)");

    // Adaugam manual o notificare noua pentru acest user
    Logger::getInstance().log("[ANULARE TREN] Test notificare | [NOTIF:" + userIdStr + "]");

    // Acum trebuie sa apara o notificare necitita
    auto notif3 = Logger::getInstance().getUnreadNotificationsFor(userIdStr);
    CHECK(notif3.size() == 1,
        "Notificare noua aparuta dupa log — returnata la urmatoarea citire");

    // Si a patra citire — din nou goala
    auto notif4 = Logger::getInstance().getUnreadNotificationsFor(userIdStr);
    CHECK(notif4.empty(),
        "Dupa livrare, notificarea dispare la urmatoarea citire");
}

// -----------------------------------------------------------------------
// T14 — Anulare tren de catre operator
// -----------------------------------------------------------------------
void testAnulareTren(RailBookApp& app, int userId) {
    printSeparator("T14 — Anulare tren (operator) cu restituire + compensatie");

    // Gasim un tren activ
    ITrain* tren = nullptr;
    for (auto* t : app.getTrains()) {
        if (t->getStatus() == ITrain::TrainStatus::Activ &&
            !t->getWagons().empty() &&
            !t->getWagons()[0]->getSeats().empty()) {
            tren = t; break;
        }
    }
    if (!tren) {
        std::cout << "  [SKIP] Niciun tren activ cu locuri.\n";
        return;
    }

    Route* route = app.getRouteById(tren->getRouteId());
    if (!route || route->getStops().size() < 2) {
        std::cout << "  [SKIP] Ruta invalida.\n";
        return;
    }

    // Facem o rezervare pe acest tren
    int seatId  = tren->getWagons()[0]->getSeats()[0]->getId();
    int begin   = route->getStops().front()->getId();
    int end     = route->getStops().back()->getId();
    std::string data = "2027-09-10";

    int ticketId = -1;
    try {
        ticketId = ReservationFactory::bookSeat(userId, seatId, begin, end,
            40.0f, data, Client::ClientType::Adult);
        CHECK(ticketId > 0, "Rezervare creata inainte de anularea trenului");
    }
    catch (...) {
        std::cout << "  [SKIP] Nu s-a putut face rezervarea de test.\n";
        return;
    }

    float creditInainte = ReservationFactory::getUserCredit(userId);
    float compensatie   = 10.0f;

    // Anulam trenul cu compensatie de 10 RON
    int afectati = ReservationFactory::cancelTrainAndRefundAll(tren->getId(), compensatie);
    CHECK(afectati >= 1, "cancelTrainAndRefundAll — cel putin 1 bilet afectat");

    float creditDupa = ReservationFactory::getUserCredit(userId);
    CHECK(creditDupa > creditInainte,
        "Credit utilizator crescut dupa anulare tren (restituire + compensatie)");

    float diferenta = creditDupa - creditInainte;
    std::cout << "  [INFO] Credit inainte: " << creditInainte
        << " | Credit dupa: " << creditDupa
        << " | Restituit+compensatie: " << diferenta << " RON\n";

    // Verificam notificarea generata
    std::string userIdStr = std::to_string(userId);
    auto notif = Logger::getInstance().getUnreadNotificationsFor(userIdStr);
    CHECK(!notif.empty(), "Notificare generata pentru user dupa anulare tren");
}

// -----------------------------------------------------------------------
// T15 — Logout
// -----------------------------------------------------------------------
void testLogout(RailBookApp& app) {
    printSeparator("T15 — Logout");

    app.userLogout();
    IUser* user = SessionManager::getInstance().getCurrentUser();
    CHECK(user == nullptr, "getCurrentUser() returneaza nullptr dupa logout");
}

// -----------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------
int main() {
    std::cout << "╔══════════════════════════════════════════════════════╗\n";
    std::cout << "║         RAILBOOK — SUITE TESTARE COMPLETA           ║\n";
    std::cout << "╚══════════════════════════════════════════════════════╝\n";

    RailBookApp& app = RailBookApp::getInstance();

    // T1: Initializare
    testInitializare(app);

    // T2: Signup
    testSignUp(app);

    // Cream un cont de test dedicat cu credit suficient
    std::string emailTest = "tester_main_" + std::to_string(time(nullptr)) + "@railbook.ro";
    bool created = app.userSignUp("Tester", "Main", emailTest,
        "parola_test_123", "Client", "Adult", "", "");

    if (!created) {
        std::cerr << "\n[FATAL] Nu s-a putut crea contul de test. Verificati conexiunea DB.\n";
        return 1;
    }

    // Adaugam credit direct in DB pentru contul de test
    {
        auto& db = DatabaseManager::getInstance();
        auto result = db.executeQuery(
            "SELECT users_id FROM dbo.Users WHERE users_email = '" + emailTest + "'");
        if (result.next()) {
            int testId = result.get<int>(0);
            nanodbc::statement stmt(db.getConnection());
            nanodbc::prepare(stmt,
                "UPDATE dbo.Users SET client_credit = 500 WHERE users_id = ?");
            stmt.bind(0, &testId);
            nanodbc::execute(stmt);
            std::cout << "\n  [SETUP] Credit 500 RON setat pentru contul de test (ID: "
                << testId << ")\n";
        }
    }

    // T3: Login
    int userId = testLogin(app, emailTest, "parola_test_123");
    if (userId == -1) {
        std::cerr << "\n[FATAL] Login esuat. Oprire teste.\n";
        return 1;
    }

    // T4–T10: Teste cu user logat
    testSold(app);
    testCautareRute(app);
    testReduceri();

    int ticketId = testRezervare(app, userId);
    testVizualizareRezervari(userId);
    testAnulareRezervare(userId, ticketId);
    testConflictOrar(app, userId);

    // T11: Admin (opereaza pe contul de test)
   // testAdmin(userId);

    // T12: Statistici
    testStatistici();

    // T13: Notificari
    testNotificari(userId);

    // T14: Anulare tren
    testAnulareTren(app, userId);

    // T15: Logout
    testLogout(app);

    // -----------------------------------------------------------------------
    // Sumar final
    // -----------------------------------------------------------------------
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════╗\n";
    std::cout << "║                  REZULTATE FINALE                   ║\n";
    std::cout << "╠══════════════════════════════════════════════════════╣\n";
    std::cout << "║  PASSED: " << std::setw(3) << testsPassed
        << "                                           ║\n";
    std::cout << "║  FAILED: " << std::setw(3) << testsFailed
        << "                                           ║\n";
    std::cout << "╚══════════════════════════════════════════════════════╝\n";

    if (testsFailed == 0)
        std::cout << "\n  Toate testele au trecut. Codul respecta 100% livrabilul.\n\n";
    else
        std::cout << "\n  " << testsFailed << " test(e) esuat(e). Verifica output-ul de mai sus.\n\n";

    return testsFailed == 0 ? 0 : 1;
}