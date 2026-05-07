#pragma once
#include "AUser.h"
class Operator :
    public AUser
{
private:

public:
	Operator(int id, const std::string last_name, 
		const std::string name, const std::string email,
		const std::string parolaHash, UserType userType, bool isBlocked);
	
	void displayUser() const override;
};

