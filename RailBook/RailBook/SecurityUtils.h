#pragma once
#include <string>
#include "bcrypt.h"

class SecurityUtils {
public:
	//Metoda pentru a hasha parola folosind bcrypt
    static std::string HashPassword(const std::string& plainPassword);

	// Metoda pentru a verifica dacă parola introdusă de utilizator corespunde cu hash-ul stocat în baza de date
    static bool VerifyPassword(const std::string& plainPassword, const std::string& hashedPassword);
};