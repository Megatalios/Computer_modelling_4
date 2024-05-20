#pragma once
#include <iostream>

// Функция генерации непрерывного случайного числа в диапазоне [0, 1]
double default_uniform();

// Функция генерации непрерывного случайного числа в диапазоне [a, b]
double continuous_uniform(double a, double b);

// Функция целочисленной генерации числа в диапазоне [a, b]
int discrete_uniform(int a, int b);
