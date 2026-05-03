#include "RailBookApp.h"

RailBookApp& RailBookApp::getInstance()
{
	static RailBookApp instance;
	return instance;
}

void RailBookApp::initialize(const std::string& dbConnection_string)
{
	getDatabaseManager().connect(dbConnection_string);

	std::vector<int> ids = TrainFactory::GetAllTrainIds();

	for (int id : ids) {
		auto train = TrainFactory::LoadTrainFromDB(id);
		if (train != nullptr) {
			_trains.push_back(train);
		}
		else {
			getLogger().log("Eroare la incarcarea trenului cu ID: " + std::to_string(id));
		}
	}

	getLogger().log("Aplicatia a fost initializata. Trenuri incarcate: " + std::to_string(_trains.size()));

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

std::string RailBookApp::trainTypeToString(ITrain::TrainType type) const
{
	if (type == ITrain::TrainType::Regio) {
		return "Regio";
	}
	else if(type == ITrain::TrainType::InterRegio) {
		return "InterRegio";
	}
	else if(type == ITrain::TrainType::InterCity) {
		return "InterCity";
	}
	else {
		return "Unknown";
	}
}

std::string RailBookApp::trainStatusToString(ITrain::TrainStatus status) const
{
	if (status == ITrain::TrainStatus::Activ) {
		return "Activ";
	}
	else if(status == ITrain::TrainStatus::Anulat) {
		return "Anulat";
	}
	else {
		return "Unknown";
	}
}

std::string RailBookApp::wagonTypeToString(Wagon::WagonType type) const
{
	if (type == Wagon::WagonType::Clasa1) {
		return "Clasa 1";
	}
	else if(type == Wagon::WagonType::Clasa2) {
		return "Clasa 2";
	}
	else if(type == Wagon::WagonType::Cuseta) {
		return "Cuseta";
	}
	else {
		return "Unknown";
	}
}

void RailBookApp::displayTrains() const
{
	std::cout << "DEBUG: In displayTrains(), dimensiune vector: " << _trains.size() << std::endl;
	if (_trains.empty()) {
		std::cout << "\n[INFO] Nu exista trenuri incarcate in sistem." << std::endl;
		return;
	}

	std::cout << "\n========================================" << std::endl;
	std::cout << "      SISTEM RAILBOOK - TRENURI" << std::endl;
	std::cout << "========================================" << std::endl;

	for (const auto* train : _trains) {
		// Aici se apeleaza automat displayInfo() din ATrain prin polimorfism
		train->displayInfo();

		// Putem adauga si conversiile de tip string pe care le aveai deja in RailBookApp
		std::cout << "Tip: " << trainTypeToString(train->getType())
			<< " | Status: " << trainStatusToString(train->getStatus()) << std::endl;
	}

	std::cout << "========================================\n" << std::endl;
}

std::vector<Route*> RailBookApp::getRoutes() const
{
	return _routes;
}

