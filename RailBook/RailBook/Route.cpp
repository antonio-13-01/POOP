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
