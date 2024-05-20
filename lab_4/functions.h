#pragma once
#include <iostream>

// ������� ��������� ������������ ���������� ����� � ��������� [0, 1]
double default_uniform();

// ������� ��������� ������������ ���������� ����� � ��������� [a, b]
double continuous_uniform(double a, double b);

// ������� ������������� ��������� ����� � ��������� [a, b]
int discrete_uniform(int a, int b);
