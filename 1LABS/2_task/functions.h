#include <stdbool.h>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Прототипы функций

// Вычисление e с использованием предельного определения
long double eLimit(double epsilon);

// Вычисление e с использованием рядового определения
long double eSeries(double epsilon);

// Вычисление e с использованием уравнительного определения
long double eEquation(double epsilon);

// Вычисление pi с использованием предельного определения
long double piLimit(double epsilon);

// Вычисление pi с использованием рядового определения
long double piSeries(double epsilon);

// Вычисление pi с использованием уравнительного определения
long double piEquation(double epsilon);

// Вычисление ln(2) с использованием предельного определения
long double ln2Limit(double epsilon);

// Вычисление ln(2) с использованием рядового определения
long double ln2Series(double epsilon);

// Вычисление ln(2) с использованием уравнительного определения
long double ln2Equation(double epsilon);

// Вычисление sqrt(2) с использованием предельного определения
long double sqrt2Limit(double epsilon);

// Вычисление sqrt(2) с использованием рядового определения
long double sqrt2Series(double epsilon);

// Вычисление sqrt(2) с использованием уравнительного определения
long double sqrt2Equation(double epsilon);

// Вычисление гамма-функции с использованием предельного определения
long double gammaLimit(double epsilon);

// Вычисление гамма-функции с использованием рядового определения
long double gammaSeries(double epsilon);

// Проверка, является ли число простым
bool isPrime(int n);

// Расчёт произведения для вычисления гамма-функции
double prodResult(int t);

// Вычисление гамма-функции с использованием уравнительного определения
long double gammaEquation(double epsilon);

// Пользовательская функция преобразования строки в число с плавающей точкой
double myStrtod(const char* str, char** end);

#endif // FUNCTIONS_H