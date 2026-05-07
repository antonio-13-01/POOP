#include "SecurityUtils.h"

std::string SecurityUtils::HashPassword(const std::string& plainPassword) {
    // Aceasta este o formă generică; 
    // verifică documentația bibliotecii tale pentru funcția exactă de hash
    return bcrypt::generateHash(plainPassword);
}

bool SecurityUtils::VerifyPassword(const std::string& plainPassword, const std::string& hashedPassword) {
    return bcrypt::validatePassword(plainPassword, hashedPassword);
}
