#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Введите eps\n");
        return 1;
    }

    double eps = atof(argv[1]);

    if (!isFloat(argv[1])) {
        printf("Некорректный ввод\n");
        return 1;
    }

    if (eps == 0.0) {
        printf("eps не может быть равен 0\n");
        return 1;
    }

    double intA = integral(funcA, eps);
    double intB = integral(funcB, eps);
    double intC = integral(funcC, eps);
    double intD = integral(funcD, eps);

    printf("a: %.10f\n", intA);
    printf("b: %.10f\n", intB);
    printf("c: %.10f\n", intC);
    printf("d: %.10f\n", intD);

    return 0;
}