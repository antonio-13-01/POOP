#define _CRT_SECURE_NO_WARNINGS
#include "Admin.h"
#include "SecurityUtils.h"
#include <string>
#include <fstream>
#include <iostream>

Admin::Admin(int id, const std::string last_name,
    const std::string name, const std::string email,
    const std::string parolaHash, UserType userType,
    bool isBlocked)
    : AUser(id, last_name, name, email, parolaHash, userType, isBlocked)
{}

int Admin::verifyClient(const Client& client) const
{
    if (client.getId() <= 0) return 0;
    if (client.getLastName().empty() || client.getName().empty()) return 0;
    if (client.getEmail().find('@') == std::string::npos) return 0;
    if (client.getCredit() < 0) return 0;

    std::string val = client.getValability();
    if (val.length() < 10) return 0;

    int an = std::stoi(val.substr(0, 4));
    int luna = std::stoi(val.substr(5, 2));
    int zi = std::stoi(val.substr(8, 2));

    time_t t = time(nullptr);
    tm* acum = localtime(&t);
    int anCurent = acum->tm_year + 1900;
    int lunaCurenta = acum->tm_mon + 1;
    int ziCurenta = acum->tm_mday;

    if (an < anCurent) return 0;
    if (an == anCurent && luna < lunaCurenta) return 0;
    if (an == anCurent && luna == lunaCurenta && zi < ziCurenta) return 0;

    return 1;
}

void Admin::alimentareCredit(Client client) const
{
    if (verifyClient(client) == 0) {
        Logger::getInstance().log("[ADMIN] Client invalid, alimentare refuzata pentru: " +
            client.getName());
        return;
    }

    float sold = client.getCredit();
    if (sold <= 100) {
        sold += 100;
        client.setCredit(sold);
        Logger::getInstance().log("[ADMIN] Credit alimentat pentru " +
            client.getName() + " | Nou sold: " + std::to_string(sold) + " RON");
    }
}

void Admin::blocareClient(Client client) const
{
    if (verifyClient(client) == 0) {
        Logger::getInstance().log("[ADMIN] Client invalid, blocare refuzata pentru: " +
            client.getName());
        return;
    }

    if (client.isBlocked()) {
        Logger::getInstance().log("[ADMIN] Clientul " + client.getName() +
            " este deja blocat.");
        return;
    }
    client.setBlocked(true);
    Logger::getInstance().log("[ADMIN] Clientul " + client.getName() + " a fost blocat.");
}

void Admin::deblocareClient(Client client) const
{
    if (verifyClient(client) == 0) {
        Logger::getInstance().log("[ADMIN] Client invalid, deblocare refuzata pentru: " +
            client.getName());
        return;
    }

    if (!client.isBlocked()) {
        Logger::getInstance().log("[ADMIN] Clientul " + client.getName() +
            " nu este blocat.");
        return;
    }
    client.setBlocked(false);
    Logger::getInstance().log("[ADMIN] Clientul " + client.getName() + " a fost deblocat.");
}

void Admin::modificareTipClient(Client client, Client::ClientType newType) const
{
    if (verifyClient(client) == 0) {
        Logger::getInstance().log("[ADMIN] Client invalid, modificare tip refuzata pentru: " +
            client.getName());
        return;
    }

    client.setClientType(newType);
    Logger::getInstance().log("[ADMIN] Tip client modificat pentru " + client.getName());
}

bool Admin::resetParola(int user_id, const std::string& newPassword) const
{
    if (newPassword.empty()) {
        Logger::getInstance().log("[ADMIN] Resetare parola refuzata — parola goala pentru user ID: " +
            std::to_string(user_id));
        return false;
    }

    try {
		//aici facem hash la parola noua cu bcrypt
        std::string newHash = SecurityUtils::HashPassword(newPassword);

        auto& db = DatabaseManager::getInstance();
        nanodbc::statement stmt(db.getConnection());
        nanodbc::prepare(stmt,
            "UPDATE dbo.Users SET users_password = ? WHERE users_id = ?");

        stmt.bind(0, newHash.c_str());
        stmt.bind(1, &user_id);
        nanodbc::execute(stmt);

        Logger::getInstance().log("[ADMIN] Parola resetata pentru user ID: " +
            std::to_string(user_id));
        return true;
    }
    catch (const std::exception& e) {
        Logger::getInstance().log("[ADMIN] Eroare resetare parola: " + std::string(e.what()));
        return false;
    }
}

void Admin::afisareJurnal() const
{
    std::ifstream logFile("RailBookLog");

    if (!logFile.is_open()) {
        std::cout << "[INFO] Jurnalul de activitate este gol sau nu exista." << std::endl;
        return;
    }

    std::cout << "         JURNAL DE ACTIVITATE             " << std::endl;

    std::string line;
    int lineCount = 0;
    while (std::getline(logFile, line)) {
        std::cout << line << std::endl;
        lineCount++;
    }

    if (lineCount == 0)
        std::cout << "[INFO] Jurnalul este gol." << std::endl;

    std::cout << "  Total intrari: " << lineCount << std::endl;
    logFile.close();
}

void Admin::displayUser() const {
    AUser::displayUser();
    std::cout << " | Acces: Full System Control" << std::endl;
}