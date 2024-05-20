#pragma once
#include <vector>
#include <iostream>
#include "functions.h"
#include "city.h"

class Individual {
private:
    std::vector<city> route;
    double fitness;

    void swap_cities(std::vector <city>& vec, int ind1, int ind2);
public:
    Individual(std::vector<city> route);

    double calculate_fitness();

    double getFitness();

    std::vector<city> getRoute() const;

    void mutate(bool flag);

    Individual crossover(Individual parent2, bool flag);
};
