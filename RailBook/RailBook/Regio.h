#pragma once
#include "ATrain.h"

class Regio : public ATrain
{
public:
	Regio(int id, const std::string& number, int route_id, TrainType type, TrainStatus status, int number_of_wagons, float fare_per_km)
		: ATrain(id, number, route_id, type, status, number_of_wagons, fare_per_km) {
	}
};

