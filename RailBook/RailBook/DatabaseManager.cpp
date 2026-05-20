#include "DatabaseManager.h"

DatabaseManager& DatabaseManager::getInstance()
{
    static DatabaseManager instance;
    return instance;
}

void DatabaseManager::connect(const std::string& connection_string)
{
    // Aici inițializez obiectul nanodbc::connection
    conn.connect(connection_string);
}

nanodbc::connection& DatabaseManager::getConnection()
{
    if (!conn.connected()) {
        throw std::runtime_error("Nu exista o conexiune activa la baza de date!");
    }
    return conn;
}


void DatabaseManager::execute(const std::string& sql)
{
    
	if (!conn.connected()) {
        throw std::runtime_error("Nu ești conectat la baza de date!");
    }

	nanodbc::execute(conn, sql);
}

void DatabaseManager::isConnected() const {
    if (conn.connected()) {
        std::cout << "Conexiune la baza de date stabilită." << std::endl;
    }
    else {
        std::cout << "Nu ești conectat la baza de date!" << std::endl;
    }
}

nanodbc::result DatabaseManager::executeQuery(const std::string& sql)
{   
    if(!conn.connected()) {
        throw std::runtime_error("Nu ești conectat la baza de date!");
	}   
    return nanodbc::execute(conn, sql);
}

nanodbc::transaction DatabaseManager::beginTransaction()
{
    if (!conn.connected()) {
        throw std::runtime_error("Nu ești conectat la baza de date pentru a iniția o tranzacție!");
    }
    // Returnăm obiectul de tranzacție. 
    // Acesta va da automat BEGIN TRAN în baza de date.
    return nanodbc::transaction(conn);
}
