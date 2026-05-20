#include "RailBookApp.h"
#include <algorithm>

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

DatabaseManager& RailBookApp::getDatabaseManager()
{
	return DatabaseManager::getInstance();
}

Logger& RailBookApp::getLogger()
{
	return Logger::getInstance();
}


void RailBookApp::loadStationsFromDB() {
	auto& db = getDatabaseManager();

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
bool RailBookApp::createRoute(const std::string& route_name, int direction)
{
	try {
		auto& db = getDatabaseManager();
		nanodbc::statement stmt(db.getConnection());

		// Inserăm și apoi interogăm identitatea creată
		nanodbc::prepare(stmt,
			"INSERT INTO Route (route_name, route_direction) VALUES (?, ?); "
			"SELECT CAST(SCOPE_IDENTITY() AS INT);");

		stmt.bind(0, route_name.c_str());
		stmt.bind(1, &direction);

		auto result = nanodbc::execute(stmt);
		if (result.next()) {
			return result.get<int>(0); // Returnează ID-ul real din DB
		}
	}
	catch (const std::exception& e) {
		getLogger().log("[EROARE] Creare ruta: " + std::string(e.what()));
	}
	return -1; // Eroare
}
bool RailBookApp::deleteRoute(int route_id)
{
	auto& db = getDatabaseManager();

	// Verificăm dacă există rezervări active
	nanodbc::statement checkStmt(db.getConnection());
	nanodbc::prepare(checkStmt,
		"SELECT COUNT(*) FROM Ticket t "
		"JOIN Seat s ON t.seat_id = s.seat_id "
		"JOIN Wagon w ON s.wagon_id = w.wagon_id "
		"WHERE w.train_id = ? AND t.ticket_status = 'Activ'");

	checkStmt.bind(0, &route_id);
	auto result = nanodbc::execute(checkStmt);

	if (result.next() && result.get<int>(0) > 0) {
		return false;
	}

	// FIX: Folosim 'Anulat' (care este permis în baza de date) în loc de 'Inactiv'
	nanodbc::statement updateStmt(db.getConnection());
	nanodbc::prepare(updateStmt, "UPDATE Train SET train_status = 'Anulat' WHERE train_id = ?");
	updateStmt.bind(0, &route_id);
	nanodbc::execute(updateStmt);

	return true;
}



std::vector<ITrain*> RailBookApp::getTrains() const
{
	return _trains;
}
float RailBookApp::calculateFare(ITrain* train, int startStationId, int endStationId) {
	Route* route = getRouteById(train->getRouteId());
	if (!route) return 0.0f;

	// Folosim durata în loc de distanță
	int duration = route->getTravelDuration(startStationId, endStationId);

	// Prețul = minute * prețul pe minut (stocat în train->getFarePerKm())
	return (float)duration * train->getFarePerKm();
}
std::vector<std::vector<ITrain*>> RailBookApp::searchItineraries(int startStationId, int endStationId, int maxTransfers) {
	std::vector<std::vector<ITrain*>> validPaths;
	std::vector<ITrain*> currentPath;
	std::set<int> visitedStations;

	visitedStations.insert(startStationId);
	backtrackPaths(startStationId, endStationId, currentPath, visitedStations, validPaths, maxTransfers);

	std::sort(validPaths.begin(), validPaths.end(), [](const std::vector<ITrain*>& a, const std::vector<ITrain*>& b) {
		return a.size() < b.size();
		});

	std::vector<std::vector<ITrain*>> uniqueRoutePaths;
	std::set<std::string> seenRouteCombinations;

	for (const auto& path : validPaths) {
		std::string routeCombo = "";
		for (const auto* train : path) {
			routeCombo += std::to_string(train->getRouteId()) + "-";
		}
		if (seenRouteCombinations.find(routeCombo) == seenRouteCombinations.end()) {
			seenRouteCombinations.insert(routeCombo);
			uniqueRoutePaths.push_back(path);
		}
	}
	return uniqueRoutePaths;
}

void RailBookApp::backtrackPaths(int currentStation, int destinationStation, std::vector<ITrain*>& currentPath, std::set<int>& visitedStations, std::vector<std::vector<ITrain*>>& validPaths, int maxTransfers)
{
	if (currentStation == destinationStation) {
		validPaths.push_back(currentPath);
		return;
	}

	for (auto* train : _trains) {
		if (train->getStatus() != ITrain::TrainStatus::Activ) continue;
		if (std::find(currentPath.begin(), currentPath.end(), train) != currentPath.end()) continue;

		if (!currentPath.empty() && currentPath.back()->getRouteId() == train->getRouteId()) continue;

		Route* route = getRouteById(train->getRouteId());
		if (!route) continue;

		auto stops = route->getStops();
		int startIndex = -1;
		int destIndex = -1;

		for (size_t i = 0; i < stops.size(); ++i) {
			if (stops[i]->getStationId() == currentStation) startIndex = static_cast<int>(i);
			if (stops[i]->getStationId() == destinationStation) destIndex = static_cast<int>(i);
		}

		if (startIndex == -1) continue;

		if (destIndex != -1 && destIndex > startIndex) {
			currentPath.push_back(train);
			validPaths.push_back(currentPath);
			currentPath.pop_back();
			continue;
		}

		if (currentPath.size() >= maxTransfers) continue;

		for (size_t i = startIndex + 1; i < stops.size(); ++i) {
			int nextStation = stops[i]->getStationId();
			if (visitedStations.find(nextStation) == visitedStations.end()) {
				visitedStations.insert(nextStation);
				currentPath.push_back(train);
				backtrackPaths(nextStation, destinationStation, currentPath, visitedStations, validPaths, maxTransfers);
				currentPath.pop_back();
				visitedStations.erase(nextStation);
			}
		}
	}
}

std::vector<std::pair<int, float>> RailBookApp::cancelTrainAndGetRefunds(int trainId)
{
	auto& db = getDatabaseManager();
	std::vector<std::pair<int, float>> refunds;

	try {
		auto txn = db.beginTransaction();

		// 1. Schimbăm statusul trenului
		nanodbc::statement updateTrain(db.getConnection());
		nanodbc::prepare(updateTrain, "UPDATE Train SET train_status = 'Anulat' WHERE train_id = ?");
		updateTrain.bind(0, &trainId);
		nanodbc::execute(updateTrain);

		// 2. Selectăm utilizatorii și prețul pentru biletele active ale acelui tren
		std::string selectQuery =
			"SELECT users_id, fare FROM Ticket "
			"WHERE ticket_status = 'Activ' "
			"AND seat_id IN (SELECT seat_id FROM Seat WHERE wagon_id IN (SELECT wagon_id FROM Wagon WHERE train_id = ?))";

		nanodbc::statement selectTickets(db.getConnection());
		nanodbc::prepare(selectTickets, selectQuery);
		selectTickets.bind(0, &trainId);
		auto result = nanodbc::execute(selectTickets);

		while (result.next()) {
			refunds.push_back({ result.get<int>(0), result.get<float>(1) });
		}

		// 3. Anulăm biletele
		std::string updateTicketsQuery =
			"UPDATE Ticket SET ticket_status = 'Anulat' "
			"WHERE ticket_status = 'Activ' "
			"AND seat_id IN (SELECT seat_id FROM Seat WHERE wagon_id IN (SELECT wagon_id FROM Wagon WHERE train_id = ?))";

		nanodbc::statement updateTickets(db.getConnection());
		nanodbc::prepare(updateTickets, updateTicketsQuery);
		updateTickets.bind(0, &trainId);
		nanodbc::execute(updateTickets);

		txn.commit();
		std::cout << "[SUCCES] Trenul " << trainId << " a fost anulat." << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "[EROARE ANULARE] " << e.what() << std::endl;
	}
	return refunds;
}

bool RailBookApp::addTrain(const std::string& number, int route_id, ITrain::TrainType type, int nr_vagoane, float tarif)
{
	try {
		auto& db = getDatabaseManager();
		nanodbc::statement stmt(db.getConnection());

		// Inserare si recuperare ID
		nanodbc::prepare(stmt,
			"INSERT INTO Train (train_number, route_id, train_type, train_status, number_of_wagons, fare_per_km) "
			"VALUES (?, ?, ?, 'Activ', ?, ?); "
			"SELECT CAST(SCOPE_IDENTITY() AS INT);");

		stmt.bind(0, number.c_str());
		stmt.bind(1, &route_id);
		int tType = (int)type; stmt.bind(2, &tType);
		stmt.bind(3, &nr_vagoane);
		stmt.bind(4, &tarif);

		auto result = nanodbc::execute(stmt);
		if (result.next()) {
			return result.get<int>(0); // Returnează ID-ul real creat de DB
		}
	}
	catch (const std::exception& e) {
		getLogger().log("[EROARE] Adaugare tren esuata: " + std::string(e.what()));
	}
	return -1;
}

bool RailBookApp::deactivateTrain(int train_id)
{
	auto& db = getDatabaseManager();

	// Verificăm dacă există rezervări active pentru acest tren 
	nanodbc::statement checkStmt(db.getConnection());
	nanodbc::prepare(checkStmt,
		"SELECT COUNT(*) FROM Ticket t "
		"JOIN Seat s ON t.seat_id = s.seat_id "
		"JOIN Wagon w ON s.wagon_id = w.wagon_id "
		"WHERE w.train_id = ? AND t.ticket_status = 'Activ'");

	checkStmt.bind(0, &train_id);
	auto result = nanodbc::execute(checkStmt);

	if (result.next() && result.get<int>(0) > 0) {
		getLogger().log("[OPERATOR] EROARE: Trenul " + std::to_string(train_id) + " are rezervari active!");
		return false; // Nu permitem operațiunea
	}

	// Dacă nu are rezervări, putem dezactiva
	nanodbc::statement updateStmt(db.getConnection());
	nanodbc::prepare(updateStmt, "UPDATE Train SET train_status = 'Inactiv' WHERE train_id = ?");
	updateStmt.bind(0, &train_id);
	nanodbc::execute(updateStmt);

	return true;
}

float RailBookApp::getCurrentUserCredit() const
{
	IUser* user = SessionManager::getInstance().getCurrentUser();
	if (!user) throw std::runtime_error("Eroare: Nu exista un utilizator conectat.");

	return ReservationFactory::getUserCredit(user->getId());
}

int RailBookApp::bookSeat(int seat_id, int begin_stop_info_id, int end_stop_info_id, float base_fare, const std::string& journey_date, Client::ClientType clientType)
{
	IUser* user = SessionManager::getInstance().getCurrentUser();
	if (!user) throw std::runtime_error("Eroare: Nu exista un utilizator conectat pentru a face rezervarea.");

	return ReservationFactory::bookSeat(user->getId(), seat_id, begin_stop_info_id, end_stop_info_id, base_fare, journey_date, clientType);
}

bool RailBookApp::cancelTicket(int ticket_id)
{
	IUser* user = SessionManager::getInstance().getCurrentUser();
	if (!user) throw std::runtime_error("Eroare: Nu exista un utilizator conectat.");

	return ReservationFactory::cancelTicket(ticket_id, user->getId());
}

std::vector<TicketInfo> RailBookApp::getCurrentUserTickets() const
{
	IUser* user = SessionManager::getInstance().getCurrentUser();
	if (!user) return {}; // Returnam o lista goala daca nu e logat

	return ReservationFactory::getUserTickets(user->getId());
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

		// Verificăm notificările pentru acest user
		// Căutăm în log-uri orice conține "[ANULARE TREN]" și ID-ul userului
		std::string user_id_str = std::to_string(user->getId());
		auto notificari = Logger::getInstance().getLogsFor(user_id_str);

		if (!notificari.empty()) {
			std::cout << "\n[NOTIFICARE] Ai mesaje noi de la sistem!" << std::endl;
			// Aici vei afișa notificările în frontend (sau în consolă, momentan)
		}

		return true;
	}
	return false;
}

void RailBookApp::userLogout()
{
	SessionManager::getInstance().logout();
	getLogger().log("Utilizator deconectat.");
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

