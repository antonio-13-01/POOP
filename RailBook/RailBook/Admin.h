#pragma once
#include "AUser.h"
#include "Client.h"
#include "Logger.h"
class Admin :
    public AUser
{
private:

public:
    Admin(int id, const std::string last_name,
        const std::string name, const std::string email, const std::string parolaHash,
        UserType userType, bool isBlocked);
    
    int getIdAdmin() const;
    int verifyClient(Client client) const; 
    // daca functia returneaza 0 clientul nu e valabil
    //Alimenteze credit utilizatorilor daca soldul e sub 50 ii adauga 100
    int alimentareCredit(Client client) const;
    void blocareClient(Client client) const;
    void deblocareClient(Client client) const;
    void modificareTipClient(Client client, Client::ClientType newType) const;

	void displayUser() const override;  
};

