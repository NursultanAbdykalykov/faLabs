#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* add_a_b(const char* number1, const char* number2, int cc) {
    const char DIGITS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int maxLen = (strlen(number1) > strlen(number2)) ? strlen(number1) : strlen(number2);
    char* result = (char*)malloc((maxLen + 2) * sizeof(char));

    if (result == NULL) {
        return NULL;
    }

    int ost = 0;    // для остатка
    int index = 0;  // индекс для result
    int i = strlen(number1) - 1;
    int j = strlen(number2) - 1;


    while (i >= 0 || j >= 0 || ost > 0) {
        int digit1 = (i >= 0) ? strchr(DIGITS, number1[i--]) - DIGITS : 0;
        int digit2 = (j >= 0) ? strchr(DIGITS, number2[j--]) - DIGITS : 0;

        int sum = digit1 + digit2 + ost;
        result[index++] = DIGITS[sum % cc];
        ost = sum / cc;
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
  
    return result;
}

int main() {
    char* result = add_a_b("A", "1F", 16);  
    printf("%s\n", result);                 

    free(result);
    return 0;
}
