#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

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

double stirlingFormula(int n) {
    if (n == 0) {
        return 1.0;
    }
    return sqrt(2 * acos(-1) * n) * pow(n / exp(1.0), n);
}

double fact(const int n) {
    if (n == 0 || n == 1) {
        return 1.0;
    }
    if (n <= 15) {
        double fact = 1;
        for (int i = 2; i <= n; i++) {
            fact *= i;
        }
        return fact;
    } else {
        return stirlingFormula(n);
    }
}

double numPow(const double a, const int pw) {  
    double num = 1.0;  
    for (int i = 1; i <= pw; i++) {  
        num *= a;  
    }  
    return num;  
}  

double sumA(double x, double eps) {
    double sum = 0.0, a = 1.0;
    int n = 0;
    while (fabs(a) > eps) {
        sum += a;
        n++;
        a = numPow(x, n) / fact(n);
        if (isinf(a) || isnan(a)) {
            printf("переполнение значения при n=%d\n", n);
            return 0.0;
        }
    }
    return sum;
}

double sumB(double x, double eps) {
    double sum = 0.0, a = 1.0;
    int n = 0;
    while (fabs(a) > eps) {
        sum += a;
        n++;
        a = numPow(-1.0, n) * numPow(x, 2 * n) / fact(2 * n);
        if (isinf(a) || isnan(a)) {
            printf("переполнение значения при n=%d\n", n);
            return 0.0;
        }
    }
    return sum;
}

double sumC(double x, double eps) {
    if (fabs(x) >= 1.0) {
        printf("ряд c сходится при |x| < 1\n");
        return 0.0;
    }
    double sum = 0.0, a = 1.0;
    int n = 0;
    while (fabs(a) > eps) {
        sum += a;
        n++;
        
        a = (numPow(3, 3 * n) * numPow(fact(n), 3) * numPow(x, 2 * n)) / fact(3 * n);
        if(isinf(a) || isnan(a)) {
            printf("переполнение значения при n=%d\n", n);
            return 0.0;
        }
    }
    return sum;
}

double sumD(double x, double eps) {
    if (fabs(x) >= 1.0) {
        printf("ряд d сходится при |x| < 1\n");
        return 0.0;
    }
    
    double sum = 0.0, a = -x * x / 2.0; 
    int n = 1;

    while (fabs(a) > eps) {
        sum += a;
        n++;
        
        a = (numPow(-1.0, n) * numPow(x, 2 * n) * fact(fact(2 * n - 1))) / fact(fact(2 * n));
        
        if (isinf(a) || isnan(a)) {
            printf("переполнение значения при n=%d\n", n);
            return 0.0;
        }
    }
    
    return sum;
}