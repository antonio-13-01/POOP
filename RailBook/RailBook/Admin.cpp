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

void Admin::alimentareCredit(int userId, float amount = 100.0f) const
{
    if (userId <= 0 || amount <= 0) {
        Logger::getInstance().log("[ADMIN] Alimentare refuzata — parametri invalizi pentru user ID: " +
            std::to_string(userId));
        return;
    }

    try {
        auto& db = DatabaseManager::getInstance();

        // Citim soldul curent din DB
        nanodbc::statement selectStmt(db.getConnection());
        nanodbc::prepare(selectStmt,
            "SELECT client_credit FROM dbo.Users WHERE users_id = ?");
        selectStmt.bind(0, &userId);
        auto result = nanodbc::execute(selectStmt);

        if (!result.next()) {
            Logger::getInstance().log("[ADMIN] Alimentare refuzata — user ID negasit: " +
                std::to_string(userId));
            return;
        }

        float soldCurent = result.get<float>(0);

        // Aplicam regula: daca soldul e <= 50, adaugam 100 RON
        if (soldCurent <= 50) {
            float soldNou = soldCurent + amount;

            nanodbc::statement updateStmt(db.getConnection());
            nanodbc::prepare(updateStmt,
                "UPDATE dbo.Users SET client_credit = ? WHERE users_id = ?");
            updateStmt.bind(0, &soldNou);
            updateStmt.bind(1, &userId);
            nanodbc::execute(updateStmt);

            Logger::getInstance().log("[ADMIN] Credit alimentat pentru user ID " +
                std::to_string(userId) + " | Sold vechi: " + std::to_string(soldCurent) +
                " RON | Sold nou: " + std::to_string(soldNou) + " RON");

            std::cout << "[OK] Credit alimentat. Sold nou: " << soldNou << " RON" << std::endl;
        }
        else {
            Logger::getInstance().log("[ADMIN] Alimentare refuzata — soldul (" +
                std::to_string(soldCurent) + " RON) depaseste limita pentru user ID: " +
                std::to_string(userId));
            std::cout << "[INFO] Soldul curent (" << soldCurent
                << " RON) este deja peste limita de alimentare." << std::endl;
        }
    }
    catch (const std::exception& e) {
        Logger::getInstance().log("[ADMIN] Eroare alimentare credit: " + std::string(e.what()));
    }
}

void Admin::blocareClient(int userId) const
{
    if (userId <= 0) {
        Logger::getInstance().log("[ADMIN] Blocare refuzata — userId invalid.");
        return;
    }

    try {
        auto& db = DatabaseManager::getInstance();

        // Verificam daca e deja blocat
        nanodbc::statement checkStmt(db.getConnection());
        nanodbc::prepare(checkStmt,
            "SELECT is_blocked, users_first_name FROM dbo.Users WHERE users_id = ?");
        checkStmt.bind(0, &userId);
        auto result = nanodbc::execute(checkStmt);

        if (!result.next()) {
            Logger::getInstance().log("[ADMIN] Blocare refuzata — user ID negasit: " +
                std::to_string(userId));
            return;
        }

        bool isAlreadyBlocked = result.get<int>(0) != 0;
        std::string userName = result.get<std::string>(1);

        if (isAlreadyBlocked) {
            Logger::getInstance().log("[ADMIN] Clientul " + userName + " (ID: " +
                std::to_string(userId) + ") este deja blocat.");
            std::cout << "[INFO] Contul este deja blocat." << std::endl;
            return;
        }

        // Blocam contul in DB
        nanodbc::statement updateStmt(db.getConnection());
        nanodbc::prepare(updateStmt,
            "UPDATE dbo.Users SET is_blocked = 1 WHERE users_id = ?");
        updateStmt.bind(0, &userId);
        nanodbc::execute(updateStmt);

        Logger::getInstance().log("[ADMIN] Clientul " + userName + " (ID: " +
            std::to_string(userId) + ") a fost blocat.");
        std::cout << "[OK] Contul utilizatorului " << userName << " a fost blocat." << std::endl;
    }
    catch (const std::exception& e) {
        Logger::getInstance().log("[ADMIN] Eroare blocare client: " + std::string(e.what()));
    }
}

void Admin::deblocareClient(int userId) const
{
    if (userId <= 0) {
        Logger::getInstance().log("[ADMIN] Deblocare refuzata — userId invalid.");
        return;
    }

    try {
        auto& db = DatabaseManager::getInstance();

        // Verificam daca e intr-adevar blocat
        nanodbc::statement checkStmt(db.getConnection());
        nanodbc::prepare(checkStmt,
            "SELECT is_blocked, users_first_name FROM dbo.Users WHERE users_id = ?");
        checkStmt.bind(0, &userId);
        auto result = nanodbc::execute(checkStmt);

        if (!result.next()) {
            Logger::getInstance().log("[ADMIN] Deblocare refuzata — user ID negasit: " +
                std::to_string(userId));
            return;
        }

        bool isBlocked = result.get<int>(0) != 0;
        std::string userName = result.get<std::string>(1);

        if (!isBlocked) {
            Logger::getInstance().log("[ADMIN] Clientul " + userName + " (ID: " +
                std::to_string(userId) + ") nu este blocat.");
            std::cout << "[INFO] Contul nu este blocat." << std::endl;
            return;
        }

        // Deblocam contul in DB
        nanodbc::statement updateStmt(db.getConnection());
        nanodbc::prepare(updateStmt,
            "UPDATE dbo.Users SET is_blocked = 0 WHERE users_id = ?");
        updateStmt.bind(0, &userId);
        nanodbc::execute(updateStmt);

        Logger::getInstance().log("[ADMIN] Clientul " + userName + " (ID: " +
            std::to_string(userId) + ") a fost deblocat.");
        std::cout << "[OK] Contul utilizatorului " << userName << " a fost deblocat." << std::endl;
    }
    catch (const std::exception& e) {
        Logger::getInstance().log("[ADMIN] Eroare deblocare client: " + std::string(e.what()));
    }
}

void Admin::modificareTipClient(int userId, Client::ClientType newType, const std::string& newValability, const std::string& newIc) const
{
    if (userId <= 0) {
        Logger::getInstance().log("[ADMIN] Modificare tip refuzata — userId invalid.");
        return;
    }

    std::string tipStr;
    bool isAdult = false;
    switch (newType) {
    case Client::ClientType::Student:   tipStr = "Student";   break;
    case Client::ClientType::Elev:      tipStr = "Pupil";     break;
    case Client::ClientType::Pensionar: tipStr = "Pensioner"; break;
    case Client::ClientType::Adult:
    default:                            isAdult = true;       break;
    }

    try {
        auto& db = DatabaseManager::getInstance();

        // 1. Verificam existenta utilizatorului
        nanodbc::statement checkStmt(db.getConnection());
        nanodbc::prepare(checkStmt, "SELECT users_first_name FROM dbo.Users WHERE users_id = ?");
        checkStmt.bind(0, &userId);
        auto result = nanodbc::execute(checkStmt);

        if (!result.next()) {
            Logger::getInstance().log("[ADMIN] Modificare tip refuzata — user ID negasit: " + std::to_string(userId));
            return;
        }

        std::string userName = result.get<std::string>(0);

        // 2. Facem Update-ul curat si corect
        nanodbc::statement updateStmt(db.getConnection());
        nanodbc::prepare(updateStmt,
            "UPDATE dbo.Users SET client_category = ?, valability_date = ?, identity_card_number = ? WHERE users_id = ?");

        if (isAdult) {
            updateStmt.bind_null(0);
            updateStmt.bind_null(1);
            updateStmt.bind_null(2);
        }
        else {
            updateStmt.bind(0, tipStr.c_str());

            // Daca admin-ul a introdus date, le salvam. Altfel, in functie de DB, poate da eroare de constrangere.
            if (newValability.empty()) updateStmt.bind_null(1);
            else updateStmt.bind(1, newValability.c_str());

            if (newIc.empty()) updateStmt.bind_null(2);
            else updateStmt.bind(2, newIc.c_str());
        }

        updateStmt.bind(3, &userId);
        nanodbc::execute(updateStmt);

        Logger::getInstance().log("[ADMIN] Tip cont modificat la '" + (isAdult ? "Adult" : tipStr) +
            "' pentru " + userName + " (ID: " + std::to_string(userId) + ")");
        std::cout << "[OK] Tipul contului a fost modificat la: " << (isAdult ? "Adult" : tipStr) << std::endl;
    }
    catch (const std::exception& e) {
        Logger::getInstance().log("[ADMIN] Eroare modificare tip client: " + std::string(e.what()));
        std::cout << "[EROARE] Modificare esuata: " << e.what() << std::endl;
    }
}

bool Admin::resetParola(int user_id, const std::string& newPassword) const
{
    if (newPassword.empty()) {
        Logger::getInstance().log("[ADMIN] Resetare parola refuzata — parola goala pentru user ID: " +
            std::to_string(user_id));
        return false;
    }

    try {
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

        std::cout << "[OK] Parola a fost resetata cu succes." << std::endl;
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