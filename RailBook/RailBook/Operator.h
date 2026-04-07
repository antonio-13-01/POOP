#pragma once
#include "AUtilizator.h"
class Operator :
    public AUtilizator
{
private:
	int _idOperator;
public:
	Operator(int id, const std::string& nume, const std::string& prenume, const std::string& email, const std::string& parolaHash, UserType userType, int idOperator);
	int getIdOperator() const;
	
};

