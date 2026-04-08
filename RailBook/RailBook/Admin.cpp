#define _CRT_SECURE_NO_WARNINGS
#include "Admin.h"
#include <string>
Admin::Admin(int id, const std::string& nume, const std::string& prenume, const std::string& email, const std::string& parolaHash, UserType userType, int idAdmin) : AUtilizator(id, nume, prenume, email, parolaHash, userType), _idAdmin(id)
{
}

int Admin::getIdAdmin() const
{
    return _idAdmin;
}

int Admin::checkClientId(Client* client) const
{
    if (client == nullptr) 
        return 0;

    std::string id = client->getIdClient();

    if (id.length() < 11)
        return 0;

    char tip = id[0];

    Client::ClientType tipAsteptat;
    if (tip == '1') tipAsteptat = Client::ClientType::Adult;
    else if (tip == '2') tipAsteptat = Client::ClientType::Pensionar;
    else if (tip == '3') tipAsteptat = Client::ClientType::Student;
    else if (tip == '4') tipAsteptat = Client::ClientType::Elev;
    else return 0;

    if (client->getClientType() != tipAsteptat)
        return 0;

    std::string anStr = id.substr(2, 4);
    int an = std::stoi(anStr);

    time_t t = time(nullptr);
    int anCurent = localtime(&t)->tm_year + 1900;

    if (an < anCurent)
        return 0;

    return 1;
}
