#include <vector>
#include <iostream>
#include "functions.h"
#include "city.h"
#include "Individual.h"

// Вспомогательный для мутации метод (не доступен для обычного вызова)
void Individual::swap_cities(std::vector <city>& vec, int ind1, int ind2) {
    // По сути просто меняем местами элементы по определенным индексам 
    city temp = vec[ind1];
    vec[ind1] = vec[ind2];
    vec[ind2] = temp;
}

// Должен быть только конструктор с параметрами, поскольку не может быть особи без маршрута 
Individual::Individual(std::vector<city> route) : route(route), fitness(-1.0) {}

// Метод подсчета длины маршрута у определенной особи
double Individual::calculate_fitness() {
    fitness = 0.0;
    
    // Суммируем расстояние между каждым городом
    for (int i = 0; i < route.size() - 1; i++) {
        fitness += distance_between(route[i], route[i + 1]);
    }
    // Добавляем расстояние от последнего города до первого города
    fitness += distance_between(route.back(), route.front()); 
    return fitness;
}

// Метод, которая возвращает длину маршрута
double Individual::getFitness() {
    // Если значение не посчитано, то сначала считаем, а потом возвращаем
    if (fitness == -1) return calculate_fitness();
    return fitness;
}

// Метод, который возвращает сами маршруты
std::vector<city> Individual::getRoute() const {
    return route;
}

// Метод мутации (по сути обертка над функцией swap_cities)
void Individual::mutate(bool flag) {
    // Самостоятельно генерируем 2 индекса для мутации
    int ind1 = discrete_uniform(0, route.size() - 1);
    int ind2 = discrete_uniform(0, route.size() - 1);
    // Если индекс не тот же самый, то меняем элементы местами
    // Если отладочный флаг true, то еще и в консоль выводим информацию
    if (ind1 != ind2) {
        if (flag) std::cout << "Элементы по индексам " << ind1 + 1 << " и " << ind2 + 1 << " в результате мутаций были поменяны местами" << std::endl;
        swap_cities(route, ind1, ind2);
    }
}

// Метод скрещивания (по-хорошему нужно было бы его реализовать как дружественную функцию, так как в виде метода странно его использовать)
Individual Individual::crossover(Individual parent2, bool flag) {
    std::vector<city> childRoute;
    int start = discrete_uniform(0, route.size() - 3);
    int end = discrete_uniform(start, route.size() - 2);
    if (flag) {
        std::cout << "Родитель 1:" << std::endl;
        for (int i = 0; i < route.size(); ++i) {
            if (i == start) std::cout << "|";
            if (i != 0) std::cout << " ";
            std::cout << route[i] << " ";
            if (i == end) std::cout << "|";
        }

        std::cout << std::endl << "Родитель 2:" << std::endl;
        for (int i = 0; i < parent2.route.size(); ++i) {
            if (i == start) std::cout << "|";
            if (i != 0) std::cout << " ";
            std::cout << parent2.route[i] << " ";
            if (i == end) std::cout << "|";
        }
        std::cout << std::endl;
    }
    for (int i = start; i <= end; i++) {
        childRoute.push_back(route[i]);
    }
    for (int i = 0; i < parent2.getRoute().size(); i++) {
        bool found = false;
        for (int j = 0; j < childRoute.size(); j++) {
            if (parent2.getRoute()[i] == childRoute[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            childRoute.push_back(parent2.getRoute()[i]);
        }
    }
    if (flag) {
        std::cout << "Результат скрещивания:" << std::endl;
        for (int i = 0; i < childRoute.size(); ++i) {
            if (i == start) std::cout << "|";
            if (i != 0) std::cout << " ";
            std::cout << childRoute[i] << " ";
            if (i == end) std::cout << "|";
        }
        std::cout << std::endl << std::endl;
    }

    return Individual(childRoute);
}