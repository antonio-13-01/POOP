#include "Client.h"

Client::Client(int id, const std::string last_name,
	const std::string name, const std::string email,
	const std::string parolaHash, UserType userType,
	float credit, std::string valability, bool isBlocked)
	:AUser(id, last_name, name, email, parolaHash, userType,isBlocked), _credit(credit), _valability(valability)
{
}

int Client::getId() const
{
	return _id;
}

std::string Client::getLastName() const
{
	return _last_name;
}

std::string Client::getName() const
{
	return _name;
}

std::string Client::getEmail() const
{
	return _email;
}

Client::ClientType Client::getClientType() const
{
	return _type;
}

float Client::getCredit() const
{
	return _credit;
}

std::string Client::getValability() const
{
	return _valability;
}

void Client::setCredit(float credit)
{
	_credit = credit;
}

void Client::setClientType(ClientType clientType)
{
	_type = clientType;
}
