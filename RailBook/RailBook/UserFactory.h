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
    static IUser* LoadUserFromDB(int user_id);
    static std::vector<int> GetAllUserIds();
    static IUser::UserType stringToUserType(const std::string& roleStr);

    static int signUp(const std::string& lastName, const std::string& firstName,
        const std::string& email, const std::string& password,
        const std::string& role, const std::string& category = "Adult",
        const std::string& valability = "", const std::string& ic_number = "");

    // ic_number -doar pentru stud si elev
    static bool login(const std::string& email, const std::string& password,
        const std::string& ic_number = "");
};