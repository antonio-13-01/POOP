#include "RailBookApp.h"

RailBookApp& RailBookApp::getInstance()
{
	static RailBookApp instance;
	return instance;
}

void RailBookApp::initialize(const std::string& dbConnection_string)
{
	getDatabaseManager().connect(dbConnection_string);

	loadStationsFromDB();

	_routes = RouteFactory::LoadAllRoutes();
	getLogger().log("Rute incarcate: " + std::to_string(_routes.size()));

	linkStopsWithStations();

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


void RailBookApp::loadStationsFromDB() {
	auto& db = DatabaseManager::getInstance();
	// Folosim numele corecte de coloane conform imaginii image_913.png
	auto result = db.executeQuery("SELECT station_id, station_name, station_city, station_county FROM Station");

	int count = 0;
	while (result.next()) {
		_allStations.push_back(new Station(
			result.get<int>(0),           // station_id
			result.get<std::string>(1),    // station_name
			result.get<std::string>(2),    // station_city
			result.get<std::string>(3)     // station_county
		));
		count++;
	}
	std::cout << "[DEBUG] Am incarcat " << count << " statii din baza de date." << std::endl;
}
void RailBookApp::linkStopsWithStations() {
	for (auto* route : _routes) {
		for (auto* stop : route->getStops()) {
			int idCautat = stop->getStationId();

			for (auto* s : _allStations) {
				// Forțăm compararea directă
				if (s->getId() == idCautat) {
					stop->setStation(s);
					break;
				}
			}
		}
	}
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

		std::cout << "   -> Detalii: " << train->getWagons().size() << " vagoane." << std::endl;
	}

	std::cout << "========================================\n" << std::endl;
}

void RailBookApp::displayRoutes() const {
	std::cout << "\n========== LISTA RUTE DISPONIBILE ==========" << std::endl;
	if (_routes.empty()) {
		std::cout << "Nu exista rute incarcate." << std::endl;
		return;
	}

	for (const auto* route : _routes) {
		route->displayRoute(); 
		std::cout << "--------------------------------------------" << std::endl;
	}
}

std::vector<Route*> RailBookApp::getRoutes() const
{
	return _routes;
}

Route* RailBookApp::getRouteById(int routeId) const {
	for (auto* r : _routes) {
		if (r->getId() == routeId) return r;
	}
	return nullptr;
}

