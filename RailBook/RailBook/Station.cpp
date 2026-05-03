#include "Station.h"

Station::Station(int id, const std::string& name, const std::string& city, const std::string& county)
	: _id(id), _name(name), _city(city), _county(county)
{
}

int Station::getId() const
{
	return _id;
}

std::string Station::getName() const
{
	return _name;
}

std::string Station::getCity() const
{
	return _city;
}

std::string Station::getCounty() const
{
	return _county;
}
