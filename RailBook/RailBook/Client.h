#pragma once
#include "AUtilizator.h"
class Client :
    public AUtilizator
{
private:
	std::string _idClient;
	float _soldCredit;
	std::string _valabilitate;
public:
	enum class ClientType
	{ Adult, Pensionar, Student, Elev };
	ClientType _clientType;

	Client(int id, const std::string& nume, const std::string& prenume, const std::string& email, const std::string& parolaHash, UserType userType, ClientType clientType, std::string idClient, float soldCredit, std:: string valabilitate);
	std::string getIdClient() const;
	ClientType getClientType() const;

};

