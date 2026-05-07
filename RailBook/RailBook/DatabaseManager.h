#pragma once
#include <iostream>
#include <string>
#include "nanodbc.h"
class DatabaseManager
{
private:

public:
	static DatabaseManager& getInstance();
	// Metoda pentru a stabili conexiunea la baza de date
	void connect(const std::string& connection_string);
	// Metoda pentru a obține o conexiune activă
	nanodbc::connection& getConnection();
	//Metoda pentru Update, Insert, Delete	
	void execute(const std::string& sql);
	//Metoda pentru a verifica dacă conexiunea este stabilită
	void isConnected() const;
	// Metoda pentru a executa interogări de tip SELECT și a returna rezultatele
	nanodbc::result executeQuery(const std::string& sql);

private:
	nanodbc::connection conn;

	DatabaseManager() = default;
	~DatabaseManager()
	{
		if (conn.connected()) {
			conn.disconnect();
		}
	}
	DatabaseManager(const DatabaseManager&) = delete;
	DatabaseManager& operator=(const DatabaseManager&) = delete;	
};

