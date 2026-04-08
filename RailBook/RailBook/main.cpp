#include <iostream>
#include "nanodbc.h"

int main() {
    try {
        
        std::string connection_string = "DRIVER={ODBC Driver 17 for SQL Server};SERVER=DESKTOP-INU1UOQ\\SQLEXPRESS;DATABASE=RailBook;Trusted_Connection=yes;";

        nanodbc::connection conn(connection_string);

        if (conn.connected()) {
            std::cout << "conexiune" << std::endl;
            
        }
    }
    catch (const std::exception& e) {
        std::cout << "eroare conexiune" << e.what() << std::endl;
    }

    return 0;
}