#pragma once
#include "AUser.h"
class Client :
    public AUser
{
public:
	enum class ClientType
	{ Adult, Pensionar, Student, Elev };
	
private:
	std::string _idDiscount;
	float _credit;
	std::string _valability;
	ClientType _type;
public:
	
	Client(int id, const std::string& last_name, const std::string& name, const std::string& email, const std::string& parolaHash, UserType userType, float credit, std:: string valability, std::string idDiscount);
	
	//de ce faci asa aici? Nu era vorba ca idDiscount sa fie dat de legitimatie? 
	// Si apoi sa verificam 
	//in baza de date daca aexista vreun client cu acel id?
	//nu generam noi id-uri de discount, 
	//ci verificam daca clientul are un id de discount valid in baza de date
	std::string getIdDiscount() const;
	ClientType getClientType() const;
};

