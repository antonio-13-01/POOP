#include <iostream>
#include "nanodbc.h"
#include "RailBookApp.h"
#include "Exceptions.h"

// Observa ca au disparut include-urile de SessionManager si Factory! 
// RailBookApp controleaza absolut totul acum.

int main() {
    std::cout << "Pornirea aplicatiei RailBook..." << std::endl;

    try {
        // Configurarea initiala
        std::string conn_str = "DRIVER={ODBC Driver 17 for SQL Server};SERVER=DESKTOP-INU1UOQ\\SQLEXPRESS;DATABASE=RailBook;Trusted_Connection=yes;MultipleActiveResultSets=True;";

        auto& app = RailBookApp::getInstance();
        app.initialize(conn_str);

        // 1. Modulul de Autentificare
        if (app.userLogin("ana@test.ro", "parola123")) {
            std::cout << "Login reusit! Utilizatorul a fost conectat." << std::endl;

            // =========================================================================
            // TEST 1: REZERVARE BILET
            // =========================================================================
            std::cout << "\n--- TEST 1: Rezervare Bilet ---" << std::endl;

            int testSeatId = 16;        // Locul 16 (ca sa nu ne lovim de vechiul loc 15)
            int testBeginStop = 1;      // Bucuresti Nord
            int testEndStop = 33;       // Brasov
            float testBaseFare = 50.0f; // Pret de baza
            std::string testDate = "2026-12-05"; // Alta zi

            int biletNouId = -1; // Vom pastra ID-ul ca sa-l anulam automat mai jos

            std::cout << "[INFO] Incercam rezervarea locului " << testSeatId << " pentru data " << testDate << "..." << std::endl;

            try {
                // UI-ul nu mai trimite userId. RailBookApp stie deja cine este logat!
                biletNouId = app.bookSeat(testSeatId, testBeginStop, testEndStop, testBaseFare, testDate, Client::ClientType::Adult);
                std::cout << ">> [SUCCES VALIDAT] Biletul a fost creat! ID Bilet: " << biletNouId << std::endl;
            }
            catch (const SeatTakenException& e) {
                std::cout << ">> [EROARE - LOC OCUPAT] " << e.what() << std::endl;
            }
            catch (const InsufficientFundsException& e) {
                std::cout << ">> [EROARE - FONDURI] " << e.what() << std::endl;
            }
            catch (const DatabaseTransactionException& e) {
                std::cout << ">> [EROARE - DB TRANZACTIE] " << e.what() << std::endl;
            }

            // =========================================================================
            // TEST 2: ANULARE BILET
            // =========================================================================
            std::cout << "\n--- TEST 2: Anulare Bilet ---" << std::endl;

            // Daca testul 1 a reusit, anulam fix biletul creat. Daca nu, incercam un ID oarecare (ex: 5)
            int biletDeAnulat = (biletNouId != -1) ? biletNouId : 5;

            try {
                // Vedem cati bani avem in cont direct prin app.
                float creditInainte = app.getCurrentUserCredit();
                std::cout << "[INFO] Credit inainte de anulare: " << creditInainte << " RON" << std::endl;
                std::cout << "[INFO] Incercam anularea biletului cu ID: " << biletDeAnulat << "..." << std::endl;

                // Anularea se face cu un singur apel
                if (app.cancelTicket(biletDeAnulat)) {
                    float creditDupa = app.getCurrentUserCredit();
                    std::cout << ">> [SUCCES VALIDAT] Biletul a fost anulat!" << std::endl;
                    std::cout << ">> [INFO] Banii au fost returnati. Noul credit: " << creditDupa << " RON" << std::endl;
                }
                else {
                    std::cout << ">> [EROARE] Biletul nu a putut fi anulat (deja anulat sau nu iti apartine)." << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cout << ">> [EROARE - SISTEM] " << e.what() << std::endl;
            }
        }
    }
    // Tratarea erorilor generale pentru cand "crapa" complet baza de date / conexiunea
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