#include <iostream>

// ������� ��������� ������������ ���������� ����� � ��������� [0, 1]
double default_uniform() { 
    return ((double)rand()) / RAND_MAX; 
}

// ������� ��������� ������������ ���������� ����� � ��������� [a, b]
double continuous_uniform(double a, double b) {
    double u = default_uniform();
    return a + (b - a) * u;
}

// ������� ������������� ��������� ����� � ��������� [a, b]
int discrete_uniform(int a, int b) { 
    return (rand() % (b - a)) + a; 
}