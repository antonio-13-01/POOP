#include <iostream>
#include "nanodbc.h"
#include "RailBookApp.h"
#include "Migration.h"

int main() {
	std::cout << "Pornirea aplicatiei RailBook..." << std::endl;

    try {
        // Adaugă MultipleActiveResultSets=True; la finalul string-ului
        std::string conn_str = "DRIVER={ODBC Driver 17 for SQL Server};SERVER=DESKTOP-INU1UOQ\\SQLEXPRESS;DATABASE=RailBook;Trusted_Connection=yes;MultipleActiveResultSets=True;MultipleActiveResultSets = True;";
        RailBookApp::getInstance().initialize(conn_str);

        auto& app = RailBookApp::getInstance();
        

		//Fiindca am avut parolele in clar, am decis sa le migrez catre bcrypt
		//Nu mai trebuie sa rulez aceasta migratie, am facut-o o singura data, dar am lasat-o aici pentru referinta
        //
        //MigratePasswords();
        //std::cout << "Migrarea s-a incheiat cu succes!" << std::endl;


        //app.displayTrains();
		//app.displayRoutes();

       // app.displayUsers();

        /*if (app.userSignUp("Nacu", "Ana", "ana@test.ro", "parola123", "Client", "Student", "2024-12-31", "123456789")) {
            std::cout << "Inregistrare reusita!" << std::endl;
        }*/

        //app.displayUsers();

        if (app.userLogin("ana@test.ro", "parola123")) {
            std::cout << "Login reusit! Sesiune pornita prin SessionManager." << std::endl;
        }
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