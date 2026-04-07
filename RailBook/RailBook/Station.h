#pragma once
#include <iostream>
#include <string>

class Station
{
private:
	int _id;
	std::string _city;
	std::string _county;

public:
	Station(int id, const std::string& city, const std::string& county);
	
	
	int getId() const;
	std::string getCity() const;
	std::string getCounty() const;
};


