#include "Wagon.h"

Wagon::Wagon(int id, int number, int capacity, WagonType type, int train_id)
{
	_id = id;	
	_capacity = capacity;
	_number = number;	
	_type = type;
	_train_id = train_id;	
}

int Wagon::getId() const
{
	return _id;
}

int Wagon::getNumber() const
{
	return _number;
}

int Wagon::getCapacity() const
{
	return _capacity;
}

Wagon::WagonType Wagon::getType() const
{
	return _type;
}

int Wagon::getTrainId() const
{
	return _train_id;
}

void Wagon::addSeat(Seat* seat) {
	_seats.push_back(seat);
}

Wagon::~Wagon() {
	for (Seat* seat : _seats) {
		delete seat;
	}
}
