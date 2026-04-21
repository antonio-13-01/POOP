#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "DatabaseManager.h"
#include "Logger.h"
#include "ITrain.h"
#include "Route.h"
#include "IUser.h"
class RailBookApp
{
private:
	std::vector<ITrain*> _trains;
	std::vector<Route*> _routes;
	std::vector<IUser*>_user;
	
public:
	static RailBookApp& getInstance();

	DatabaseManager& getDatabaseManager();
	Logger& getLogger();
	std::vector<ITrain*> getTrains() const;
	std::vector<Route*> getRoutes() const;

private:
	RailBookApp() = default;
	~RailBookApp() = default;
	RailBookApp(const RailBookApp&) = delete;
	RailBookApp& operator=(const RailBookApp&) = delete;	
};

