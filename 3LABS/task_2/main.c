#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>


enum Errors {
    ERROR = -1,
    SUCCESS,
};

typedef double (*Norma)(double* x, int n);

typedef struct {
    int n;
    double* x; 
} Vector;

double IterPow(double a, long long n) {
    double result = 1.0;

    if (n == 0) {
        return result; 
    }

    if (n < 0) {
        a = 1.0 / a;
        n = -n; 
    }

    while (n > 0) {
        if (n % 2 == 0) {
            a *= a;
            n /= 2;
        } else {
            result *= a;
            n--;
        }
    }

    return result;
}

int ValidateNumber(const char* str) {
    int lenStr = strlen(str);
    for (int i = 0; i < lenStr; ++i) {
        if ('0' > str[i] || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int ValidateFloatNumber(const char* str) {
    int lenStr = strlen(str);
    int wasSep = 0;
    for (int i = 0; i < lenStr; ++i) {
        if (str[i] == '-') {
            if (i == 0) {
                continue;
            } else {
                return 0;
            }
        }
        if (str[i] == '.' || str[i] == ','){
            if (wasSep) {
                return 0;
            } 
            wasSep = 1;
        } else if (('0' > str[i] || str[i] > '9') && str[i] != '.' && str[i] != ',') {
            return 0;
        }
    }
    return 1;
}

double FirstNorma(double* x, int n) {
    if (n <= 0) {
        return -1;
    }
    double max = 0;
    for (int i = 0; i < n; ++i) {
        int isNegative = x[i] < 0 ? -1 : 1;
        if (x[i] * isNegative > max) {
            max = x[i];
        }
    }
    return max;
}

double CalculateSum(double* x, int n, int p) {
    if (n <= 0 || p <= 0) {
        return ERROR;
    }
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        int isNegative = x[i] < 0 ? -1 : 1;
        sum += IterPow(isNegative * x[i], p);
    }
    sum = pow(sum, 1.0 / p);
    return sum;
}

double SecondNorma(double* x, int n) {
    int p = 2;
    return CalculateSum(x, n, p);
}

double MulMatrixVec(double* A, double* x, int n) {
    double newX[n];
    double result = 0;
    for (int i = 0; i < n ; ++i) {
        newX[i] = 0;
        for (int j = 0; j < n; ++j) {
            newX[i] += A[(i * n) + j] * x[j];
        }
    }
    
    for (int i = 0; i < n; ++i) {
        result += newX[i] * x[i];
    }
    return result;
}

double ThirdNorma(double* x, int n) {
    double A[] = {
        10.0, 2.0, 3.0,
        4.0, 3.3, 7.0,
        7.0, 8.0, 9.0
    };
    double res = pow(MulMatrixVec(A, x, n), 0.5);
    return res;
}

int DisplayResult(int amountOfVectors[], Vector** maxVectors, int numNorm, int n) {
    for (int i = 0; i < numNorm; ++i) {
        printf("%d вектора для %d нормы:\n", amountOfVectors[i], i + 1);
        for (int j = 0; j < amountOfVectors[i]; ++j) {
            printf("* (");
            for (int z = 0; z < n; ++z) {
                if (z == n - 1) {
                    printf("%.3f", maxVectors[i][j].x[z]);
                } else {
                    printf("%.3f, ", maxVectors[i][j].x[z]);
                }
            }
            printf(")\n");
        }
        printf("\n");
    }
    return SUCCESS;
}

Vector** FindMax(int n, int numVec, int numNorm, ...) {
    if (n <= 0 || numVec <= 0 || numNorm <= 0) {
        return NULL;
    }
    Vector vectors[numVec];
    Norma normas[numNorm];

    va_list args;
    va_start(args, numNorm);

    for (int i = 0; i < numVec; ++i) {
        vectors[i].n = n;
        vectors[i] = va_arg(args, Vector);
    }

    for (int i = 0; i < numNorm; ++i) {
        normas[i] = va_arg(args, Norma);
    }

    int amountOfVectors[numNorm];
    Vector** maxVectors = malloc(numNorm * sizeof(Vector*));
    if (maxVectors == NULL) {
        return NULL;
    }
    for (int i = 0; i < numNorm; i++) {
        maxVectors[i] = malloc(numVec * sizeof(Vector));
        if (maxVectors[i] == NULL) {
        return NULL;
    }
    }
    for (int i = 0; i < numNorm; ++i) {    

        double max = normas[i](vectors[0].x, n);
        int indx = 0;
        for (int j = 0; j < numVec; ++j) {

            if (max < normas[i](vectors[j].x, n)) {
                max = normas[i](vectors[j].x, n);
                maxVectors[i][0] = vectors[j];
                indx = 1;
            } else if (max == normas[i](vectors[j].x, n)) {
                maxVectors[i][indx] = vectors[j];
                indx++;
            }

        }
        amountOfVectors[i] = indx;
    }

    va_end(args);

    DisplayResult(amountOfVectors, maxVectors, numNorm, n);

    return maxVectors;
} 

double* MakeVector(int n, double* x, Vector* vec) {
    vec->n = n;
    vec->x = (double*)malloc(sizeof(double) * n);
    for (int i = 0; i < n; ++i) {
        vec->x[i] = x[i];
    }
    return vec->x;
}

int main() {
    Vector x1;
    Vector x2;
    Vector x3;
    char buffer[15]; 
    int n = 0; 
    printf("Введите размерность: ");
    scanf("%s", buffer);
    if (!ValidateNumber(buffer)) {
        printf("ОШИБКА: размерность должна быть числом больше 0\n");
        return ERROR;
    }
    n = atoi(buffer);

    double coords[3][n];

    printf("Введите 3 вектора размерностью %d:\n", n);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%s", buffer);
            if (!ValidateFloatNumber(buffer)) {
                printf("ОШИБКА: некорректное число\n");
                return ERROR;
            }
            coords[i][j] = atof(buffer);
        }
    }
    
    double* pch1 = MakeVector(n, coords[0], &x1);
    double* pch2 = MakeVector(n, coords[1], &x2);
    double* pch3 = MakeVector(n, coords[2], &x3);

    Vector** vectors = FindMax(n, 3, 3, x1, x2, x3, &FirstNorma, &SecondNorma, &ThirdNorma);
    free(pch1);
    free(pch2);
    free(pch3);
    for (int i = 0; i < 3; i++) {
        free(vectors[i]);
    }
    free(vectors);
    return SUCCESS;
}
