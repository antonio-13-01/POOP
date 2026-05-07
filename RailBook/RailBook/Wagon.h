#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Seat.h"
class Wagon
{
public:
	enum class WagonType { Clasa1, Clasa2, Cuseta };
private:
	int _id;
	int _number;
	int _capacity;
	WagonType _type;
	int _train_id;
	std::vector<Seat*> _seats;

public:
	Wagon(int id, int number, int capacity, WagonType type, int train_id);
	
	int getId() const;
	int getNumber() const;
	int getCapacity() const;
	WagonType getType() const;
	int getTrainId() const;

	void addSeat(Seat* seat);

	~Wagon();
};

