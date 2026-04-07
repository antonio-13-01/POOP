#include "RailBookApp.h"

RailBookApp& RailBookApp::getInstance()
{
	static RailBookApp instance;
	return instance;
}

DatabaseManager& RailBookApp::getDatabaseManager()
{
	return _dbManager;	
}

inline Logger& RailBookApp::getLogger()
{
	return _logger; 
}

std::vector<ITrain*> RailBookApp::getTrains() const
{
	return _trains;
}

std::vector<Route*> RailBookApp::getRoutes() const
{
	return _routes;
}

