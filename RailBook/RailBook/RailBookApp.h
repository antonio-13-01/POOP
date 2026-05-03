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
class RailBookApp
{
private:
	std::vector<ITrain*> _trains;
	std::vector<Route*> _routes;
	std::vector<IUser*>_user;
	
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
	void displayTrains() const;
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

