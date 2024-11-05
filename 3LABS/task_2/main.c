#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef enum
{
    SUCCESS,
    INVALID_DIMENSION,
    NO_VECTORS_PROVIDED,
    NORM_FUNCTION_NOT_PROVIDED
} ErrorCode;

// Тип функции для вычисления нормы
typedef double (*NormFunction)(const double *, int, const void *);

// Фдля первой
double infinityNorm(const double *vec, int n, const void *_)
{
    double max_val = 0.0;
    for (int i = 0; i < n; ++i)
    {
        double abs_val = fabs(vec[i]);
        if (abs_val > max_val)
        {
            max_val = abs_val;
        }
    }
    return max_val;
}

// для второй
double pNorm(const double *vec, int n, const void *p_ptr)
{
    double p = *(const double *)p_ptr; // Приводим указатель к тпиу double
    double sum = 0.0;
    for (int i = 0; i < n; ++i)
    {
        sum += pow(fabs(vec[i]), p);
    }
    return pow(sum, 1.0 / p);
}

// для тертьей
double matrixNorm(const double *vec, int n, const void *A_ptr)
{
    const double **A = (const double **)A_ptr;
    double sum = 0.0;

    for (int i = 0; i < n; ++i)
    {
        double temp = 0.0;
        for (int j = 0; j < n; ++j)
        {
            temp += A[i][j] * vec[j];
        }
        sum += temp * vec[i];
    }
    return sqrt(sum);
}

// функция для поиска вектора с наибольшей номрой
ErrorCode findLongestVector(int n, int numVectors, int numNorms, ...)
{
    if (n <= 0)
        return INVALID_DIMENSION;
    if (numVectors <= 0)
        return NO_VECTORS_PROVIDED;
    if (numNorms <= 0)
        return NORM_FUNCTION_NOT_PROVIDED;

    va_list args;
    va_start(args, numNorms);

    // считываем векторы
    const double **vectors = malloc(numVectors * sizeof(double *));
    for (int i = 0; i < numVectors; ++i)
    {
        vectors[i] = va_arg(args, const double *);
    }

    // считываем функции норм и их параметры
    NormFunction *normFuncs = malloc(numNorms * sizeof(NormFunction));
    const void **normParams = malloc(numNorms * sizeof(void *));
    for (int i = 0; i < numNorms; ++i)
    {
        normFuncs[i] = va_arg(args, NormFunction);
        normParams[i] = va_arg(args, const void *);
    }

    // для каждой функции нормы находим вектор с максимальной нормой
    for (int i = 0; i < numNorms; ++i)
    {
        NormFunction normFunc = normFuncs[i];
        const void *normParam = normParams[i];
        double maxNorm = -DBL_MAX;
        const double *longestVector = NULL;

        for (int j = 0; j < numVectors; ++j)
        {
            double currentNorm = normFunc(vectors[j], n, normParam);
            if (currentNorm > maxNorm)
            {
                maxNorm = currentNorm;
                longestVector = vectors[j];
            }
        }

        if (longestVector != NULL)
        {
            printf("Вектор с наибольшей нормой для функции %d: ", i + 1);
            for (int k = 0; k < n; ++k)
            {
                printf("%f ", longestVector[k]);
            }
            printf("\n");
        }
    }

    free(vectors);
    free(normFuncs);
    free(normParams);
    va_end(args);
    return SUCCESS;
}

int main()
{
    int n = 3;

    double vec1[] = {1.0, 2.0, 3.0};
    double vec2[] = {4.0, 5.0, 6.0};
    double vec3[] = {7.0, 8.0, 9.0};

    double A_data[3][3] = {
        {2.0, 0.5, 0.0},
        {0.5, 3.0, 0.5},
        {0.0, 0.5, 4.0}};
    const double *A[3] = {A_data[0], A_data[1], A_data[2]};

    double p = 2.0; // Значение p для p-нормы (например, p = 2 для евклидовой нормы)

    // вызыва функции для поиска вектора с наибольшей нормой
    ErrorCode code = findLongestVector(
        n,
        3,
        3,
        vec1, vec2, vec3,
        infinityNorm, NULL,
        pNorm, &p,
        matrixNorm, A);

    if (code != SUCCESS)
    {
        printf("Произошла ошибка: ");
        switch (code)
        {
        case INVALID_DIMENSION:
            printf("Неверная размерность\n");
            break;
        case NO_VECTORS_PROVIDED:
            printf("Векторы не предоставлены\n");
            break;
        case NORM_FUNCTION_NOT_PROVIDED:
            printf("Функция нормы не предоставлена\n");
            break;
        default:
            printf("Неизвестная ошибка\n");
            break;
        }
    }

    return 0;
}
