#include "Operator.h"

Operator::Operator(int id, const std::string& nume, const std::string& prenume, const std::string& email, const std::string& parolaHash, UserType userType, int idOperator)
	: AUtilizator(id, nume, prenume, email, parolaHash, userType), _idOperator(idOperator)
{
}

int Operator::getIdOperator() const
{
	return _idOperator;
}

