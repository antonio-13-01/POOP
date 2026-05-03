#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "DatabaseManager.h"
#include "Logger.h"
#include "ITrain.h"
#include "Route.h"
#include "IUser.h"
#include "TrainFactory.h"
#include "RouteFactory.h"
#include "Station.h"
#include <map>

class RailBookApp
{
private:
	std::vector<ITrain*> _trains;
	std::vector<Route*> _routes;
	std::vector<IUser*>_user;
	std::vector<Station*> _allStations;
	
public:
	static RailBookApp& getInstance();

	void initialize(const std::string& dbConnection_string);
	DatabaseManager& getDatabaseManager();
	Logger& getLogger();	
	
	std::vector<Route*> getRoutes() const;

	//Metode pentru trenuri
	std::vector<ITrain*> getTrains() const;
	std::string trainTypeToString(ITrain::TrainType type) const;
	std::string trainStatusToString(ITrain::TrainStatus status) const;	
	std::string wagonTypeToString(Wagon::WagonType type) const;
	
	//Metode pentru rute
	Route* getRouteById(int routeId)const;
	void loadStationsFromDB();
	void linkStopsWithStations();

	//Metoda vizualizare
	void displayTrains() const;
	void displayRoutes() const;
private:
	RailBookApp() = default;
	~RailBookApp()
	{
		for (ITrain* train : _trains) {
			delete train;

			_trains.clear();
		}
	}
	RailBookApp(const RailBookApp&) = delete;
	RailBookApp& operator=(const RailBookApp&) = delete;	
};

