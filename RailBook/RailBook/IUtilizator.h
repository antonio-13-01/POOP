#pragma once
#include <iostream>

class IUtilizator
{
public:
	enum class UserType { Admin, Operator, Client };

	virtual int getId() const = 0;
	virtual std::string getName() const = 0;
	virtual std::string getPrenume() const = 0;
	virtual std::string getEmail() const = 0;
	virtual std::string getParolaHash() const = 0;]
	virtual UserType getUserType() const = 0;
};

