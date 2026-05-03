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
	int _direction; //0 for forward, 1 for backward
	std::vector<StopInfo*> _stops;
public:
	Route(int id, const std::string& name, int direction);
	
	int getId() const;
	std::string getName() const;
	std::vector<StopInfo*> getStops() const;

	void addStop(StopInfo* stop);

	void displayRoute() const;

	//add stops to the route
};

