#pragma once
#include "ATrain.h"
class InterCity :
    public ATrain
{
public:
    	InterCity(int id, const std::string& number, int route_id, TrainType type, TrainStatus status, int number_of_wagons, float fare_per_km)
        : ATrain(id, number, route_id, type, status, number_of_wagons, fare_per_km) {}
};

