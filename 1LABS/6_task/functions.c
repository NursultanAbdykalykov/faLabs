#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "functions.h"

// Проверка, является ли строка допустимым числом с плавающей запятой
int isFloat(char* x) {
    bool numsBeforeDot = false;
    bool numsAfterDot = false;
    bool hasDot = false;
    
    for (int i = 0; x[i] != '\0'; i++) {
        if (x[0] == '-') {
            continue;
        }
        if (!((x[i] - '0' >= 0 && x[i] - '0' <= 9) || x[i] == '.')) {  
            return 0;
        }
        if ((x[i] - '0' >= 0 && x[i] - '0' <= 9 && !hasDot)) {  
            numsBeforeDot = true;
        }
        if ((x[i] - '0' >= 0 && x[i] - '0' <= 9 && hasDot)) {  
            numsAfterDot = true;
        }
        if (x[i] == '.' && !numsBeforeDot) {  
            return 0;
        }
        if (x[i] == '.' && hasDot) {  
            return 0;
        }
        if (x[i] == '.' && !hasDot) {  
            hasDot = true;
        }
    }
    
    if (hasDot && !numsAfterDot) {  
        return 0;
    }

    if (numsBeforeDot && !hasDot && !numsAfterDot) {  
        return 1;
    }
    
    return 1;
}

// Функция A
double funcA(double x) {
    if (x == 0) {
        return 0.0;
    }
    return log(1 + x) / x;
}

// Функция B
double funcB(double x) {
    return exp(-x * x / 2);
}

// Функция C
double funcC(double x) {
    if (x == 1) {
        return 0.0;
    }  
    return -log(1 - x);
}

// Функция D
double funcD(double x) {
    return pow(x, x);
}

// Вычисление интеграла с использованием метода трапеций
double integral(double (*func)(double), double eps) {
    double a = 0.0, b = 1.0, n = 2.0;
    double prevSum = 0;
    double h = (b - a) / n;
    double sum = 0.5 * (func(a) + func(b));

    do {
        prevSum = sum;
        sum = 0;
        h = (b - a) / n;

        for (int i = 1; i < n; i++) {
            sum += func(a + i * h);
        }

        sum = h * (sum + 0.5 * (func(a) + func(b)));
        n *= 2;
        
    } while (fabs(sum - prevSum) > eps);
    
    return sum;
}