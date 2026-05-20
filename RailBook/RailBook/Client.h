#pragma once
#include "AUser.h"
#include "DatabaseManager.h"
#include "nanodbc.h"

class Client : public AUser
{
public:
	enum class ClientType
	{
		Adult, Pensionar, Student, Elev
	};

protected:
	float _credit;
	std::string _valability;
	ClientType _type;

public:
	Client(int id, const std::string last_name, const std::string name,
		const std::string email, const std::string parolaHash,
		UserType userType, float credit, std::string valability,
		bool isBlocked);

	int getId() const;
	std::string getLastName() const;
	std::string getName() const;
	std::string getEmail() const;
	ClientType getClientType() const;
	float getCredit() const;
	std::string getValability() const;
	void setCredit(float credit);
	void setClientType(ClientType clientType);
	void afisareSold() const;
	void afisareDetaliiProfil() const;
	bool editareProfil(const std::string& newLastName,
		const std::string& newName,
		const std::string& newPassword);

	void vizualizareRezervari() const;
	bool anulareRezervare(int ticket_id);
	void afisareNotificari() const;
};