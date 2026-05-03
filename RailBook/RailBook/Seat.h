#pragma once
#include <string>

class Seat {
private:
    int _id;
    int _number;
    float _fare;
    int _wagon_id;

public:
    Seat(int id, int number, float fare, int wagon_id)
        : _id(id), _number(number), _fare(fare), _wagon_id(wagon_id) {
    }

    int getId() const { return _id; }
    int getNumber() const { return _number; }
    float getFare() const { return _fare; }
};