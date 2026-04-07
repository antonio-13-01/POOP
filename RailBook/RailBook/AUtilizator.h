#pragma once
#include "IUtilizator.h"

class AUtilizator : public IUtilizator
{
private:
	int _id;
	std::string _nume;
	std::string _prenume;
	std::string _email;
	std::string _parolaHash;
	UserType _userType;
public:
	AUtilizator(int id, const std::string& nume, const std::string& prenume, const std::string& email, const std::string& parolaHash, UserType userType);
	int getId() const override;
	std::string getName() const override;
	std::string getPrenume() const override;
	std::string getEmail() const override;
	std::string getParolaHash() const override;
	UserType getUserType() const override;
};

