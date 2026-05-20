#include "Logger.h"

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::log(const std::string& message)
{
    _logStream << message << std::endl;
    _logs.push_back(message);
}

std::vector<std::string> Logger::getLogsFor(const std::string& keyword) const
{
    std::vector<std::string> result;
    for (const auto& entry : _logs) {
        if (entry.find(keyword) != std::string::npos) {
            result.push_back(entry);
        }
    }
    return result;
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