#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <map>

class Logger
{
public:
    static Logger& getInstance();

    void log(const std::string& message);

    std::vector<std::string> getLogsFor(const std::string& keyword) const;

    std::vector<std::string> getUnreadNotificationsFor(const std::string& userId);

    void markNotificationsRead(const std::string& userId);

private:
    Logger();
    ~Logger();

    std::string _file;
    std::ofstream _logStream;
    std::vector<std::string> _logs;

    // Set cu indicii log-urilor deja livrate, per userId
    // Cheie: userId, Valoare: set de indici din _logs deja notificati
    std::map<std::string, std::set<size_t>> _deliveredNotifications;
};