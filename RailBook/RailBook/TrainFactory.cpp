#include "TrainFactory.h"
#include "DatabaseManager.h"
#include "Regio.h"
#include "InterRegio.h"
#include "InterCity.h"
#include <vector>

ITrain::TrainType TrainFactory::stringToTrainType(const std::string& typeStr)
{
	if (typeStr == "Regio") {
        return ITrain::TrainType::Regio;
    }
    else if(typeStr == "InterRegio") {
        return ITrain::TrainType::InterRegio;
    }
    else if(typeStr == "InterCity") {
        return ITrain::TrainType::InterCity;
    }
    else {
        throw std::invalid_argument("Invalid train type string: " + typeStr);
    }
}

ITrain::TrainStatus TrainFactory::stringToTrainStatus(const std::string& statusStr)
{
	if (statusStr == "Activ") {
        return ITrain::TrainStatus::Activ;
    }
    else if(statusStr == "Anulat") {
        return ITrain::TrainStatus::Anulat;
    }
    else {
        throw std::invalid_argument("Invalid train status string: " + statusStr);
    }
}

Wagon::WagonType TrainFactory::stringToWagonType(const std::string& typeStr)
{
    // Acum verificăm exact string-urile din scriptul SQL
    if (typeStr == "Clasa I") {
        return Wagon::WagonType::Clasa1; // Mapăm la enum-ul tău
    }
    else if (typeStr == "Clasa a II-a") {
        return Wagon::WagonType::Clasa2; // Mapăm la enum-ul tău
    }
    else if (typeStr == "Cuseta") {
        return Wagon::WagonType::Cuseta;
    }
    else {
        throw std::invalid_argument("Invalid wagon type string: " + typeStr);
    }
}

ITrain* TrainFactory::LoadTrainFromDB(int id) {

    auto& db = DatabaseManager::getInstance();

    // 1. Definim variabilele în care vom stoca datele
    std::string number;
    int route_id;
    std::string type_str;
    std::string status_str;
    int nr_wagons;
    float fare;

    {
        auto stmt = nanodbc::statement(db.getConnection(),
            "SELECT train_number, route_id, train_type, train_status, number_of_wagons, price_multiplier FROM Train WHERE train_id = ?");
        stmt.bind(0, &id);

        auto result = nanodbc::execute(stmt);
        if (result.next()) {
            number = result.get<std::string>(0);
            route_id = result.get<int>(1);
            type_str = result.get<std::string>(2);
            status_str = result.get<std::string>(3);
            nr_wagons = result.get<int>(4);
            fare = result.get<float>(5);
        }
        else {
            return nullptr; // Trenul nu există
        }
    } 

    ITrain::TrainType type = stringToTrainType(type_str);
    ITrain::TrainStatus status = stringToTrainStatus(status_str);

    ITrain* train = nullptr;
    if (type == ITrain::TrainType::Regio)
        train = new Regio(id, number, route_id, type, status, nr_wagons, fare);
    else if (type == ITrain::TrainType::InterRegio)
        train = new InterRegio(id, number, route_id, type, status, nr_wagons, fare);
    else
        train = new InterCity(id, number, route_id, type, status, nr_wagons, fare);

    LoadWagons(id, train);
    return train;
}

void TrainFactory::LoadWagons(int train_id, ITrain* train) {
    auto& db = DatabaseManager::getInstance();

    nanodbc::statement stmt(db.getConnection());
    nanodbc::prepare(stmt, "SELECT wagon_id, wagon_number, capacity, wagon_type FROM Wagon WHERE train_id = ?");
    stmt.bind(0, &train_id);
    auto result = nanodbc::execute(stmt);

    struct WagonTemp { int id, nr, cap; std::string type; };
    std::vector<WagonTemp> wagonsData;

    while (result.next()) {
        wagonsData.push_back({
            result.get<int>(0),
            result.get<int>(1),
            result.get<int>(2),
            result.get<std::string>(3)
            });
    }

    for (const auto& w : wagonsData) {
        Wagon::WagonType type = stringToWagonType(w.type);
        Wagon* newWagon = new Wagon(w.id, w.nr, w.cap, type, train_id);

        LoadSeats(w.id, newWagon);
        train->addWagon(newWagon);
    }
}

void TrainFactory::LoadSeats(int wagon_id, Wagon* wagon) {
    auto& db = DatabaseManager::getInstance();

    nanodbc::statement stmt(db.getConnection());
    nanodbc::prepare(stmt, "SELECT seat_id, seat_number, seat_fare FROM Seat WHERE wagon_id = ?");
    stmt.bind(0, &wagon_id);

    auto result = nanodbc::execute(stmt);

    while (result.next()) {
        int s_id = result.get<int>(0);
        int s_nr = result.get<int>(1);
        float s_fare = result.get<float>(2);

        Seat* newSeat = new Seat(s_id, s_nr, s_fare, wagon_id);
        wagon->addSeat(newSeat);

    }
}

std::vector<int> TrainFactory::GetAllTrainIds() {
    auto& db = DatabaseManager::getInstance();
    auto result = db.executeQuery("SELECT train_id FROM Train");

    std::vector<int> ids;
    while (result.next()) {
        ids.push_back(result.get<int>(0));
    }
    return ids;
}
