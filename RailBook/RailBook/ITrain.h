#pragma once
#include <iostream>
#include <string>
#include <vector>
#include"Wagon.h"

class ITrain
{
public:
    enum class TrainType { Regio, InterRegio, InterCity };

    enum class TrainStatus { Activ, Anulat };

	virtual int getId() const = 0;
	virtual std::string getNumber() const = 0;
	virtual int getRouteId() const = 0;
	virtual TrainType getType() const = 0;
	virtual TrainStatus getStatus() const = 0;	
	virtual int getNumberOfWagons() const = 0;
	virtual float getFarePerKm() const = 0;
	virtual std::vector<Wagon*> getWagons() const = 0;
	
};

