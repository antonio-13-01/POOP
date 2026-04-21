#include "Operator.h"

Operator::Operator(int id, const std::string& last_name, const std::string& name, const std::string& email, const std::string& parolaHash, UserType userType, bool isBlocked)
	:AUser(id, last_name, name, email, parolaHash, userType,isBlocked) {
}
