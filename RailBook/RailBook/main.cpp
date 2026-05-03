#include <iostream>
#include "nanodbc.h"
#include "RailBookApp.h"
#include "Migration.h"

int main() {
    std::cout << ">>> PROGRAMUL A PORNIT CU SUCCES <<<" << std::endl;

    // Testam daca codul ajunge aici
    std::string test;
    std::cout << "Apasa ENTER pentru a incerca conectarea...";
    std::getline(std::cin, test);
    try {
        // Adaugă MultipleActiveResultSets=True; la finalul string-ului
        std::string conn_str =
            "DRIVER={ODBC Driver 18 for SQL Server};" // Am pus 18
            "SERVER=DESKTOP-INU1UOQ\\SQLEXPRESS;"
            "DATABASE=RailBook;"
            "Trusted_Connection=yes;"
            "TrustServerCertificate=yes;";

        auto& app = RailBookApp::getInstance();
        app.initialize(conn_str);

       
        app.displayTrains();
        

		//Fiindca am avut parolele in clar, am decis sa le migrez catre bcrypt
		//Nu mai trebuie sa rulez aceasta migratie, am facut-o o singura data, dar am lasat-o aici pentru referinta
        //
        //std::cout << "Se incepe migrarea parolelor..." << std::endl;
        //MigratePasswords();
        //std::cout << "Migrarea s-a incheiat cu succes!" << std::endl;


        RailBookApp::getInstance().displayTrains();

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