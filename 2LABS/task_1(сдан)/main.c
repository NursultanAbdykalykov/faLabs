#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int is_integer_digit(char *s) {
    int i = 0;
    if (s[0] == '\0') {
        return -1;
    }
    if (s[i] == '-') {
        return -1;
    }
    while (s[i] != '\0') {
        if (s[i] < '0' || s[i] > '9') {
            return -1;
        }
        i++;
    }

    return 1;
}

// Функция для сравнения строк вручную
int customStrcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

//Для флага -l
int customStrlen(const char* s) {
  int count = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    count++;
  }
  return count;
}

//Для флага -r
char* customStrrev(const char* s, int count) {
  char* newStr = (char*)malloc((count + 1) * sizeof(char));
  if (!newStr) {
    return NULL;
  }
  int j = 0;
  for (int i = count - 1; i >= 0; --i) {
    newStr[j] = *(s + i);
    ++j;
  }
  newStr[j] = '\0';
  return newStr;
}

//Для флага -u
char* capitalizeEverySecondChar(const char* s, int count) {
  char* newStr = (char*)malloc((count + 1) * sizeof(char));
  if (newStr == NULL) {
    return NULL;
  }
  int j = 0;
  for (int i = 0; i < count; ++i) {
    if (i % 2 == 0) {
      newStr[j] = *(s + i);
      j++;
    } else {
      char c = *(s + i);
      if (c >= 'a' && c <= 'z') {
        newStr[j] = c + 'A' - 'a';
        j++;
      } else {
        newStr[j] = c;
        j++;
      }
    }
  }
  newStr[j] = '\0';
  return newStr;
}

//Для флага -n
char* sortSymbolsByType(const char* s, int count) {
  char* newStr = (char*)malloc((count + 1) * sizeof(char));
  int j = 0;
  if (newStr == NULL) {
    return NULL;
  }
  for (int i = 0; i < count; ++i) {
    char c = *(s + i);
    if (c >= '0' && c <= '9') {
      newStr[j] = c;
      j++;
    }
  }

  for (int i = 0; i < count; ++i) {
    char c = *(s + i);
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
      newStr[j] = *(s + i);
      j++;
    }
  }

  for (int i = 0; i < count; ++i) {
    char c = *(s + i);
    if (!(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z') &&
        !(c >= '0' && c <= '9')) {
      newStr[j] = *(s + i);
      j++;
    }
  }
  newStr[j] = '\0';
  return newStr;
}
////////////////////

//Для флага -c

void shuffle(char* array[], int size) {
  for (int i = size - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    char* temp = array[i];
    array[i] = array[j];
    array[j] = temp;
  }
}

// Функция для конкатенации строк
void customStrcat(char* dest, const char* src) {
  // Находим конец строки dest
  int dest_len = customStrlen(dest);
  int i = 0;

  while (src[i] != '\0') {
    dest[dest_len + i] = src[i];
    i++;
  }
  dest[dest_len + i] = '\0';
}

// Функция для обработки флага -c
char* handle_c_flag(int argc, char* argv[]) {
  // Третий аргумент - это seed для srand
  int seed = atoi(argv[3]);
  srand(seed);

  // Строки для конкатенации: второй аргумент строка argv[2] и строки начиная с argv[4]
  int num_strings = argc - 3;
  char* selected_strings[num_strings];
  int total_length = 0;

  //вторая строчка
  selected_strings[0] = argv[2];
  total_length += customStrlen(argv[2]);

  //с оставшихся строк
  for (int i = 4; i < argc; i++) {
    selected_strings[i - 3] = argv[i];  // Сдвигаем индекс, чтобы начать с argv[4]
    total_length += customStrlen(argv[i]);
  }

  char* result = (char*)malloc((total_length + 1) * sizeof(char));
  if (result == NULL) {
    return NULL;
  }


  result[0] = '\0';


  shuffle(&selected_strings[0],
          num_strings);

  for (int i = 0; i < num_strings; i++) {
    customStrcat(result, selected_strings[i]);
  }
  return result;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Ошибка: недостаточно аргументов.\n");
        return 1;
    }

    char* flag = argv[1];

    if (customStrcmp(flag, "-l") == 0 || customStrcmp(flag, "-r") == 0 || customStrcmp(flag, "-u") == 0 || customStrcmp(flag, "-n") == 0) {
        if (argc != 3) {
            printf("Ошибка: неверное количество аргументов для флага %s. Ожидалось 3.\n", flag);
            return 1;
        }

        char* inputString = argv[2];
        int length = customStrlen(inputString);

        if (customStrcmp(flag, "-l") == 0) {
            printf("Длина строки: %d\n", length);
        } else if (customStrcmp(flag, "-r") == 0) {
            char* reversed = customStrrev(inputString, length);
            if (reversed) {
                printf("Перевёрнутая строка: %s\n", reversed);
                free(reversed);
            }
        } else if (customStrcmp(flag, "-u") == 0) {
            char* upperCased = capitalizeEverySecondChar(inputString, length);
            if (upperCased) {
                printf("Строка с заглавными символами: %s\n", upperCased);
                free(upperCased);
            }
        } else if (customStrcmp(flag, "-n") == 0) {
            char* sortedStr = sortSymbolsByType(inputString, length);
            if (sortedStr) {
                printf("Отсортированная строка: %s\n", sortedStr);
                free(sortedStr);
            }
        }

    } else if (customStrcmp(flag, "-c") == 0) {
        if (argc < 5) {
            printf("Ошибка: неверное количество аргументов для флага -c. Ожидалось минимум 5.\n");
            return 1;
        }
        if (is_integer_digit(argv[3]) == 1) {
            char* concatenated = handle_c_flag(argc, argv);
            if (concatenated) {
                printf("Конкатенированная строка: %s\n", concatenated);
                free(concatenated);
            }
        } else {
            printf("Ошибка: неверный тип данных у <seed>. Ожидалось целое число.\n");
            return 1;
        }
    } else {
        printf("Ошибка: неверный флаг %s.\n", flag);
        return 1;
    }

    return 0;
}

