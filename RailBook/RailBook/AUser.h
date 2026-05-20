#pragma once
#include "IUser.h"

class AUser : public IUser
{
protected:
	int _id;
	std::string _last_name;
	std::string _name;
	std::string _email;
	std::string _password;
	UserType _userType;
	bool _isBlocked;
public:
	AUser(int id, const std::string last_name,
		const std::string name, const std::string email,
		const std::string parolaHash, UserType userType,
		bool _isBlocked);

	int getId() const override;
	std::string getLastName() const override;
	std::string getName() const override;
	std::string getEmail() const override;
	std::string getPassword() const override;
	UserType getUserType() const override;
	bool isBlocked() const override;
	void setBlocked(bool blocked) override;
	void displayUser() const override;
	void setLastName(const std::string lastName) override;
	void setName(const std::string name) override;
	void setPassword(const std::string password) override;
};