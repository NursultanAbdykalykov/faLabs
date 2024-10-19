#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Прототипы функций

// Проверка, является ли строка допустимым числом с плавающей запятой
int isFloat(char* x);

// Функция A: вычисляет log(1 + x) / x
double funcA(double x);

// Функция B: вычисляет exp(-x^2 / 2)
double funcB(double x);

// Функция C: вычисляет -log(1 - x)
double funcC(double x);

// Функция D: вычисляет x^x
double funcD(double x);

// Вычисление интеграла заданной функции с заданной точностью
double integral(double (*func)(double), double eps);

#endif // FUNCTIONS_H