#include "AUser.h"

AUser::AUser(int id, const std::string last_name, 
	const std::string name, const std::string email,
	const std::string password, UserType userType,
	bool _isBlocked)
	: _id(id), _last_name(last_name), _name(name), _email(email), _password(password), _userType(userType), _isBlocked(false)
{}

int AUser::getId() const
{
	return _id;
}

std::string AUser::getLastName() const
{
	return _last_name;
}

std::string AUser::getName() const
{
	return _name;
}

std::string AUser::getEmail() const
{
	return _email;
}

std::string AUser::getPassword() const
{
	return _password;
}

IUser:: UserType AUser::getUserType() const
{
	return _userType;
}

bool AUser::isBlocked() const
{
	return _isBlocked;
}

void AUser::setBlocked(bool blocked)
{
	_isBlocked = blocked;
}

void AUser::displayUser() const
{
	std::cout << "[" << (_userType == UserType::Admin ? "ADMIN" :
		_userType == UserType::Operator ? "OPERATOR" : "CLIENT") << "] "
		<< "ID: " << _id << " | " << _last_name << " " << _name
		<< " | Email: " << _email;
	if (_isBlocked) std::cout << " [BLOCAT]";
}

