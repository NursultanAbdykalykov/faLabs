#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char* argv[]) {
    char* flag = argv[1];

    if (compareStrings(flag, "-q") || compareStrings(flag, "/q")) {
        if (argc != 6) {
            printf("введите 6 аргументов\n");
            return 1;
        } else {
            float eps = atof(argv[2]);
            float a = atof(argv[3]);
            float b = atof(argv[4]);
            float c = atof(argv[5]);

            if (!(isFloat(argv[2]) && isFloat(argv[3]) && isFloat(argv[4]) && isFloat(argv[5]))) {
                printf("недопустимые аргументы\n");
                return 1;
            }

            if (eps == 0) {
                printf("eps не может быть равным 0\n");
                return 1;
            }

            flagQ(eps, a, b, c);
        }
    } else if (compareStrings(flag, "-m") || compareStrings(flag, "/m")) {
        if (argc != 4) {
            printf("введите 4 аргумента\n");
            return 1;
        } else {
            int a = atoi(argv[2]);
            int b = atoi(argv[3]);
            if (!(isInt(argv[2]) && isInt(argv[3]))) {
                printf("недопустимые аргументы\n");
                return 1;
            }

            if (a && b) {
                flagM(a, b);
            } else {
                printf("a и b должны быть != 0\n");
                return 2;
            }
        }
    } else if (compareStrings(flag, "-t") || compareStrings(flag, "/t")) {
        if (argc != 6) {
            printf("введите 6 аргументов\n");
            return 1;
        } else {
            float eps = atof(argv[2]);
            float a = atof(argv[3]);
            float b = atof(argv[4]);
            float c = atof(argv[5]);

            if (!(isFloat(argv[2]) && isFloat(argv[3]) && isFloat(argv[4]) && isFloat(argv[5]))) {
                printf("недопустимые аргументы\n");
                return 1;
            }

            if (a < 0 || b < 0 || c < 0) {
                printf("стороны треугольника должны быть положительными\n");
                return 1;
            }

            if (eps == 0) {
                printf("eps не может быть равным 0\n");
                return 1;
            }

            flagT(eps, a, b, c);
        }
    } else {
        printf("неизвестный флаг\n");
    }

    return 0;
}