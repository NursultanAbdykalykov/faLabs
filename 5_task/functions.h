#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

// Проверяет, является ли строка представлением числа с плавающей запятой
int isFloat(char* x);

// Вычисляет факториал с использованием формулы Стирлинга для больших n
double stirlingFormula(int n);

// Вычисляет факториал числа n
double fact(const int n);

// Возвращает a в степени pw
double numPow(const double a, const int pw);

// Вычисляет сумму ряда A
double sumA(double x, double eps);

// Вычисляет сумму ряда B
double sumB(double x, double eps);

// Вычисляет сумму ряда C
double sumC(double x, double eps);

// Вычисляет сумму ряда D
double sumD(double x, double eps);

#endif // FUNCTIONS_H