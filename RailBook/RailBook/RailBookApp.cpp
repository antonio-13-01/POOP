#include "RailBookApp.h"

RailBookApp& RailBookApp::getInstance()
{
	static RailBookApp instance;
	return instance;
}

DatabaseManager& RailBookApp::getDatabaseManager()
{
	auto& dbManager = DatabaseManager::getInstance();
	return dbManager;
}

Logger& RailBookApp::getLogger()
{
	auto& logger = Logger::getInstance();	
	return logger;
}



std::vector<ITrain*> RailBookApp::getTrains() const
{
	return _trains;
}

std::vector<Route*> RailBookApp::getRoutes() const
{
	return _routes;
}

