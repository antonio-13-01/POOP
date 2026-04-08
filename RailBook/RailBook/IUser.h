#pragma once
#include <iostream>
#include <string>
class IUser
{
public:
	enum class UserType { Admin, Operator, Client };

	virtual int getId() const = 0;
	virtual std::string getLastName() const = 0;
	virtual std::string getName() const = 0;
	virtual std::string getEmail() const = 0;
	virtual std::string getPassword() const = 0;
	virtual UserType getUserType() const = 0;
};

