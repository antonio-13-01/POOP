#pragma once
#include "ITrain.h"
#include <string>

class TrainFactory {
private:
	static ITrain::TrainType stringToTrainType(const std::string& typeStr);
	static ITrain::TrainStatus stringToTrainStatus(const std::string& statusStr);
	static Wagon::WagonType stringToWagonType(const std::string& typeStr);	
public:
    
    // Indiferent dacă e Regio sau InterCity, 
    // funcția va returna tipul corect.
    static ITrain* LoadTrainFromDB(int id);
	static void LoadWagons(int train_id, ITrain* train);
	static void LoadSeats(int wagon_id, Wagon* wagon);
	static std::vector<int> GetAllTrainIds();
};