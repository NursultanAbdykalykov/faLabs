#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int id;
    char first_name[50];
    char last_name[50];
    double salary;
} Employee;

typedef enum
{
    SUCCESS = 0,
    FILE_ERROR,
    MEMORY_ERROR,
} ErrorCode;

ErrorCode read_employees(const char *filename, Employee **employees, size_t *count)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        return FILE_ERROR;
    }

    size_t capacity = 10;
    *employees = malloc(capacity * sizeof(Employee));
    if (!*employees)
    {
        fclose(file);
        return MEMORY_ERROR;
    }

    *count = 0;
    while (fscanf(file, "%u %49s %49s %lf", &(*employees)[*count].id,
                  (*employees)[*count].first_name,
                  (*employees)[*count].last_name,
                  &(*employees)[*count].salary) == 4)
    {
        (*count)++;
        if (*count >= capacity)
        {
            capacity *= 2;
            *employees = realloc(*employees, capacity * sizeof(Employee));
            if (!*employees)
            {
                fclose(file);
                return MEMORY_ERROR;
            }
        }
    }

    fclose(file);
    return SUCCESS;
}

ErrorCode write_employees(const char *filename, Employee *employees, size_t count)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        return FILE_ERROR;
    }

    char buffer[200];

    for (size_t i = 0; i < count; i++)
    {
        snprintf(buffer, sizeof(buffer), "%u %.49s %.49s %.2f\n", employees[i].id,
                 employees[i].first_name,
                 employees[i].last_name,
                 employees[i].salary);
        fputs(buffer, file);
    }

    fclose(file);
    return SUCCESS;
}

int compare_employees(const void *a, const void *b)
{
    const Employee *emp1 = (const Employee *)a;
    const Employee *emp2 = (const Employee *)b;

    if (emp1->salary != emp2->salary)
    {
        return (emp1->salary < emp2->salary) ? -1 : 1;
    }

    int last_name_cmp = strcmp(emp1->last_name, emp2->last_name);
    if (last_name_cmp != 0)
    {
        return last_name_cmp;
    }

    int first_name_cmp = strcmp(emp1->first_name, emp2->first_name);
    if (first_name_cmp != 0)
    {
        return first_name_cmp;
    }

    return (emp1->id < emp2->id) ? -1 : (emp1->id > emp2->id);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Неверное количество аргументов\n");
        return EXIT_FAILURE;
    }

    Employee *employees = NULL;
    size_t count = 0;

    ErrorCode result = read_employees(argv[1], &employees, &count);

    if (result != SUCCESS)
    {
        if (result == FILE_ERROR)
        {
            fprintf(stderr, "Ошибка: не удалось открыть входной файл.\n");
        }
        else if (result == MEMORY_ERROR)
        {
            fprintf(stderr, "Ошибка: недостаточно памяти.\n");
        }
        return EXIT_FAILURE;
    }

    qsort(employees, count, sizeof(Employee), compare_employees);

    if (strcmp(argv[2], "-d") == 0 || strcmp(argv[2], "d") == 0 ||
        strcmp(argv[2], "/d") == 0 || strcmp(argv[2], "/d") == 0)
    {
        for (size_t i = 0; i < count / 2; i++)
        {
            Employee temp = employees[i];
            employees[i] = employees[count - i - 1];
            employees[count - i - 1] = temp;
        }

        result = write_employees(argv[3], employees, count);

        if (result != SUCCESS)
        {
            fprintf(stderr, "Ошибка: не удалось открыть выходной файл.\n");
            free(employees);
            return EXIT_FAILURE;
        }

        free(employees);

        return EXIT_SUCCESS;
    }
    else if (!(strcmp(argv[2], "-a") == 0 || strcmp(argv[2], "a") == 0 ||
               strcmp(argv[2], "/a") == 0))
    {
        fprintf(stderr, "Ошибка: неверный флаг сортировки. Используйте -a или a для сортировки по возрастанию или -d или d для сортировки по убыванию.\n");
        free(employees);
        return EXIT_FAILURE;
    }

    result = write_employees(argv[3], employees, count);

    if (result != SUCCESS)
    {
        fprintf(stderr, "Ошибка: не удалось открыть выходной файл.\n");
        free(employees);
        return EXIT_FAILURE;
    }

    free(employees);

    return EXIT_SUCCESS;
}