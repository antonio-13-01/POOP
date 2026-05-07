#include "Pensioner.h"

Pensioner::Pensioner(int id, const std::string last_name, const std::string name,
	const std::string email, const std::string parolaHash,
	UserType userType, float credit, std::string valability, bool isBlocked)
	: Client(id, last_name, name, email, parolaHash, userType, credit, valability, isBlocked)
{}
