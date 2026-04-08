#include "AUtilizator.h"

AUtilizator::AUtilizator(int id, const std::string& nume, const std::string& prenume, const std::string& email, const std::string& parolaHash, UserType userType)
	: _id(id), _nume(nume), _prenume(prenume), _email(email), _parolaHash(parolaHash), _userType(userType)
{
}

int AUtilizator::getId() const
{
	return _id;
}

std::string AUtilizator::getName() const
{
	return _nume;
}

std::string AUtilizator::getPrenume() const
{
	return _prenume;
}

std::string AUtilizator::getEmail() const
{
	return _email;
}

std::string AUtilizator::getParolaHash() const
{
	return _parolaHash;
}

IUtilizator:: UserType AUtilizator::getUserType() const
{
	return _userType;
}
