#include "Admin.h"

Admin::Admin(int id, const std::string& nume, const std::string& prenume, const std::string& email, const std::string& parolaHash, UserType userType, int idAdmin) : AUtilizator(id, nume, prenume, email, parolaHash, userType), _idAdmin(id)
{
}

int Admin::getIdAdmin() const
{
    return _idAdmin;
}
