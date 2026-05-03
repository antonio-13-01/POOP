#include "ATrain.h"

ATrain::ATrain(int id, const std::string& number, int route_id, TrainType type, TrainStatus status, int number_of_wagons, float fare_per_km)
{
	_id = id;
	_number = number;	
	_route_id = route_id;	
	_type = type;
	_status = status;
	_number_of_wagons = number_of_wagons;	
	_fare_per_km = fare_per_km;
}

int ATrain::getId() const
{
	return _id;
}

std::string ATrain::getNumber() const
{
	return _number;
}

int ATrain::getRouteId() const
{
	return _route_id;
}

ITrain::TrainType ATrain::getType() const
{
	return _type;
}

ITrain::TrainStatus ATrain::getStatus() const
{
	return _status;
}

int ATrain::getNumberOfWagons() const
{
	return _number_of_wagons;
}

float ATrain::getFarePerKm() const
{
	return _fare_per_km;
}

std::vector<Wagon*> ATrain::getWagons() const
{
	return _wagons;
}

void ATrain::displayInfo() const
{
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "[TREN ID: " << _id << "] Numar: " << _number << std::endl;
	std::cout << "Ruta ID: " << _route_id << " | Tarif/km: " << _fare_per_km << " RON" << std::endl;
	std::cout << "Vagoane: " << _wagons.size() << " din " << _number_of_wagons << " planificate." << std::endl;

	if (!_wagons.empty()) {
		std::cout << "  Detalii vagoane:" << std::endl;
		for (auto* w : _wagons) {
			std::cout << "    - Vagon ID: " << w->getId() << " Tip: " << (int)w->getType() << std::endl;
		}
	}
}

void ATrain::addWagon(Wagon* wagon)
{
	_wagons.push_back(wagon);
}
