#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

#include "functions.h" // Функции генерации случайных чисел
#include "Individual.h" // Модуль, описывающий методы и интерфейс работы с особью популяции
#include "city.h" // Модуль, описывающий методы и интерфейс работы с городом


int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");
    std::cout << "Выберите количество данных для работы (5, 10, 25, 50, 75, 100): ";
    // Количество городов
    int numCities;
    std::cin >> numCities;

    // Если написано неверное число, то невозможно будет открыть файл - программа завершится 
    std::ifstream file(std::to_string(numCities) + ".txt");
    if (!file.is_open()) return 0;

    // Если же данные введены допустимые, то файл открывается, а алгоритм начинает свою работу
    std::vector<city> cities;
    
    // В файле в каждой строке данные в следующем виде:
    // номер_города координата_х координата_у координата_z
    // Считываем координаты каждого города, создаем объекты city с данными свойствами
    for (int i = 0; i < numCities; i++) {
        std::string id;
        double x, y, z;
        file >> id >> x >> y >> z;
        cities.push_back(city(id, x, y, z));
    }
    // Закрываем файл
    file.close();

    // Размер популяции (сколько различных решений будет храниться в нашем, можно сказать, буфере
    int populationSize = 10;
    // Количество поколений (сколько итераций алгоритма будет совершено)
    int generations = 50;
    // Вероятность мутации (может быть любое число от 0 до 1)
    double mutationRate = 0.5;
    // Эта переменная отвечает за отладочный вывод (в случае ненадобности вывод можно убрать для повышения быстродействия)
    bool is_output_data = false;

    // Основная наша популяция (Individual - в нашем случае список городов или же один представитель популяции)
    // Создается список особей
    std::vector<Individual> population;

    // Цикл 
    for (int i = 0; i < populationSize; i++) {
        // Берем наш изначальный список городов, копируем его, а затем случайным образом перемешиваем
        // Таким образом создаем маршрут
        std::vector<city> route = cities;
        std::random_shuffle(route.begin(), route.end());

        // Заносим наш маршрут в список популяции
        population.push_back(Individual(route));
    }

    // Основной цикл программы
    for (int i = 0; i < generations; i++) {
        // Отладочный вывод при установке соответствующего флажка
        if (is_output_data) {
            std::cout << "Популяция:" << std::endl;
            for (int j = 0; j < population.size(); ++j) {
                for (int k = 0; k < numCities; ++k) {
                    std::cout << population[j].getRoute()[k] << " ";
                }
                std::cout << "(" << population[j].getFitness() << ")";
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;

        int num1 = discrete_uniform(0, populationSize - 1);
        int num2 = discrete_uniform(0, populationSize - 1);
        while (num1 == num2) num2 = discrete_uniform(0, populationSize - 1);

        // Выбор двух родителей для дальнейшего их скрещивания
        Individual parent1 = population[num1];
        Individual parent2 = population[num2];
        // Вызов метода скрещивания 
        Individual child = parent1.crossover(parent2, is_output_data);
        // Если случайное число меньше вероятности мутации, то вызываем метод мутации у ребенка
        if (continuous_uniform(0, 1) < mutationRate) {
            child.mutate(is_output_data);
        }
        
        // Заносим результат в список начальной популяции
        population.push_back(child);

        // Сортируем список по возрастанию по лямбда функции, которая сравнивает длины элементов
        std::sort(population.begin(), population.end(), [](Individual a, Individual b) { return a.getFitness() < b.getFitness();});
        // Удаляем маршрут с наибольшей длиной
        population.pop_back();
    }

    // Присваиваем этой переменной маршрут с наименьшей длиной
    Individual bestIndividual = population[0];

    // Информация о лучшем маршруте
    std::cout << "Лучший маршрут: ";
    for (int i = 0; i < bestIndividual.getRoute().size(); i++) {
        std::cout << bestIndividual.getRoute()[i].get_name() << ", ";
    }
    std::cout << "\b\b    ";
    std::cout << std::endl;
    std::cout << "Длина лучшего маршрута: " << bestIndividual.getFitness() << std::endl;

    return 0;

}