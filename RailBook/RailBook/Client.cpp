#include "Client.h"

Client::Client(int id, const std::string& last_name, const std::string& name, const std::string& email, const std::string& parolaHash, UserType userType, float credit, std::string valability, std::string idDiscount)
	:AUser(id, last_name, name, email, parolaHash, userType), _credit(credit), _valability(valability), _idDiscount(idDiscount)
{
	_idDiscount = idDiscount;	
}

std::string Client::getIdDiscount() const
{
	return _idDiscount;
}

Client::ClientType Client::getClientType() const
{
	return _type;
}
