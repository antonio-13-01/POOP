#include <iostream>
#include "nanodbc.h"
#include "RailBookApp.h"
#include "Migration.h"

int main() {
    try {
        // Adaugă MultipleActiveResultSets=True; la finalul string-ului
        std::string conn_str = "DRIVER={ODBC Driver 17 for SQL Server};SERVER=DESKTOP-INU1UOQ\\SQLEXPRESS;DATABASE=RailBook;Trusted_Connection=yes;MultipleActiveResultSets=True;";        
        RailBookApp::getInstance().initialize(conn_str);

        auto& app = RailBookApp::getInstance();
        std::cout << "DEBUG: Numar trenuri in memorie: " << app.getTrains().size() << std::endl;

		//Fiindca am avut parolele in clar, am decis sa le migrez catre bcrypt
		//Nu mai trebuie sa rulez aceasta migratie, am facut-o o singura data, dar am lasat-o aici pentru referinta
        //
        //std::cout << "Se incepe migrarea parolelor..." << std::endl;
        //MigratePasswords();
        //std::cout << "Migrarea s-a incheiat cu succes!" << std::endl;


        RailBookApp::getInstance().displayTrains();

    }
    catch (const std::exception& e) {
		std::cout << "Eroare: " << e.what() << std::endl;
    }
    return 0;
}