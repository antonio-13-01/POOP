#include <iostream>
#include "nanodbc.h"

int main() {
    try {
        
        std::string connection_string = "DRIVER={ODBC Driver 17 for SQL Server};SERVER=DESKTOP-INU1UOQ\\SQLEXPRESS;DATABASE=RailBook;Trusted_Connection=yes;";

        nanodbc::connection conn(connection_string);

        if (conn.connected()) {
            std::cout << "========================================" << std::endl;
            std::cout << "   CONEXIUNE REUSITA LA RAILBOOK!      " << std::endl;
            std::cout << "========================================" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "EROARE DE CONEXIUNE: " << e.what() << std::endl;
    }

    std::cout << "\nApasa orice tasta pentru a iesi...";
    std::cin.get();
    return 0;
}