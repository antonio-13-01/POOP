#include "Station.h"

Station::Station(int id, const std::string& city, const std::string& county)
	: _id(id), _city(city), _county(county)
{
}

int Station::getId() const
{
	return _id;
}

std::string Station::getCity() const
{
	return _city;
}

std::string Station::getCounty() const
{
	return _county;
}
