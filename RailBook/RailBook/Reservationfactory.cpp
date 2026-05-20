#include "ReservationFactory.h"
#include "Logger.h"
#include <stdexcept>
#include <sstream>

// Adult    ->  0% reducere
// Student  -> 50% reducere
// Elev     -> 50% reducere
// Pensionar-> 33% reducere
float ReservationFactory::calculateFinalFare(float base_fare, Client::ClientType clientType)
{
    switch (clientType) {
    case Client::ClientType::Student:
        return base_fare * 0.50f;
    case Client::ClientType::Elev:
        return base_fare * 0.50f;
    case Client::ClientType::Pensionar:
        return base_fare * 0.67f;
    case Client::ClientType::Adult:
    default:
        return base_fare;
    }
}

//  Un loc e disponibil daca NU exista niciun bilet cu
//  ticket_status != 'Anulat' pentru acea zi.
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
        "SELECT client_credit FROM Users WHERE users_id = ?");
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
        "UPDATE Users SET client_credit = ? WHERE users_id = ?");
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
        "INSERT INTO Ticket (users_id, seat_id, begin_stop_info_id, end_stop_info_id, "
        "                    fare, ticket_status, journey_date) "
        "VALUES (?, ?, ?, ?, ?, 'Activ', ?) ; "
        "SELECT SCOPE_IDENTITY();");

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

ReservationResult ReservationFactory::bookSeat(
    int users_id,
    int seat_id,
    int begin_stop_info_id,
    int end_stop_info_id,
    float base_fare,
    const std::string& journey_date,
    Client::ClientType clientType)
{
    ReservationResult res;
    res.success = false;
    res.ticket_id = -1;
    res.fare_paid = 0.0f;

    //verifica disponibilitatea locului
    if (!isSeatAvailable(seat_id, journey_date)) {
        res.message = "Locul nu este disponibil pentru data selectata.";
        Logger::getInstance().log("[REZERVARE] Loc " + std::to_string(seat_id) +
            " indisponibil pentru " + journey_date);
        return res;
    }

    //calculeaza pretul final cu reducere
    float final_fare = calculateFinalFare(base_fare, clientType);
    res.fare_paid = final_fare;

    //verifica creditul utilizatorului
    float credit = 0.0f;
    try {
        credit = getUserCredit(users_id);
    }
    catch (const std::exception& e) {
        res.message = e.what();
        return res;
    }

    if (credit < final_fare) {
        res.message = "Credit insuficient. Necesar: " + std::to_string(final_fare) +
            " RON, disponibil: " + std::to_string(credit) + " RON.";
        Logger::getInstance().log("[REZERVARE] Credit insuficient pentru user " +
            std::to_string(users_id));
        return res;
    }

    //scade creditul + insereaza biletul
    auto& conn = DatabaseManager::getInstance().getConnection();

    try {
        nanodbc::just_execute(conn, "BEGIN TRANSACTION");

        float new_credit = credit - final_fare;
        if (!updateUserCredit(users_id, new_credit, conn)) {
            nanodbc::just_execute(conn, "ROLLBACK");
            res.message = "Eroare la actualizarea creditului.";
            return res;
        }

        int ticket_id = insertTicket(users_id, seat_id,
            begin_stop_info_id, end_stop_info_id,
            final_fare, journey_date, conn);

        if (ticket_id == -1) {
            nanodbc::just_execute(conn, "ROLLBACK");
            res.message = "Eroare la inserarea biletului. Tranzactie anulata.";
            Logger::getInstance().log("[REZERVARE] ROLLBACK — inserare bilet esuata pentru user " +
                std::to_string(users_id));
            return res;
        }

        nanodbc::just_execute(conn, "COMMIT");

        res.success = true;
        res.ticket_id = ticket_id;
        res.message = "Rezervare reusita! Bilet ID: " + std::to_string(ticket_id) +
            " | Pret platit: " + std::to_string(final_fare) + " RON";

        Logger::getInstance().log("[REZERVARE] Bilet " + std::to_string(ticket_id) +
            " creat pentru user " + std::to_string(users_id) +
            " | Loc " + std::to_string(seat_id) +
            " | Pret: " + std::to_string(final_fare) + " RON");

    }
    catch (const std::exception& e) {
        try { nanodbc::just_execute(conn, "ROLLBACK"); }
        catch (...) {}
        res.message = std::string("Eroare tranzactie: ") + e.what();
        Logger::getInstance().log("[REZERVARE] ROLLBACK exceptie: " + std::string(e.what()));
    }

    return res;
}

//anulare bilet
bool ReservationFactory::cancelTicket(int ticket_id, int users_id)
{
    auto& conn = DatabaseManager::getInstance().getConnection();

    try {
        //verifica ca biletul apartine userului si e activ
        nanodbc::statement checkStmt(conn);
        nanodbc::prepare(checkStmt,
            "SELECT fare FROM Ticket "
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

        nanodbc::just_execute(conn, "BEGIN TRANSACTION");

        //marcheaza biletul ca anulat
        nanodbc::statement cancelStmt(conn);
        nanodbc::prepare(cancelStmt,
            "UPDATE Ticket SET ticket_status = 'Anulat' WHERE ticket_id = ?");
        cancelStmt.bind(0, &ticket_id);
        nanodbc::execute(cancelStmt);

        //restituie creditul
        float current_credit = getUserCredit(users_id);
        updateUserCredit(users_id, current_credit + fare, conn);

        nanodbc::just_execute(conn, "COMMIT");

        Logger::getInstance().log("[ANULARE] Bilet " + std::to_string(ticket_id) +
            " anulat. Credit restituit: " + std::to_string(fare) + " RON -> user " +
            std::to_string(users_id));
        return true;
    }
    catch (const std::exception& e) {
        try { nanodbc::just_execute(conn, "ROLLBACK"); }
        catch (...) {}
        Logger::getInstance().log("[ANULARE] Eroare: " + std::string(e.what()));
        return false;
    }
}

//anulare tren + restituire pasagerilor afectati + compensatie extra
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
            //anuleaza biletul
            nanodbc::statement cancelStmt(conn);
            nanodbc::prepare(cancelStmt,
                "UPDATE Ticket SET ticket_status = 'Anulat' WHERE ticket_id = ?");
            int tid = tr.ticket_id;
            cancelStmt.bind(0, &tid);
            nanodbc::execute(cancelStmt);

            //restituie fare + compensatie
            float current = getUserCredit(tr.users_id);
            float refund = tr.fare + compensatie_extra;
            updateUserCredit(tr.users_id, current + refund, conn);

            Logger::getInstance().log("[ANULARE TREN] Bilet " + std::to_string(tr.ticket_id) +
                " anulat | User " + std::to_string(tr.users_id) +
                " | Restituit: " + std::to_string(refund) + " RON");
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

    nanodbc::statement stmt(db.getConnection());
    nanodbc::prepare(stmt,
        "SELECT ticket_id, seat_id, begin_stop_info_id, end_stop_info_id, "
        "       fare, ticket_status, CONVERT(varchar, journey_date, 23) "
        "FROM Ticket "
        "WHERE users_id = ? "
        "ORDER BY journey_date DESC");
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
        tickets.push_back(t);
    }
    return tickets;
}