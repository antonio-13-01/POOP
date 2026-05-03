#include "StopInfo.h"
#include "Station.h"


StopInfo::StopInfo(int id, int route_id, int station_id, int arrival_minutes, int departure_minutes)
{
	_id = id;
	_route_id = route_id;
	_station_id = station_id;
	_arrival_minutes = arrival_minutes;
	_departure_minutes = departure_minutes;
	_station = nullptr;
}

int StopInfo::getId() const
{
	return _id;
}

int StopInfo::getRouteId() const
{
	return _route_id;
}

int StopInfo::getStationId() const
{
	return _station_id;
}

int StopInfo::getArrivalMinutes() const
{
	return _arrival_minutes;
}

int StopInfo::getDepartureMinutes() const
{
	return _departure_minutes;
}

void StopInfo::displayStop() const {
	if (_station != nullptr) {
		std::cout << "   - Statie: " << std::left << _station->getName()
			<< " | Oras: "  << _station->getCity()
			<< " | Judet: " << _station->getCounty()
			<< " | Sosire: " << _arrival_minutes << " min" << std::endl;
	}
	else {
		std::cout << "   - [EROARE] Legatura statie inexistenta pentru ID: " << _station_id << std::endl;
	}
}