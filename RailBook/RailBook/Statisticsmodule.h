#pragma once
#include "DatabaseManager.h"
#include "nanodbc.h"
#include <string>
#include <vector>
#include <iostream>


struct RouteOccupancyReport {
    int route_id;
    std::string route_name;
    int total_seats;
    int reserved_seats;
    float occupancy_percent;
};

struct CancellationReport {
    int train_id;
    std::string train_number;
    std::string route_name;
    int total_tickets;
    int cancelled_tickets;
    float cancellation_rate_percent;
};

struct HistoricalTrendEntry {
    std::string month;   // "YYYY-MM"
    int reservations;
    int cancellations;
    float revenue;
};

class StatisticsModule
{
public:
    static std::vector<RouteOccupancyReport> getRouteOccupancy()
    {
        auto& db = DatabaseManager::getInstance();
        std::vector<RouteOccupancyReport> reports;

        try {
            // Total locuri per ruta si locuri rezervate (bilete active)
            auto result = db.executeQuery(
                "SELECT r.route_id, r.route_name, "
                "       COUNT(DISTINCT s.seat_id) AS total_seats, "
                "       SUM(CASE WHEN t.ticket_status = 'Activ' THEN 1 ELSE 0 END) AS reserved_seats "
                "FROM Route r "
                "JOIN Train tr  ON tr.route_id = r.route_id AND tr.train_status = 'Activ' "
                "JOIN Wagon w   ON w.train_id  = tr.train_id "
                "JOIN Seat  s   ON s.wagon_id  = w.wagon_id "
                "LEFT JOIN Ticket t ON t.seat_id = s.seat_id AND t.ticket_status = 'Activ' "
                "GROUP BY r.route_id, r.route_name "
                "ORDER BY r.route_name"
            );

            while (result.next()) {
                RouteOccupancyReport rep;
                rep.route_id = result.get<int>(0);
                rep.route_name = result.get<std::string>(1);
                rep.total_seats = result.get<int>(2);
                rep.reserved_seats = result.is_null(3) ? 0 : result.get<int>(3);
                rep.occupancy_percent = (rep.total_seats > 0)
                    ? (float)rep.reserved_seats / rep.total_seats * 100.0f
                    : 0.0f;
                reports.push_back(rep);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "[STATISTICI] Eroare grad ocupare: " << e.what() << std::endl;
        }
        return reports;
    }

    static std::vector<CancellationReport> getCancellationFrequency()
    {
        auto& db = DatabaseManager::getInstance();
        std::vector<CancellationReport> reports;

        try {
            auto result = db.executeQuery(
                "SELECT tr.train_id, tr.train_number, r.route_name, "
                "       COUNT(t.ticket_id) AS total_tickets, "
                "       SUM(CASE WHEN t.ticket_status = 'Anulat' THEN 1 ELSE 0 END) AS cancelled "
                "FROM Train tr "
                "JOIN Route r ON r.route_id = tr.route_id "
                "LEFT JOIN Wagon w  ON w.train_id  = tr.train_id "
                "LEFT JOIN Seat  s  ON s.wagon_id  = w.wagon_id "
                "LEFT JOIN Ticket t ON t.seat_id   = s.seat_id "
                "GROUP BY tr.train_id, tr.train_number, r.route_name "
                "HAVING COUNT(t.ticket_id) > 0 "
                "ORDER BY cancelled DESC"
            );

            while (result.next()) {
                CancellationReport rep;
                rep.train_id = result.get<int>(0);
                rep.train_number = result.get<std::string>(1);
                rep.route_name = result.get<std::string>(2);
                rep.total_tickets = result.get<int>(3);
                rep.cancelled_tickets = result.is_null(4) ? 0 : result.get<int>(4);
                rep.cancellation_rate_percent = (rep.total_tickets > 0)
                    ? (float)rep.cancelled_tickets / rep.total_tickets * 100.0f
                    : 0.0f;
                reports.push_back(rep);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "[STATISTICI] Eroare frecventa anulari: " << e.what() << std::endl;
        }
        return reports;
    }

    static std::vector<HistoricalTrendEntry> getHistoricalTrends(int lastNMonths = 12)
    {
        auto& db = DatabaseManager::getInstance();
        std::vector<HistoricalTrendEntry> trends;

        try {
            nanodbc::statement stmt(db.getConnection());
            nanodbc::prepare(stmt,
                "SELECT FORMAT(journey_date, 'yyyy-MM') AS luna, "
                "       COUNT(*) AS total_rezervari, "
                "       SUM(CASE WHEN ticket_status = 'Anulat' THEN 1 ELSE 0 END) AS anulari, "
                "       SUM(CASE WHEN ticket_status = 'Activ'  THEN fare ELSE 0 END) AS venituri "
                "FROM Ticket "
                "WHERE journey_date >= DATEADD(MONTH, ?, GETDATE()) "
                "GROUP BY FORMAT(journey_date, 'yyyy-MM') "
                "ORDER BY luna ASC"
            );

            int negMonths = -lastNMonths;
            stmt.bind(0, &negMonths);
            auto result = nanodbc::execute(stmt);

            while (result.next()) {
                HistoricalTrendEntry entry;
                entry.month = result.get<std::string>(0);
                entry.reservations = result.get<int>(1);
                entry.cancellations = result.is_null(2) ? 0 : result.get<int>(2);
                entry.revenue = result.is_null(3) ? 0.0f : result.get<float>(3);
                trends.push_back(entry);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "[STATISTICI] Eroare tendinte istorice: " << e.what() << std::endl;
        }
        return trends;
    }

    static void displayOccupancyReport()
    {
        auto reports = getRouteOccupancy();
        std::cout << "========== GRAD OCUPARE PER RUTA ==========" << std::endl;
        if (reports.empty()) {
            std::cout << "[INFO] Nu exista date disponibile." << std::endl;
        }
        for (const auto& r : reports) {
            std::cout << "Ruta: " << r.route_name
                << " | Total locuri: " << r.total_seats
                << " | Rezervate: " << r.reserved_seats
                << " | Ocupare: " << r.occupancy_percent << "%" << std::endl;
        }
        std::cout << "===========================================" << std::endl;
    }

    static void displayCancellationReport()
    {
        auto reports = getCancellationFrequency();
        std::cout << "========== FRECVENTA ANULARI PER TREN ==========" << std::endl;
        if (reports.empty()) {
            std::cout << "[INFO] Nu exista date disponibile." << std::endl;
        }
        for (const auto& r : reports) {
            std::cout << "Tren: " << r.train_number
                << " (" << r.route_name << ")"
                << " | Total bilete: " << r.total_tickets
                << " | Anulate: " << r.cancelled_tickets
                << " | Rata anulare: " << r.cancellation_rate_percent << "%" << std::endl;
        }
        std::cout << "=================================================" << std::endl;
    }

    static void displayHistoricalTrends(int lastNMonths = 12)
    {
        auto trends = getHistoricalTrends(lastNMonths);
        std::cout << "========== TENDINTE ISTORICE (ultimele "
            << lastNMonths << " luni) ==========" << std::endl;
        if (trends.empty()) {
            std::cout << "[INFO] Nu exista date disponibile." << std::endl;
        }
        for (const auto& t : trends) {
            std::cout << "Luna: " << t.month
                << " | Rezervari: " << t.reservations
                << " | Anulari: " << t.cancellations
                << " | Venituri: " << t.revenue << " RON" << std::endl;
        }
        std::cout << "==========================================" << std::endl;
    }
};