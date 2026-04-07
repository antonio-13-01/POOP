#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Logger
{
private:
	std::string _file;
	std::ofstream _logStream;
public:
	static Logger& getInstance();
	void log(const std::string& message);

private:
	Logger();
	~Logger();

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
};

