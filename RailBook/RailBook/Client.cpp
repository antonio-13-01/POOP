#include "Client.h"

Client::Client(int id, const std::string& nume, const std::string& prenume, const std::string& email, const std::string& parolaHash, UserType userType, ClientType clientType, std::string idClient, float soldCredit, std::string valabilitate)
	: AUtilizator(id, nume, prenume, email, parolaHash, userType)
	,_clientType(clientType), _idClient(idClient), _soldCredit(soldCredit), _valabilitate(valabilitate)
{
}

std::string Client::getIdClient() const
{
	return _idClient;
}

Client::ClientType Client::getClientType() const
{
	return _clientType;
}

