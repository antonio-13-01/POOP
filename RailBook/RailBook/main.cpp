#include <iostream>
#include "nanodbc.h"
#include "RailBookApp.h"
#include "Exceptions.h"
#include "Server.h"

int main() {
    std::cout << "Pornirea aplicatiei RailBook..." << std::endl;

    try {
        std::string conn_str = "DRIVER={ODBC Driver 17 for SQL Server};"
            "SERVER=DESKTOP-B6Q1E26\\SQLEXPRESS;"
            "DATABASE=RailBook;"
            "Trusted_Connection=yes;"
            "MultipleActiveResultSets=True;";

        auto& app = RailBookApp::getInstance();
        app.initialize(conn_str);

        std::cout << "[OK] Baza de date initializata." << std::endl;

        // Porneste serverul TCP — blocheaza aici
        runServer(app, 1234);
    }
    catch (const nanodbc::database_error& e) {
        std::cerr << "EROARE NANODBC: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "EROARE STANDARD: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "EROARE NECUNOSCUTA!" << std::endl;
    }

    return 0;
}