#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    char firstName[BUFSIZ];
    char lastName[BUFSIZ];
    char group[BUFSIZ];
    unsigned char *grades;
} Student;

int IsInt(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int IsString(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) {
            return 0;
        }
    }
    return 1;
}


char* GetFileName(const char* filePath) {
    const char* fileName = strrchr(filePath, '\\');
    
    if (fileName == NULL) {
        return (char*)filePath;
    } else {
        return (char*)(fileName + 1);
    }
}

int LoadStudents(const char *inputFile, Student **students, int *count, const char *outputFile) {
    FILE *input = fopen(inputFile, "r");
    FILE *output = fopen(outputFile, "w");
    if (!input || !output) {
        printf("Невозможно открыть входной или выходной файл\n");
        return -1;
    }

    int capacity = 2;
    *count = 0;
    *students = malloc(capacity * sizeof(Student));
    if (*students == NULL) {
        printf("Ошибка выделения памяти\n");
        fclose(input);
        fclose(output);
        return -1;
    }

    char idStr[20];
    char firstName[BUFSIZ], lastName[BUFSIZ], group[BUFSIZ];
    char gradeStr[5][4];  
    while (fscanf(input, "%s %s %s %s %s %s %s %s %s", idStr, firstName, lastName, group,
                  gradeStr[0], gradeStr[1], gradeStr[2], gradeStr[3], gradeStr[4]) == 9) {

        int isValid = 1;  

        if (!IsInt(idStr)) {
            fprintf(output, "Неверные данные (ID не целое число): %s\n", idStr);
            isValid = 0;
        }

        if (!IsString(firstName)) {
            fprintf(output, "Неверные данные (имя содержит неалфавитные символы): %s\n", firstName);
            isValid = 0;
        }
        if (!IsString(lastName)) {
            fprintf(output, "Неверные данные (фамилия содержит неалфавитные символы): %s\n", lastName);
            isValid = 0;
        }

        if (strlen(group) == 0) {
            fprintf(output, "Неверные данные (группа пустая)\n");
            isValid = 0;
        }

        unsigned char grades[5];
        for (int i = 0; i < 5; i++) {
            if (!IsInt(gradeStr[i])) {
                fprintf(output, "Неверные данные (оценка не целое число): %s\n", gradeStr[i]);
                isValid = 0;
                break;
            }
            int gradeValue = atoi(gradeStr[i]);
            if (gradeValue < 0 || gradeValue > 255) {
                fprintf(output, "Неверные данные (оценка вне допустимого диапазона): %d\n", gradeValue);
                isValid = 0;
                break;
            }
            grades[i] = (unsigned char) gradeValue;
        }

        if (!isValid) {
            continue;
        }

        if (*count >= capacity) {
            capacity *= 2;
            Student *temp = realloc(*students, capacity * sizeof(Student));
            if (temp == NULL) {
                printf("Ошибка перераспределения памяти\n");
                fclose(input);
                fclose(output);
                return -1;
            }
            *students = temp;
        }

        Student *current = &(*students)[*count];
        current->id = atoi(idStr);
        strcpy(current->firstName, firstName);
        strcpy(current->lastName, lastName);
        strcpy(current->group, group);
        current->grades = malloc(5 * sizeof(unsigned char));
        if (current->grades == NULL) {
            printf("Ошибка выделения памяти\n");
            fclose(input);
            fclose(output);
            return -1;
        }
        memcpy(current->grades, grades, 5 * sizeof(unsigned char));

        (*count)++;
    }

    fclose(input);
    fclose(output);
    return 0;
}



int CompareById(const void *a, const void *b) {
    return ((Student *)a)->id - ((Student *)b)->id;
}

int CompareByLastName(const void *a, const void *b) {
    return strcmp(((Student *)a)->lastName, ((Student *)b)->lastName);
}

int CompareByFirstName(const void *a, const void *b) {
    return strcmp(((Student *)a)->firstName, ((Student *)b)->firstName);
}

int CompareByGroup(const void *a, const void *b) {
    return strcmp(((Student *)a)->group, ((Student *)b)->group);
}

float CalcAverageGrade(const Student *student) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += student->grades[i];
    }
    return sum / 5.0;
}

void PrintStudent(const Student *student) {
    printf("ID: %d, name: %s %s, group: %s, average grade: %.2f\n",
           student->id, student->firstName, student->lastName, student->group, CalcAverageGrade(student));
}

void PrintAboveAverageStudents(const char *logFileName, Student *students, int count, float overallAverage) {
    FILE *logFile = fopen(logFileName, "w");
    if (logFile == NULL) {
        printf("Невозможно открыть файл вывода\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        float avgGrade = CalcAverageGrade(&students[i]);
        if (avgGrade > overallAverage) {
            fprintf(logFile, "Студент: %s %s, средняя оценка: %.2f\n", 
                    students[i].firstName, students[i].lastName, avgGrade);
        }
    }
    fclose(logFile); 
}

void FindByID(const char *logFileName, Student *students, int count, int id) {
    int found = 0;

    FILE *logFile = fopen(logFileName, "w");
    if (logFile == NULL) {
        printf("Невозможно открыть файл вывода\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            fprintf(logFile, "ID: %d, Имя: %s %s, Группа: %s, Средняя оценка: %.2f\n",
                   students[i].id, students[i].firstName, students[i].lastName,
                   students[i].group, CalcAverageGrade(&students[i]));
            found = 1;
            break; 
        }
    }
    if (!found) {
        fprintf(logFile, "Студент с ID '%d' не найден\n", id);
    }
    fclose(logFile); 
}

void FindByLastName(const char *logFileName, Student *students, int count, const char *lastName) {
    int found = 0;  

    FILE *logFile = fopen(logFileName, "w");
    if (logFile == NULL) {
        printf("Невозможно открыть файл вывода\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            fprintf(logFile, "ID: %d, Имя: %s %s, Группа: %s, Средняя оценка: %.2f\n",
                   students[i].id, students[i].firstName, students[i].lastName,
                   students[i].group, CalcAverageGrade(&students[i]));
            found = 1;  
        }
    }
    if (!found) {
        fprintf(logFile, "Студент с фамилией '%s' не найден\n", lastName);
    }
    fclose(logFile); 
}

void FindByFirstName(const char *logFileName, Student *students, int count, const char *firstName) {
    int found = 0; 

    FILE *logFile = fopen(logFileName, "w");
    if (logFile == NULL) {
        printf("Невозможно открыть файл вывода\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].firstName, firstName) == 0) {
            fprintf(logFile, "ID: %d, Имя: %s %s, Группа: %s, Средняя оценка: %.2f\n",
                   students[i].id, students[i].firstName, students[i].lastName,
                   students[i].group, CalcAverageGrade(&students[i]));
            found = 1;
        }
    }
    
    if (!found) {
        fprintf(logFile, "Студент с именем '%s' не найден\n", firstName);
    }
    fclose(logFile);
}

void FindByGroup(const char *logFileName, Student *students, int count, const char *group) {
    int found = 0; 

    FILE *logFile = fopen(logFileName, "w");
    if (logFile == NULL) {
        printf("Невозможно открыть файл вывода\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].group, group) == 0) {
            fprintf(logFile, "ID: %d, Имя: %s %s, Группа: %s, Средняя оценка: %.2f\n",
                   students[i].id, students[i].firstName, students[i].lastName,
                   students[i].group, CalcAverageGrade(&students[i]));
            found = 1;
        }
    }
    if (!found) {
        fprintf(logFile, "Группа '%s' не найдена\n", group);
    }
    fclose(logFile);
}


int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("enter input and output files\n");
        return 1;
    }
    
    Student *students = NULL;
    int studentCount = 0;

    char* inAddress = argv[1];
    char* outAddress = argv[2];

    char* fileName1 = GetFileName(inAddress);
    char* fileName2 = GetFileName(outAddress);

    if (!strcmp(fileName1, fileName2)) {
        printf("input and output files cannot be the same\n");
        return 2;
    }
    
    FILE *logFile = fopen(outAddress, "w");
    if (!logFile) {
        printf("cannot open output file");
        free(students);
        return 2;
    }

    if (LoadStudents(argv[1], &students, &studentCount, argv[2]) != 0) {
        printf("cannot read from input file\n");
        return 2;
    }
    
    float overallAverage = 0;
    for (int i = 0; i < studentCount; i++) {
        overallAverage += CalcAverageGrade(&students[i]);
    }
    overallAverage /= studentCount;
    
    int choice;
    int id;
    char input[BUFSIZ];
    
    while (1) {
        printf("1. Поиск по ID\n");
        printf("2. Поиск по фамилии\n");
        printf("3. Поиск по имени\n");
        printf("4. Поиск по группе\n");
        printf("5. Сортировка по ID\n");
        printf("6. Сортировка по фамилии\n");
        printf("7. Сортировка по имени\n");
        printf("8. Сортировка по группе\n");
        printf("9. Вывод студентов с оценками выше средней\n");
        printf("10. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Введите ID: ");
                scanf("%d", &id);
                FindByID(argv[2], students, studentCount, id);
                break;
            case 2:
                printf("Введите фамилию: ");
                scanf("%s", input);
                FindByLastName(argv[2], students, studentCount, input);
                break;

            case 3:
                printf("Введите имя: ");
                scanf("%s", input);
                FindByFirstName(argv[2], students, studentCount, input);
                break;

            case 4:
                printf("Введите группу: ");
                scanf("%s", input);
                FindByGroup(argv[2], students, studentCount, input);
                break;
                
            case 5:
                qsort(students, studentCount, sizeof(Student), CompareById);
                for (int i = 0; i < studentCount; i++) {
                    PrintStudent(&students[i]);
                }
                break;
                
            case 6:
                qsort(students, studentCount, sizeof(Student), CompareByLastName);
                for (int i = 0; i < studentCount; i++) {
                    PrintStudent(&students[i]);
                }
                break;
                
            case 7:
                qsort(students, studentCount, sizeof(Student), CompareByFirstName);
                for (int i = 0; i < studentCount; i++) {
                    PrintStudent(&students[i]);
                }
                break;
                
            case 8:
                qsort(students, studentCount, sizeof(Student), CompareByGroup);
                for (int i = 0; i < studentCount; i++) {
                    PrintStudent(&students[i]);
                }
                break;
                
            case 9:
                PrintAboveAverageStudents(argv[2], students, studentCount, overallAverage);
                break;
                
            case 10:
                for (int i = 0; i < studentCount; i++) {
                    free(students[i].grades);
                }
                free(students);
                fclose(logFile);
                return 0;
            default:
                printf("Неверный выбор\n");
                break;
        }
    }
    return 0;
}