#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include "DatabaseManager.h"
#include "Logger.h"
#include "ITrain.h"
#include "Route.h"
#include "IUser.h"
#include "UserFactory.h" 
#include "TrainFactory.h"
#include "RouteFactory.h"
#include "Station.h"
#include "SessionManager.h"
#include "Reservationfactory.h"

class RailBookApp {
private:
    std::vector<ITrain*> _trains;
    std::vector<Route*> _routes;
    std::vector<IUser*> _users;    
    std::vector<Station*> _allStations;

public:
    static RailBookApp& getInstance();

    void initialize(const std::string& dbConnection_string);
    DatabaseManager& getDatabaseManager();
    Logger& getLogger();

 
	// Metode de conversie pentru afisare
    std::string trainTypeToString(ITrain::TrainType type) const;
    std::string trainStatusToString(ITrain::TrainStatus status) const;
    std::string wagonTypeToString(Wagon::WagonType type) const;

	//Metode pentru înregistrare
    bool userSignUp(const std::string& lastName, const std::string& firstName,
        const std::string& email, const std::string& password,
        const std::string& role, const std::string& category,
        const std::string& valability, const std::string& ic_number);
	
    //Metode pentru autentificare
    bool userLogin(const std::string& email, const std::string& password);
   
    //Metode pentru deconectare
    void userLogout();

	//Metoda de calculare a tarifului pentru o anumită rută și tren
    float calculateFare(ITrain* train, int startStationId, int endStationId);

   
    //Metode pentru rute
    std::vector<Route*> getRoutes() const;
    Route* getRouteById(int routeId) const;
    void loadStationsFromDB();
    void linkStopsWithStations();
    bool createRoute(const std::string& route_name, int direction);
    bool deleteRoute(int route_id);

    //Metode pentru trenuri
    std::vector<ITrain*> getTrains() const;
    std::vector<std::vector<ITrain*>> searchItineraries(int startStationId, int endStationId, int maxTransfers = 1);
    void backtrackPaths(int currentStation, int destinationStation,
         std::vector<ITrain*>& currentPath,
         std::set<int>& visitedStations,
         std::vector<std::vector<ITrain*>>& validPaths,
         int maxTransfers);
    std::vector<std::pair<int, float>> cancelTrainAndGetRefunds(int trainId);
    bool addTrain(const std::string& number, int route_id, ITrain::TrainType type, int nr_vagoane, float tarif);
    bool deactivateTrain(int train_id);
    
	// Metode pentru utilizatori
    float getCurrentUserCredit() const;
    int bookSeat(int seat_id, int begin_stop_info_id, int end_stop_info_id, float base_fare, const std::string& journey_date, Client::ClientType clientType);
    bool cancelTicket(int ticket_id);
    std::vector<TicketInfo> getCurrentUserTickets() const;

    // Metode de afișare
    void displayTrains() const;
    void displayRoutes() const;
    void displayUsers() const; 

private:
    RailBookApp() = default;
    ~RailBookApp() {
        for (auto* t : _trains) delete t;
        for (auto* r : _routes) delete r;
        for (auto* u : _users)  delete u;  
        for (auto* s : _allStations) delete s;
    }
    RailBookApp(const RailBookApp&) = delete;
    RailBookApp& operator=(const RailBookApp&) = delete;
};