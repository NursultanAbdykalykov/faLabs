#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "functions.h"

int compareStrings(const char* s1, const char* s2) {
    return !strcmp(s1, s2);
}

int isFloat(char* x) {
    bool numsBeforeDot = false;
    bool numsAfterDot = false;
    bool hasDot = false;
    for (int i = 0; x[i] != '\0'; i++) {
        if (x[0] == '-') {
            continue;
        }
        if (!((x[i] - '0' >= 0 && x[i] - '0' <= 9) || x[i] == '.')) {
            return 0; // Неверный символ
        }
        if ((x[i] - '0' >= 0 && x[i] - '0' <= 9 && !hasDot)) {
            numsBeforeDot = true;
        }
        if ((x[i] - '0' >= 0 && x[i] - '0' <= 9 && hasDot)) {
            numsAfterDot = true;
        }
        if (x[i] == '.' && !numsBeforeDot) {
            return 0; // Точка в начале
        }
        if (x[i] == '.' && hasDot) {
            return 0; // Вторая точка
        }
        if (x[i] == '.' && !hasDot) {
            hasDot = true;
        }
    }
    if (hasDot && !numsAfterDot) {
        return 0; // Точка в конце
    }

    return 1; // Вещественное число
}

int isInt(char* x) {
    int i = 0;
    if (x[0] == '-') {
            i = 1;
    }
    for (; x[i] != '\0'; i++) {
        if (!(x[i] - '0' >= 0 && x[i] - '0' <= 9)) {
            return 0; // Неверный символ
        }
    }
    return 1; // Целое число
}

int quadEq(const float eps, const float a, const float b, const float c) {
    if (fabs(a) <= fabs(eps)) {
        printf("a должно быть != 0\n");
        return 1;
    }

    printf("%.3fx^2 + %.3fx + %.3f: ", a, b, c);
    float x1, x2;
    float d = b * b - 4 * a * c;

    if (d < -fabs(eps)) {
        printf("d = %.3f, действительных корней не найдено\n", d);
        return 0;
    } else if (fabs(d) <= fabs(eps)) {
        x1 = -b/(2 * a);
        x2 = x1; // Один корень
    } else {
        x1 = (-b - sqrt(d))/(2 * a);
        x2 = (-b + sqrt(d))/(2 * a);
    }

    printf("d = %.3f, x1 = %.3f, x2 = %.3f\n", d, x1, x2);
    return 0;
}

int isDivBy(const int a, const int b) {
    return !(((a % b) + b) % b);
}

int rightTriangle(const float eps, const float a, const float b, const float c) {
    if (fabs(a * a - (b * b + c * c)) <= fabs(eps)) {
        return 1; 
    } else if (fabs(b * b - (a * a + c * c)) <= fabs(eps)) {
        return 1; 
    } else if (fabs(c * c - (b * b + a * a)) <= fabs(eps)) {
        return 1; 
    } else {
        return 0; 
    }
}

int flagQ(const float eps, const float a, const float b, const float c) {
    quadEq(eps, a, b, c);
}

int flagM(const int a, const int b) {
    if (isDivBy(a, b)) {
        printf("a делится на b\n");
    } else {
        printf("a НЕ делится на b\n");
    }
}

int flagT(const float eps, const float a, const float b, const float c) {
    if (rightTriangle(eps, a, b, c)) {
        printf("да\n");
    } else {
        printf("нет\n");
    }
}