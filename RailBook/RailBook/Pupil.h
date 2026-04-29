#pragma once
#include "Client.h"
#include <string>
class Pupil :
    public Client
{
	Pupil(int id, const std::string last_name, const std::string name,
		const std::string email, const std::string parolaHash,
		UserType userType, float credit, std::string valability, 
		bool isBlocked);
};

