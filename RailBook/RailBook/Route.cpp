#include "Route.h"

Route::Route(int id, const std::string& name, int direction)
{
	_id = id;
	_name = name;
	_direction = direction;
}

int Route::getId() const
{
	return _id;
}

std::string Route::getName() const
{
	return _name;
}

std::vector<StopInfo*> Route::getStops() const
{
	return _stops;
}

void Route::addStop(StopInfo* stop)
{
	_stops.push_back(stop);
}

void Route::displayRoute() const {
    std::cout << "Ruta: " << _name << " (ID: " << _id << ")" << std::endl;
    const std::vector<StopInfo*>& stops = getStops();

    if (stops.empty()) {
        std::cout << "   [INFO] Aceasta ruta nu are statii definite." << std::endl;
    }
    else {
        for (const auto* stop : stops) {
            std::cout << "      Statie ID: " << stop->getStationId()
                << " | Sosire: " << stop->getArrivalMinutes() << " min" << std::endl;
        }
    }
}
