#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

int validateFirstArgument(const char* x) {
    for (int i = 0; x[i] != '\0'; i++) {
        if (!(x[i] >= '0' && x[i] <= '9')) {
            return 0;
        }
    }
    return 1;
}

int compareStrings(const char* line1, const char* line2) { 
    return !strcmp(line1, line2);
}

int IsPrime(const int x) {
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}

long long NumPow(const int a, const int pw) {  
    long long num = 1;  
    for (int i = 1; i <= pw; i++) {  
        num *= a;  
    }  
    return num;  
}

long long fact(const int x) {
    const int divBy = 1000000007;
    long long fact = 1;
    for (long long int i = 2; i <= x; i++) {
        fact = (fact * i) % divBy;
    }
    printf("факториал (по модулю 10^9 + 7) = %lld\n", fact);
    return 0;
}

int printHex(int x) {
    char hexDigits[16] = "0123456789ABCDEF";
    char result[8];
    int index = 0;

    while (x > 0) {
        result[index++] = hexDigits[x % 16];
        x /= 16;
    }

    for (int i = index - 1; i >= 0; --i) {
        if (i < index - 1) {
            printf(" ");
        }
        printf("%c", result[i]);
    }
    return 1;
    printf("\n");
}

int flagH(const int x) {
    if (x > 100) {
        printf("Число должно быть меньше ста\n");
        return 1;
    }

    int count = 0;
    for (int i = x + 1; i <= 100; ++i) {
        if (i % x == 0) {
            printf("%d ", i);
            count++;
        }
    }
    
    if (count == 0) {
        printf("Таких чисел нет\n");
    }
    
    return count;
}

int flagP(const int x) {
    if (IsPrime(x)) {
        printf("%d является простым\n", x);
    } else {
        printf("%d является составным\n", x);
    }
    
    return 0;
}

int flagE(const int x) {
    if (x > 10) {
        printf("число должно быть меньше десяти\n");
        return 1;
    }

    for (int b = 1; b <= 10; b++) {
        for (int p = 0; p <= x; p++) {
            printf("%2d^%2d = %-5lld ", b, p, NumPow(b, p));
        }
        printf("\n");
    }
    
    return 0;
}

int flagA(const int x) {
    long long sum = 0;
    
    for (int i = 0; i <= x; ++i) {
        sum += i;
    }
    
    printf("%lld\n", sum);
    
    return sum;
}

int flagF(const int x) {
    fact(x);
    return 1;
}

int flagS(const int x) {
    if (x < 0) {
        printf("число не должно быть отрицательным\n");
        return -1;
    } else if (x == 0) {
        printf("0\n");
        return 0;
    } else {
        printHex(x);
        return 0;
    }
}