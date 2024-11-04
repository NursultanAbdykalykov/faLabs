#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Сравнивает две строки и возвращает 1, если они равны, иначе 0.
int compareStrings(const char* s1, const char* s2);

// Проверяет, является ли строка допустимым вещественным числом.
int isFloat(char* x);

// Проверяет, является ли строка допустимым целым числом.
int isInt(char* x);

// Решает квадратное уравнение ax^2 + bx + c = 0 и выводит корни.
int quadEq(const float eps, const float a, const float b, const float c);

// Проверяет, делится ли a на b без остатка.
int isDivBy(const int a, const int b);

// Проверяет, является ли треугольник с длинами сторон a, b и c прямоугольным.
int rightTriangle(const float eps, const float a, const float b, const float c);

// Вызывает функцию решения квадратного уравнения для различных комбинаций коэффициентов.
int flagQ(const float eps, const float a, const float b, const float c);

// Проверяет делимость числа a на число b и выводит результат.
int flagM(const int a, const int b);

// Проверяет, является ли треугольник прямоугольным и выводит результат.
int flagT(const float eps, const float a, const float b, const float c);

#endif // FUNCTIONS_H