#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Logger
{
private:
    std::string _file;
    std::ofstream _logStream;           //adaugate pt notificari
    std::vector<std::string> _logs;

public:
    static Logger& getInstance();
    void log(const std::string& message);
    std::vector<std::string> getLogsFor(const std::string& keyword) const;

private:
    Logger();
    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};