#pragma once
#include <iostream>
#include <string>

class DatabaseManager
{
private:

public:
	static DatabaseManager& getInstance();

private:

	DatabaseManager() = default;
	~DatabaseManager() = default;
	DatabaseManager(const DatabaseManager&) = delete;
	DatabaseManager& operator=(const DatabaseManager&) = delete;	
};

