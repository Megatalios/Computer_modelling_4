#include <iostream>
#include <vector>

// Функция генерации непрерывного случайного числа в диапазоне [0, 1]
double default_uniform() {
    return ((double)rand()) / RAND_MAX;
}

double continuous_uniform(double a, double b) {
    srand(time(NULL));
    double u = default_uniform();
    return a + (b - a) * u;
}

int discrete_uniform(int a, int b) {
    return rand() % b + a;
}

class city {
private:
    double x, y, z;
public:
    city() {
        x = 0; y = 0; z = 0;
    }
    city(double x_, double y_, double z_) {
        this->x = x_;
        this->y = y_;
        this->z = z_;
    }
    city(city& a) {
        this->x = a.x;
        this->y = a.y;
        this->z = a.z;
    }

    void set(double x_, double y_, double z_) {
        this->x = x_;
        this->y = y_;
        this->z = z_;
    }

    double distance_to_city(city& some_city) {
        return std::sqrt((this->x - some_city.x)*(this->x - some_city.x) + (this->y - some_city.y) * (this->y - some_city.y) + (this->z - some_city.z) * (this->z - some_city.z));
    }

    city operator=(const city& a) {
        this->x = a.x;
        this->y = a.y;
        this->z = a.z;
        return *this;
    }

    friend double distance_between(city& a, city& b) {
        return std::sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
    }
};

void shuffle(std::vector <city>& vec, int ind1, int ind2) {
    city temp = vec[ind1];
    vec[ind1] = vec[ind2];
    vec[ind2] = temp;
}

int main() {
}