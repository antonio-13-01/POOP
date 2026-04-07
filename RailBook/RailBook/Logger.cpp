#include "Logger.h"

Logger& Logger::getInstance()
{
	static Logger instance;
	return instance;
}

void Logger::log(const std::string& message)
{
	_logStream << message << std::endl;
}

Logger::Logger()
{
	_file = "RailBookLog";

	_logStream.open(_file, std::ios::app);
}

Logger::~Logger()
{
	_logStream.close();
}
