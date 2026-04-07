#pragma once
#include <iostream>
#include <string>

class StopInfo
{
private:
	int _id;
	int _route_id;
	int _station_id;
	int _arrival_minutes;
	int _departure_minutes;

public:
	StopInfo(int id, int route_id, int station_id, int arrival_minutes, int departure_minutes);
	
	
	int getId() const;
	int getRouteId() const;
	int getStationId() const;
	int getArrivalMinutes() const;
	int getDepartureMinutes() const;
};

