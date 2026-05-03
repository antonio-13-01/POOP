#include "SecurityUtils.h"
#include "RailBookApp.h"

void MigratePasswords() {
    auto& db = RailBookApp::getInstance().getDatabaseManager();

    // 1. Luăm toți utilizatorii cu parolele în clar
    auto result = db.executeQuery("SELECT users_id, users_password FROM Users");

    std::vector<std::pair<int, std::string>> users;

    while (result.next()) {
        int id = result.get<int>(0);
        std::string plainPass = result.get<std::string>(1);
        users.push_back({ id, plainPass });
    }

    // 2. Hashuim și update-ăm (facem asta după while pentru a evita probleme de cursors)
    for (const auto& user : users) {
        std::string newHash = SecurityUtils::HashPassword(user.second);

        // Construim SQL-ul de update
        std::string sql = "UPDATE Users SET users_password = '" + newHash +
            "' WHERE users_id = " + std::to_string(user.first);

        db.execute(sql);
        std::cout << "Migrat user ID: " << user.first << std::endl;
    }
}
#pragma once

void MigratePasswords();