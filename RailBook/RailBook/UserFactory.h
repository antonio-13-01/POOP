#pragma once
#include <string>
#include <vector>
#include "IUser.h"
#include "DatabaseManager.h"
#include "Admin.h"  
#include "Operator.h"
#include "Student.h"
#include "Pupil.h"
#include "Pensioner.h"
#include "Adult.h"
#include "SecurityUtils.h"
#include <iostream>
#include <stdexcept>
#include "SessionManager.h"
class UserFactory {
public:
    // Cerința 3.1.1: Încărcare și Gestionare [cite: 56]
    static IUser* LoadUserFromDB(int user_id);
    static std::vector<int> GetAllUserIds();
    static IUser::UserType stringToUserType(const std::string& roleStr);

    // Cerința 3.1.1: Înregistrare utilizator [cite: 57]
    static int signUp(const std::string& lastName, const std::string& firstName,
        const std::string& email, const std::string& password,
        const std::string& role, const std::string& category = "Adult Standard",
        const std::string& valability = "", const std::string& ic_number = "");

    // Cerința 3.1.1: Autentificare utilizator [cite: 59]
    static bool login(const std::string& email, const std::string& password);
};