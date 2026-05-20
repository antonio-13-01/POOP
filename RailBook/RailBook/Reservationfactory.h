#pragma once
#include <string>
#include <vector>
#include "DatabaseManager.h"
#include "Client.h"
#include "Exceptions.h"

struct ReservationResult {
    bool success;
    int ticket_id;       // -1 daca a esuat
    float fare_paid;     // pretul final platit
    std::string message; // mesaj de eroare sau succes
};

struct TicketInfo {
    int ticket_id;
    int seat_id;
    int begin_stop_info_id;
    int end_stop_info_id;
    float fare;
    std::string status;
    std::string journey_date;
};

class ReservationFactory {
public:

    static int bookSeat(
        int users_id,
        int seat_id,
        int begin_stop_info_id,
        int end_stop_info_id,
        float base_fare,          // tariful de baza (din Seat.seat_fare * distanta)
        const std::string& journey_date,  // format "YYYY-MM-DD"
        Client::ClientType clientType     // pentru calcul reducere
    );

    static bool cancelTicket(int ticket_id, int users_id);
    static int cancelTrainAndRefundAll(int train_id, float compensatie_extra);
    static bool isSeatAvailable(int seat_id, const std::string& journey_date);
    static float calculateFinalFare(float base_fare, Client::ClientType clientType);
    static float getUserCredit(int users_id);
    static std::vector<TicketInfo> getUserTickets(int users_id);

private:
    
    static bool updateUserCredit(int users_id, float new_credit, nanodbc::connection& conn);
    static int insertTicket(int users_id, int seat_id,
        int begin_stop_info_id, int end_stop_info_id,
        float fare, const std::string& journey_date,
        nanodbc::connection& conn);
};