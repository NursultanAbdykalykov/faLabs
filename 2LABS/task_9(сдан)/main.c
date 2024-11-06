#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


char* add_a_b(int cc, int count, ...) {
    const char DIGITS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char** numbers = (char**)malloc(count * sizeof(char*));
    if (numbers == NULL) {
        return NULL;
    }

    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        numbers[i] = va_arg(args, char*);
    }
    va_end(args);

    int* positions = (int*)malloc(count * sizeof(int));
    if (positions == NULL) {
        free(numbers);
        return NULL;
    }

    for (int k = 0; k < count; k++) {
        positions[k] = strlen(numbers[k]) - 1; // Устанавливаем начальные позиции на последний индекс
    }


    size_t maxLen = 0;
    for (int k = 0; k < count; k++) {
        maxLen = (strlen(numbers[k]) > maxLen) ? strlen(numbers[k]) : maxLen;
    }

    char* result = (char*)malloc((maxLen + 2) * sizeof(char));
    if (result == NULL) {
        free(positions);
        free(numbers);
        return NULL;
    }

    int ost = 0;    // для остатка
    int index = 0;  // индекс для result

    while (1) {
        int total = ost;

        for (int k = 0; k < count; k++) {
            if (positions[k] >= 0) {
                total += strchr(DIGITS, numbers[k][positions[k]--]) - DIGITS;
            }
        }

        if (total == 0 && ost == 0) break; // Если все числа закончились и нет остатка

        result[index++] = DIGITS[total % cc];
        ost = total / cc; 
    }

    result[index] = '\0';

    for (int start = 0, end = index - 1; start < end; start++, end--) {
        char temp = result[start];
        result[start] = result[end];
        result[end] = temp;
    }

    char* ptr = result;
    while (*ptr == '0' && *(ptr + 1) != '\0') {
        ptr++;
    }
    memmove(result, ptr, strlen(ptr) + 1);
    
    free(positions);
    free(numbers);

    return result;
}


int main() {
    char* result = add_a_b(10, 5, "1", "2", "3", "4", "5");  
    printf("%s\n", result);                     
    free(result);

    char* result2 = add_a_b(16, 5, "1A", "2", "3B", "4C", "5");  
    printf("%s\n", result2);                     
    free(result2);

    char* result3 = add_a_b(31, 5, "1Z", "ZZ", "VS", "4A", "51");  
    printf("%s\n", result3);                     
    free(result3);

    return 0;
}