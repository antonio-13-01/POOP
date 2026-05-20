#include "Client.h"
#include "Logger.h"
#include <iostream>
#include <ctime>

Client::Client(int id, const std::string last_name,
	const std::string name, const std::string email,
	const std::string parolaHash, UserType userType,
	float credit, std::string valability, bool isBlocked)
	: AUser(id, last_name, name, email, parolaHash, userType, isBlocked),
	_credit(credit), _valability(valability), _type(ClientType::Adult)
{}

int Client::getId() const { return _id; }
std::string Client::getLastName() const { return _last_name; }
std::string Client::getName() const { return _name; }
std::string Client::getEmail() const { return _email; }
Client::ClientType Client::getClientType() const { return _type; }
float Client::getCredit() const { return _credit; }
std::string Client::getValability() const { return _valability; }
void Client::setCredit(float credit) { _credit = credit; }
void Client::setClientType(ClientType clientType) { _type = clientType; }

void Client::afisareSold() const
{
	std::cout << "==========================================" << std::endl;
	std::cout << "  Sold curent: " << _credit << " RON" << std::endl;
	std::cout << "==========================================" << std::endl;
}

void Client::afisareDetaliiProfil() const
{
	std::string tipClient;
	switch (_type) {
	case ClientType::Student:   tipClient = "Student";   break;
	case ClientType::Elev:      tipClient = "Elev";      break;
	case ClientType::Pensionar: tipClient = "Pensionar"; break;
	case ClientType::Adult:
	default:                    tipClient = "Adult";     break;
	}

	std::cout << "==========================================" << std::endl;
	std::cout << "           PROFILUL MEU                   " << std::endl;
	std::cout << "==========================================" << std::endl;
	std::cout << "  Nume:         " << _last_name << std::endl;
	std::cout << "  Prenume:      " << _name << std::endl;
	std::cout << "  Email:        " << _email << std::endl;
	std::cout << "  Tip cont:     " << tipClient << std::endl;
	std::cout << "  Credit:       " << _credit << " RON" << std::endl;
	std::cout << "  Valabilitate: " << _valability << std::endl;
	std::cout << "  Stare cont:   " << (_isBlocked ? "BLOCAT" : "Activ") << std::endl;
	std::cout << "==========================================" << std::endl;
}

bool Client::editareProfil(const std::string& newLastName,
	const std::string& newName,
	const std::string& newPassword)
{
	bool modified = false;

	if (!newLastName.empty() && newLastName != _last_name) {
		setLastName(newLastName);
		modified = true;
		Logger::getInstance().log("[PROFIL] Nume modificat pentru " + _email +
			": " + newLastName);
	}

	if (!newName.empty() && newName != _name) {
		setName(newName);
		modified = true;
		Logger::getInstance().log("[PROFIL] Prenume modificat pentru " + _email +
			": " + newName);
	}

	if (!newPassword.empty() && newPassword != _password) {
		setPassword(newPassword);
		modified = true;
		Logger::getInstance().log("[PROFIL] Parola modificata pentru " + _email);
	}

	if (modified)
		std::cout << "[OK] Profilul a fost actualizat." << std::endl;
	else
		std::cout << "[INFO] Nicio modificare efectuata." << std::endl;

	return modified;
}

void Client::vizualizareRezervari() const
{
	try {
		auto& db = DatabaseManager::getInstance();
		nanodbc::statement stmt(db.getConnection());
		nanodbc::prepare(stmt,
			"SELECT ticket_id, seat_id, begin_stop_info_id, end_stop_info_id, "
			"       fare, ticket_status, CONVERT(varchar, journey_date, 23) "
			"FROM Ticket "
			"WHERE users_id = ? "
			"ORDER BY journey_date DESC");

		stmt.bind(0, &_id);
		auto result = nanodbc::execute(stmt);

		std::cout << "==========================================" << std::endl;
		std::cout << "        REZERVARILE MELE                  " << std::endl;
		std::cout << "==========================================" << std::endl;

		int count = 0;
		while (result.next()) {
			int ticket_id = result.get<int>(0);
			int seat_id = result.get<int>(1);
			int begin_stop = result.get<int>(2);
			int end_stop = result.get<int>(3);
			float fare = result.get<float>(4);
			std::string status = result.get<std::string>(5);
			std::string date = result.get<std::string>(6);

			std::cout << "------------------------------------------" << std::endl;
			std::cout << "  Bilet ID:    " << ticket_id << std::endl;
			std::cout << "  Loc ID:      " << seat_id << std::endl;
			std::cout << "  De la statia:" << begin_stop << std::endl;
			std::cout << "  Pana la:     " << end_stop << std::endl;
			std::cout << "  Pret platit: " << fare << " RON" << std::endl;
			std::cout << "  Status:      " << status << std::endl;
			std::cout << "  Data:        " << date << std::endl;
			count++;
		}

		if (count == 0) {
			std::cout << "  Nu ai nicio rezervare." << std::endl;
		}

		std::cout << "==========================================" << std::endl;
		std::cout << "  Total: " << count << " bilete" << std::endl;
		std::cout << "==========================================" << std::endl;
	}
	catch (const std::exception& e) {
		Logger::getInstance().log("[REZERVARI] Eroare citire: " + std::string(e.what()));
		std::cout << "[EROARE] Nu s-au putut incarca rezervarile." << std::endl;
	}
}
//journey_date > azi + 1 zi  -> 100% din fare
//journey_date <= azi + 1 zi -> 50% din fare
bool Client::anulareRezervare(int ticket_id)
{
	try {
		auto& db = DatabaseManager::getInstance();
		auto& conn = db.getConnection();

		//verifica biletul
		nanodbc::statement checkStmt(conn);
		nanodbc::prepare(checkStmt,
			"SELECT fare, CONVERT(varchar, journey_date, 23) "
			"FROM Ticket "
			"WHERE ticket_id = ? AND users_id = ? AND ticket_status = 'Activ'");
		checkStmt.bind(0, &ticket_id);
		checkStmt.bind(1, &_id);

		auto checkResult = nanodbc::execute(checkStmt);
		if (!checkResult.next()) {
			std::cout << "[EROARE] Biletul nu exista, nu este activ sau nu iti apartine." << std::endl;
			return false;
		}

		float fare = checkResult.get<float>(0);
		std::string dateStr = checkResult.get<std::string>(1); // "YYYY-MM-DD"

		//calculeaza restituirea in functie de journey_date
		int an = std::stoi(dateStr.substr(0, 4));
		int luna = std::stoi(dateStr.substr(5, 2));
		int zi = std::stoi(dateStr.substr(8, 2));

		time_t t = time(nullptr);
		tm* acum = localtime(&t);

		//transformam ambele date in zile de la o referinta simpla
		//pentru a calcula diferenta
		auto toJulian = [](int y, int m, int d) -> long {
			// Formula simpla pentru numar de zile
			return 365L * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + d;
			};

		long journeyJulian = toJulian(an, luna, zi);
		long todayJulian = toJulian(
			acum->tm_year + 1900,
			acum->tm_mon + 1,
			acum->tm_mday
		);

		long diffZile = journeyJulian - todayJulian;

		float refund = (diffZile > 1) ? fare : fare * 0.50f;
		std::string motivRefund = (diffZile > 1) ? "100%" : "50%";

		//tranzactie: anuleaza biletul + restituie credit
		nanodbc::just_execute(conn, "BEGIN TRANSACTION");

		//anuleaza biletul
		nanodbc::statement cancelStmt(conn);
		nanodbc::prepare(cancelStmt,
			"UPDATE Ticket SET ticket_status = 'Anulat' WHERE ticket_id = ?");
		cancelStmt.bind(0, &ticket_id);
		nanodbc::execute(cancelStmt);

		//restituie creditul in db
		float newCredit = _credit + refund;
		nanodbc::statement creditStmt(conn);
		nanodbc::prepare(creditStmt,
			"UPDATE Users SET client_credit = ? WHERE users_id = ?");
		creditStmt.bind(0, &newCredit);
		creditStmt.bind(1, &_id);
		nanodbc::execute(creditStmt);

		nanodbc::just_execute(conn, "COMMIT");

		//actualizeaza si obiectul local
		_credit = newCredit;

		std::cout << "==========================================" << std::endl;
		std::cout << "  Bilet " << ticket_id << " anulat cu succes." << std::endl;
		std::cout << "  Restituire: " << motivRefund << " -> " << refund << " RON" << std::endl;
		std::cout << "  Sold nou:   " << _credit << " RON" << std::endl;
		std::cout << "==========================================" << std::endl;

		Logger::getInstance().log("[ANULARE] Bilet " + std::to_string(ticket_id) +
			" anulat de user " + std::to_string(_id) +
			" | Restituit: " + motivRefund + " (" + std::to_string(refund) + " RON)");

		return true;
	}
	catch (const std::exception& e) {
		try {
			nanodbc::just_execute(DatabaseManager::getInstance().getConnection(), "ROLLBACK");
		}
		catch (...) {}
		Logger::getInstance().log("[ANULARE] Eroare ROLLBACK: " + std::string(e.what()));
		std::cout << "[EROARE] Anularea a esuat." << std::endl;
		return false;
	}
}

void Client::afisareNotificari() const
{
	std::string idStr = std::to_string(_id);
	auto notificari = Logger::getInstance().getLogsFor(idStr);

	if (notificari.empty()) return;

	std::cout << "==========================================" << std::endl;
	std::cout << "  *** NOTIFICARI NOI ***                  " << std::endl;
	std::cout << "==========================================" << std::endl;
	for (const auto& n : notificari) {
		std::cout << "  >> " << n << std::endl;
	}
	std::cout << "==========================================" << std::endl;
}
