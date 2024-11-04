#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("введите два аргумента\n");
        return 1;
    }

    double x = atof(argv[1]);
    double eps = atof(argv[2]);

    if (!isFloat(argv[1]) || !isFloat(argv[2])) {
        printf("недопустимый ввод\n");
        return 1;
    }

    if (eps == 0.0) {
        printf("eps не может быть равен нулю\n");
        return 1;
    }

    if (x == 0.0) {
        printf("x не может быть равен нулю\n");
        return 1;
    }

    printf("a: %.10f\n", sumA(x, eps));
    printf("b: %.10f\n", sumB(x, eps));
    
  	if(sumC(x, eps)){
    	printf("c: %.10f\n", sumC(x, eps));
	}
  	if(sumD(x, eps)){
    	printf("d: %.10f\n", sumD(x, eps));
	}

  	return 0; 
}