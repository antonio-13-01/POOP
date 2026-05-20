#pragma once
#include <stdexcept>
#include <string>

// Exceptie pentru cand locul este deja luat
class SeatTakenException : public std::runtime_error {
public:
    SeatTakenException(const std::string& message)
        : std::runtime_error(message) {}
};

// Exceptie pentru cand utilizatorul nu are suficient credit 
class InsufficientFundsException : public std::runtime_error {
public:
    InsufficientFundsException(const std::string& message)
        : std::runtime_error(message) {}
};

// Exceptie generala pentru baza de date (optional, dar util)
class DatabaseTransactionException : public std::runtime_error {
public:
    DatabaseTransactionException(const std::string& message)
        : std::runtime_error(message) {}
};