#pragma once
#include "AUser.h"
#include "Client.h"
#include "Logger.h"

class Admin : public AUser
{
public:
    Admin(int id, const std::string last_name,
        const std::string name, const std::string email,
        const std::string parolaHash,
        UserType userType, bool isBlocked);

    int verifyClient(const Client& client) const;
    int alimentareCredit(Client client) const;
    void blocareClient(Client client) const;
    void deblocareClient(Client client) const;
    void modificareTipClient(Client client, Client::ClientType newType) const;
    void afisareJurnal() const;
    void displayUser() const override;
};