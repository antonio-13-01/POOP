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
	virtual bool isBlocked() const = 0;
	virtual void setBlocked(bool blocked) = 0;
	virtual void displayUser() const = 0;

	virtual void setLastName(const std::string lastName) = 0;
	virtual void setName(const std::string name) = 0;
	virtual void setPassword(const std::string password) = 0;

	virtual ~IUser() = default;
};

