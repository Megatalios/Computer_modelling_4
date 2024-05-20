#include <vector>
#include <iostream>
#include "functions.h"
#include "city.h"
#include "Individual.h"

// ��������������� ��� ������� ����� (�� �������� ��� �������� ������)
void Individual::swap_cities(std::vector <city>& vec, int ind1, int ind2) {
    // �� ���� ������ ������ ������� �������� �� ������������ �������� 
    city temp = vec[ind1];
    vec[ind1] = vec[ind2];
    vec[ind2] = temp;
}

// ������ ���� ������ ����������� � �����������, ��������� �� ����� ���� ����� ��� �������� 
Individual::Individual(std::vector<city> route) : route(route), fitness(-1.0) {}

// ����� �������� ����� �������� � ������������ �����
double Individual::calculate_fitness() {
    fitness = 0.0;
    
    // ��������� ���������� ����� ������ �������
    for (int i = 0; i < route.size() - 1; i++) {
        fitness += distance_between(route[i], route[i + 1]);
    }
    // ��������� ���������� �� ���������� ������ �� ������� ������
    fitness += distance_between(route.back(), route.front()); 
    return fitness;
}

// �����, ������� ���������� ����� ��������
double Individual::getFitness() {
    // ���� �������� �� ���������, �� ������� �������, � ����� ����������
    if (fitness == -1) return calculate_fitness();
    return fitness;
}

// �����, ������� ���������� ���� ��������
std::vector<city> Individual::getRoute() const {
    return route;
}

// ����� ������� (�� ���� ������� ��� �������� swap_cities)
void Individual::mutate(bool flag) {
    // �������������� ���������� 2 ������� ��� �������
    int ind1 = discrete_uniform(0, route.size() - 1);
    int ind2 = discrete_uniform(0, route.size() - 1);
    // ���� ������ �� ��� �� �����, �� ������ �������� �������
    // ���� ���������� ���� true, �� ��� � � ������� ������� ����������
    if (ind1 != ind2) {
        if (flag) std::cout << "�������� �� �������� " << ind1 + 1 << " � " << ind2 + 1 << " � ���������� ������� ���� �������� �������" << std::endl;
        swap_cities(route, ind1, ind2);
    }
}

// ����� ����������� (��-�������� ����� ���� �� ��� ����������� ��� ������������� �������, ��� ��� � ���� ������ ������� ��� ������������)
Individual Individual::crossover(Individual parent2, bool flag) {
    std::vector<city> childRoute;
    int start = discrete_uniform(0, route.size() - 3);
    int end = discrete_uniform(start, route.size() - 2);
    if (flag) {
        std::cout << "�������� 1:" << std::endl;
        for (int i = 0; i < route.size(); ++i) {
            if (i == start) std::cout << "|";
            if (i != 0) std::cout << " ";
            std::cout << route[i] << " ";
            if (i == end) std::cout << "|";
        }

        std::cout << std::endl << "�������� 2:" << std::endl;
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
        std::cout << "��������� �����������:" << std::endl;
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