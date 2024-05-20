#pragma once
#include <string>
#include <algorithm>
#include "functions.h"

// Класс для города (содержит координаты и название/номер города)
class city {
private:
    std::string name;
    double x, y, z;
public:
    city();
    city(double x_, double y_, double z_);
    city(std::string name_, double x_, double y_, double z_);
    city(const city& a);

    double get_x();
    double get_y();
    double get_z();
    std::string get_name() const;
    void set(double x_, double y_, double z_);
    double distance_to_city(city& some_city);
    friend double distance_between(city& a, city& b);

    city operator=(const city& a);
    friend bool operator==(const city& a, const city& b);  

    friend std::ostream& operator << (std::ostream& os, const city& some_city);

};
