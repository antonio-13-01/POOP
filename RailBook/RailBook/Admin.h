#pragma once
#include "AUtilizator.h"
#include "Client.h"
class Admin :
    public AUtilizator
{
private:
    int _idAdmin;
public:
    Admin(int id, const std::string& nume, const std::string& prenume, const std::string& email, const std::string& parolaHash, UserType userType, int idAdmin);
    int getIdAdmin() const;

	int checkClientId(Client* client) const;
};

