#include <string>
#include <algorithm>
#include <iostream>
#include "functions.h"
#include "city.h"

    /* Конструкторы */

    // По умолчанию
    city::city() : x(0), y(0), z(0), name("unnamed") {}
    // С параметрами (без имени)
    city::city(double x_, double y_, double z_) : x(x_), y(y_), z(z_), name("unnamed") {}
    // С параметрами (с именем)
    city::city(std::string name_, double x_, double y_, double z_) : x(x_), y(y_), z(z_), name(name_) {}
    // Конструктор копирования
    city::city(const city& a) : x(a.x), y(a.y), z(a.z), name(a.name) {}

    // Методы для возвращения внутренних приватных полей
    double city::get_x() { return this->x; }
    double city::get_y() { return this->y; }
    double city::get_z() { return this->z; }
    std::string city:: get_name() const { return name; }

    // Метод для задания координат
    void city::set(double x_, double y_, double z_) {
        this->x = x_;
        this->y = y_;
        this->z = z_;
    }

    // Метод для измерения расстояния до определенного города
    double city::distance_to_city(city& some_city) {
        return std::sqrt((this->x - some_city.x) * (this->x - some_city.x) + (this->y - some_city.y) * (this->y - some_city.y) + (this->z - some_city.z) * (this->z - some_city.z));
    }

    // Функция для измерения расстояния до определенного города
    double distance_between(city& a, city& b) {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
    }

    // Оператор присваивания
    city city::operator=(const city& a) {
        this->name = a.name;
        this->x = a.x;
        this->y = a.y;
        this->z = a.z;
        return *this;
    }

    // Оператор равенства
    bool operator==(const city& a, const city& b) {
        return (b.x == a.x && b.y == a.y && b.z == a.z);
    }

    // Потоковый оператор вывода 
    std::ostream& operator << (std::ostream& os, const city& some_city) { return os << some_city.get_name(); }


