#include "Logger.h"
#include <map>
#include <iostream>

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

std::vector<std::string> Logger::getUnreadNotificationsFor(const std::string& userId)
{
    std::vector<std::string> unread;

    std::string notifTag = "[NOTIF:" + userId + "]";

    auto& delivered = _deliveredNotifications[userId];

    for (size_t i = 0; i < _logs.size(); ++i) {
        const auto& entry = _logs[i];
        if (entry.find(notifTag) != std::string::npos) {
            if (delivered.find(i) == delivered.end()) {
                unread.push_back(entry);
                delivered.insert(i);
            }
        }
    }

    return unread;
}

void Logger::markNotificationsRead(const std::string& userId)
{
    auto& delivered = _deliveredNotifications[userId];
    std::string notifTag = "[NOTIF:" + userId + "]";

    for (size_t i = 0; i < _logs.size(); ++i) {
        if (_logs[i].find(notifTag) != std::string::npos) {
            delivered.insert(i);
        }
    }
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