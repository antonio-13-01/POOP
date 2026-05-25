#include <vector>
#include <string>
#include "UserFactory.h"

IUser::UserType UserFactory::stringToUserType(const std::string& roleStr) {
    if (roleStr == "Admin") return IUser::UserType::Admin;
    if (roleStr == "Operator") return IUser::UserType::Operator;
    return IUser::UserType::Client;
}

int UserFactory::signUp(const std::string& lastName, const std::string& firstName,
    const std::string& email, const std::string& password,
    const std::string& role, const std::string& category,
    const std::string& valability, const std::string& ic_number)
{
    if (email.find('@') == std::string::npos) return -1;
    try {
        auto& db = DatabaseManager::getInstance();
        std::string passwordHash = SecurityUtils::HashPassword(password);

        std::string sql = "INSERT INTO dbo.Users (users_last_name, users_first_name, users_email, "
            "users_password, users_role, client_category, valability_date, identity_card_number, is_blocked) "
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, 0)";

        nanodbc::statement stmt(db.getConnection());
        nanodbc::prepare(stmt, sql);

        stmt.bind(0, lastName.c_str());
        stmt.bind(1, firstName.c_str());
        stmt.bind(2, email.c_str());
        stmt.bind(3, passwordHash.c_str());
        stmt.bind(4, role.c_str());
        stmt.bind(5, category.c_str());

        if (valability.empty()) stmt.bind_null(6);
        else stmt.bind(6, valability.c_str());

        if (ic_number.empty()) stmt.bind_null(7);
        else stmt.bind(7, ic_number.c_str());

        nanodbc::execute(stmt);

        nanodbc::statement stmtId(db.getConnection());
        nanodbc::prepare(stmtId, "SELECT CAST(SCOPE_IDENTITY() AS INT)");
        auto result = nanodbc::execute(stmtId);

        if (result.next()) return result.get<int>(0);
    }
    catch (const std::exception& e) {
        std::cerr << "Eroare SignUp: " << e.what() << std::endl;
        return -1;
    }
    return -1;
}

IUser* UserFactory::LoadUserFromDB(int id) {
    auto& db = DatabaseManager::getInstance();
    nanodbc::statement stmt(db.getConnection());

    nanodbc::prepare(stmt, "SELECT users_last_name, users_first_name, users_email, users_password, "
        "users_role, client_category, client_credit, valability_date, is_blocked "
        "FROM dbo.Users WHERE users_id = ?");

    stmt.bind(0, &id);
    auto result = nanodbc::execute(stmt);

    if (result.next()) {
        std::string lastName = result.get<std::string>(0);
        std::string firstName = result.get<std::string>(1);
        std::string email = result.get<std::string>(2);
        std::string password = result.get<std::string>(3);
        std::string role = result.get<std::string>(4);
        bool isBlocked = result.get<int>(8) != 0;

        if (role == "Admin") {
            return new Admin(id, lastName, firstName, email, password, IUser::UserType::Admin, isBlocked);
        }
        else if (role == "Operator") {
            return new Operator(id, lastName, firstName, email, password, IUser::UserType::Operator, isBlocked);
        }
        else {
            std::string category = result.is_null(5) ? "Adult" : result.get<std::string>(5);
            float credit = result.is_null(6) ? 0.0f : result.get<float>(6);
            std::string valability = result.is_null(7) ? "" : result.get<std::string>(7);

            if (category == "Student")
                return new Student(id, lastName, firstName, email, password, IUser::UserType::Client, credit, valability, isBlocked);
            if (category == "Pupil")
                return new Pupil(id, lastName, firstName, email, password, IUser::UserType::Client, credit, valability, isBlocked);
            if (category == "Pensioner")
                return new Pensioner(id, lastName, firstName, email, password, IUser::UserType::Client, credit, valability, isBlocked);

            return new Adult(id, lastName, firstName, email, password, IUser::UserType::Client, credit, valability, isBlocked);
        }
    }
    return nullptr;
}

bool UserFactory::login(const std::string& email, const std::string& password,
    const std::string& ic_number)
{
    auto& db = DatabaseManager::getInstance();
    nanodbc::statement stmt(db.getConnection());

    nanodbc::prepare(stmt,
        "SELECT users_id, users_password, client_category, identity_card_number "
        "FROM dbo.Users WHERE users_email = ?");
    stmt.bind(0, email.c_str());
    auto result = nanodbc::execute(stmt);

    if (result.next()) {
        int id = result.get<int>(0);
        std::string storedHash = result.get<std::string>(1);
        std::string category = result.is_null(2) ? "Adult" : result.get<std::string>(2);
        std::string storedIC = result.is_null(3) ? "" : result.get<std::string>(3);

        //verificare pass cu bcrypt
        if (!SecurityUtils::VerifyPassword(password, storedHash)) {
            return false;
        }

        //verificare id legitimatie pt stud si elev
        if (category == "Student" || category == "Pupil") {
            if (ic_number.empty() || ic_number != storedIC) {
                std::cout << "[EROARE] ID legitimatie incorect pentru cont "
                    << category << "." << std::endl;
                return false;
            }
        }

        IUser* user = LoadUserFromDB(id);
        if (!user) return false;

        if (user->isBlocked()) {
            std::cout << "[BLOCAT] Contul dvs. a fost suspendat." << std::endl;
            delete user;
            return false;
        }

        SessionManager::getInstance().login(user);
        return true;
    }
    return false;
}

std::vector<int> UserFactory::GetAllUserIds() {
    auto& db = DatabaseManager::getInstance();
    auto result = db.executeQuery("SELECT users_id FROM dbo.Users");

    std::vector<int> ids;
    while (result.next()) {
        ids.push_back(result.get<int>(0));
    }
    return ids;
}