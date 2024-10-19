#include <stdio.h>
#include "functions.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Программа должна запускаться с: %s <epsilon>\n", argv[0]);
        return 1;
    }

    char* end;
    double epsilon = myStrtod(argv[1], &end);
    if (*end != '\0') {
        fprintf(stderr, "Некорректное значение epsilon.\n");
        return 1;
    }

    printf("Константа e\n");
    printf("\tлимит: %Lf\n", eLimit(epsilon));
    printf("\tряд: %Lf\n", eSeries(epsilon));
    printf("\tуравнение: %Lf\n", eEquation(epsilon));
    
    printf("Константа pi\n");
    printf("\tлимит: %Lf\n", piLimit(epsilon));
    printf("\tряд: %Lf\n", piSeries(epsilon));
    printf("\tуравнение: %Lf\n", piEquation(epsilon));
    
    printf("ln(2)\n");
    printf("\tлимит: %Lf\n", ln2Limit(epsilon));
    printf("\tряд: %Lf\n", ln2Series(epsilon));
    printf("\tуравнение: %Lf\n", ln2Equation(epsilon));
    
    printf("sqrt(2)\n");
    printf("\tлимит: %Lf\n", sqrt2Limit(epsilon));
    printf("\tряд: %Lf\n", sqrt2Series(epsilon));
    printf("\tуравнение: %Lf\n", sqrt2Equation(epsilon));
    
    printf("Гамма-функция\n");
    printf("\tлимит: %Lf\n", gammaLimit(epsilon));
    printf("\tряд: %Lf\n", gammaSeries(epsilon));
    printf("\tуравнение: %Lf\n", gammaEquation(epsilon));

    return 0;
}