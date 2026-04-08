#pragma once
#include "AUser.h"
#include "Client.h"
class Admin :
    public AUser
{
private:

public:
    Admin(int id, const std::string& last_name, const std::string& name, const std::string& email, const std::string& parolaHash, UserType userType);
    int getIdAdmin() const;

	int checkClientId(Client* client) const;
};

