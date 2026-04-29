#define _CRT_SECURE_NO_WARNINGS
#include "Admin.h"
#include <string>


Admin::Admin(int id, const std::string last_name, const std::string name, const std::string email, const std::string parolaHash, UserType userType, bool isBlocked)
	:AUser(id, last_name, name, email, parolaHash, userType, isBlocked)   
{ }

int Admin::verifyClient(Client client) const
{
    if (client.getId() <= 0)
        return 0;

    if (client.getLastName().empty() || client.getName().empty())
        return 0;

    if (client.getEmail().find('@') == std::string::npos)
        return 0;

    if (client.getCredit() < 0)
        return 0;

    std::string val = client.getValability();
    if (val.length() < 10)
        return 0;

    int an = std::stoi(val.substr(0, 4));
    int luna = std::stoi(val.substr(5, 2));
    int zi = std::stoi(val.substr(8, 2));

    time_t t = time(nullptr);
    tm* acum = localtime(&t);
    int anCurent = acum->tm_year + 1900;
    int lunaCurenta = acum->tm_mon + 1;
    int ziCurenta = acum->tm_mday;

    if (an < anCurent)
        return 0;
    if (an == anCurent && luna < lunaCurenta)
        return 0;
    if (an == anCurent && luna == lunaCurenta && zi < ziCurenta)
        return 0;

    return 1;
}

int Admin::alimentareCredit(Client client) const
{
    float sold = client.getCredit();
    if (sold <= 50) {
        sold+=100;
    }
    client.setCredit(sold);
}

void Admin::blocareClient(Client client) const
{
    if (client.isBlocked())
        Logger::getInstance().log("clientul este deja blocat\n");
    client.setBlocked(true);
    Logger::getInstance().log("clientul " + client.getName() + " a fost blocat\n");
}

void Admin::deblocareClient(Client client) const
{
    if (!client.isBlocked())
        Logger::getInstance().log("clientul nu este blocat\n");
    client.setBlocked(false);
    Logger::getInstance().log("clientul " + client.getName() + " a fost deblocat\n");
}

void Admin::modificareTipClient(Client client, Client::ClientType newType) const
{
    client.setClientType(newType);
}

