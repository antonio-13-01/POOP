#pragma once
#include <iostream>
#include <string>

class Station
{
private:
	int _id;
	std::string _name;
	std::string _city;
	std::string _county;

public:
	Station(int id, const std::string& name, const std::string& city, const std::string& county);
	
	
	int getId() const;
	std::string getName() const;
	std::string getCity() const;
	std::string getCounty() const;
};


