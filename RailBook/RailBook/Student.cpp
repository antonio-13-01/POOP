#include "Student.h"

Student::Student(int id, const std::string last_name, 
	const std::string name, const std::string email, const std::string parolaHash,
	UserType userType, float credit, std::string valability, bool isBlocked)
	:Client(id, last_name, name, email, parolaHash, userType, credit, valability, isBlocked)
{
}
void Student::displayUser() const {
	AUser::displayUser();
	std::cout << " | Tip: STUDENT | Credit: " << _credit << " RON | Valabilitate: " << _valability << std::endl;
}