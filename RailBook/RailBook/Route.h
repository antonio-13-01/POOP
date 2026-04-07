#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "StopInfo.h"

class Route
{
private:
	int _id;
	std::string _name;
	std::vector<StopInfo*> _stops;
public:
	Route(int id, const std::string& name);
	
	int getId() const;
	std::string getName() const;
	std::vector<StopInfo*> getStops() const;
	//add stops to the route
};

