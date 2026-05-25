#pragma once
#include "AUser.h"
#include "Client.h"
#include "Logger.h"
#include "DatabaseManager.h"
#include "nanodbc.h"

class Admin : public AUser
{
public:
    Admin(int id, const std::string last_name,
        const std::string name, const std::string email,
        const std::string parolaHash,
        UserType userType, bool isBlocked);


    int verifyClient(const Client& client) const;
    void alimentareCredit(int userId, float amount) const;
    void blocareClient(int userId) const;
    void deblocareClient(int userId) const;
    void modificareTipClient(int userId, Client::ClientType newType, const std::string& newValability = "", const std::string& newIc = "") const;
    bool resetParola(int user_id, const std::string& newPassword) const;
    void afisareJurnal() const;

    void displayUser() const override;
};