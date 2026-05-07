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
	std::vector<int> userIds = UserFactory::GetAllUserIds();
	for (int id : userIds) {
		auto* user = UserFactory::LoadUserFromDB(id);
		if (user) {
			_users.push_back(user);
		}
	}

	getLogger().log("Aplicatia a fost initializata.");

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

bool RailBookApp::userSignUp(const std::string& lastName, const std::string& firstName,
	const std::string& email, const std::string& password,
	const std::string& role, const std::string& category,
	const std::string& valability, const std::string& ic_number)
{
	int success = UserFactory::signUp(lastName, firstName, email, password, role, category, valability, ic_number);

	if (success != -1) {
		IUser* newUser = UserFactory::LoadUserFromDB(success);
		_users.push_back(newUser);
		Logger::getInstance().log("Utilizator nou inregistrat: " + email); 
			return true;
	}
	return false;
}

bool RailBookApp::userLogin(const std::string& email, const std::string& password) {

	if (UserFactory::login(email, password)) {
		
		IUser* user = SessionManager::getInstance().getCurrentUser();
		Logger::getInstance().log("Login reusit pentru: " + user->getEmail());
			return true;
	}
	return false;
}

void RailBookApp::userLogout()
{
}

void RailBookApp::displayTrains() const
{
	if (_trains.empty()) {
		std::cout << "\n[INFO] Nu exista trenuri incarcate in sistem." << std::endl;
		return;
	}

	std::cout << "=============== LISTA TRENURI ===============" << std::endl;

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

void RailBookApp::displayUsers() const {
	
	std::cout << "=========LISTA UTILIZATORI============" << std::endl;

	if (_users.empty()) {
		std::cout << "[INFO] Nu există utilizatori în baza de date." << std::endl;
	}
	else {
		for (const auto* user : _users) {
			user->displayUser();
		}
	}
	std::cout << "==========================================\n" << std::endl;
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

