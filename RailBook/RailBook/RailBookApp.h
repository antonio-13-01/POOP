#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "DatabaseManager.h"
#include "Logger.h"
#include "ITrain.h"
#include "Route.h"
#include "IUser.h"
#include "UserFactory.h" 
#include "TrainFactory.h"
#include "RouteFactory.h"
#include "Station.h"

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

    std::vector<Route*> getRoutes() const;
    std::vector<ITrain*> getTrains() const;

	// Metode de conversie pentru afisare
    std::string trainTypeToString(ITrain::TrainType type) const;
    std::string trainStatusToString(ITrain::TrainStatus status) const;
    std::string wagonTypeToString(Wagon::WagonType type) const;

	//Metode pentru autentificare și înregistrare
    bool userSignUp(const std::string& lastName, const std::string& firstName,
        const std::string& email, const std::string& password,
        const std::string& role, const std::string& category,
        const std::string& valability, const std::string& ic_number);

    bool userLogin(const std::string& email, const std::string& password);

    void userLogout();

    //Metode pentru rute
    Route* getRouteById(int routeId) const;
    void loadStationsFromDB();
    void linkStopsWithStations();

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