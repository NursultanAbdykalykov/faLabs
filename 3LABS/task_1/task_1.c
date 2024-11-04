#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_BASE = 1
} StatusCode;


StatusCode convert_to_base(unsigned int number, unsigned int r, char *result, size_t buffer_size) {
    if (r < 1 || r > 5) {
        return ERROR_INVALID_BASE;
    }

    unsigned int base = 1 << r; // Основание системы счисления: 2^r
    size_t index = 0;

    while (number > 0 || index == 0) {
        // Проверяем переполнение буфера
        if (index >= buffer_size - 1) {
            return ERROR_INVALID_BASE; // Вряд ли понадобится, но добавлено для безопасности
        }

        unsigned int remainder = number & (base - 1); // Остаток от деления
        number >>= r;                                // Делим число на 2^r
        result[index++] = '0' + remainder;           // Записываем "цифру"
    }

    result[index] = '\0'; 

    for (size_t i = 0, j = index - 1; i < j; ++i, --j) {
        char temp = result[i];
        result[i] = result[j];
        result[j] = temp;
    }

    return SUCCESS;
}

int main() {
    unsigned int number = 45;
    unsigned int r = 3;

    const size_t BUFFER_SIZE = 33; // Максимум 32 цифры + '\0'
    char result[BUFFER_SIZE];


    StatusCode status = convert_to_base(number, r, result, BUFFER_SIZE);
    if (status != SUCCESS) {
        fprintf(stderr, "Ошибка: Недопустимое значение r.\n");
        return EXIT_FAILURE;
    }

    unsigned int base = 1 << r;
    printf("Число в системе счисления с основанием %u: %s\n", base, result);

    return EXIT_SUCCESS;
}
