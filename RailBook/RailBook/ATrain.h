#pragma once
#include "ITrain.h"
class ATrain :
    public ITrain
{
private:
    int _id;
    std::string _number;
	int _route_id;
	TrainType _type;
	TrainStatus _status;
	int _number_of_wagons;
	float _fare_per_km;
	std::vector<Wagon*> _wagons;

public:
	ATrain(int id, const std::string& number, int route_id, TrainType type, TrainStatus status, int number_of_wagons, float fare_per_km);
	

	int getId() const override;
	std::string getNumber() const override;
	int getRouteId() const override;
	TrainType getType() const override;
	TrainStatus getStatus() const override;
	int getNumberOfWagons() const override;
	float getFarePerKm() const override;
	std::vector<Wagon*> getWagons() const override;

	//add wagons to the train

	void addWagon(Wagon* wagon) override;
};

