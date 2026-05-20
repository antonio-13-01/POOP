// SessionManager.h
#pragma once
#include "IUser.h"

class SessionManager {
public:
    static SessionManager& getInstance() {
        static SessionManager instance;
        return instance;
    }

    void login(IUser* user) { _currentUser = user; }
    void logout() { _currentUser = nullptr; }

    IUser* getCurrentUser() const { return _currentUser; }
    bool isLoggedIn() const { return _currentUser != nullptr; }

    bool isAdmin() const { return isLoggedIn() && _currentUser->getUserType() == IUser::UserType::Admin; }
    bool isOperator() const { return isLoggedIn() && _currentUser->getUserType() == IUser::UserType::Operator; }

private:
    SessionManager() : _currentUser(nullptr) {}
    IUser* _currentUser;
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;
};