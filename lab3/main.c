#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "locale.h"
#include "conio.h"

#pragma warning(disable:4996)

typedef struct student
{
    char* last_name;
    int num_book;
    char faculty[20];
    char gtoup[10];
} Student;

int comp(const Student* i, const Student* j)
{
    return strcmp(i->last_name,j->last_name);
}

char* get_string()
{
    char* str = (char*)malloc(sizeof(char));
    char c;
    int len = 0;
    str[0] = '\0';

    c = getchar();

    if (c == '\n')
        c = getchar();

    while (c != '\n')
    {
        len++;
        str = (char*)realloc(str,sizeof(*str)*(len));
        str[len] = '\0';
        str[len - 1] = c;
        c = getchar();
    }

    return str;
}

void printEntry(Student* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("\nЗапись №%d\n",i+1);
        printf("Фамилия: %s\n",arr[i].last_name);
        printf("Номер зачетной книжки: %d\n", arr[i].num_book);
        printf("Факультет: %s\n", arr[i].faculty);
        printf("Группа: %s\n",arr[i].gtoup);
    }
}

Student* addEntry(Student* arr, int* size)
{
    Student std;

    printf("Введите фамилию: ");
    std.last_name = get_string();

    printf("Введите номер зачетной книжки: ");
    scanf("%d", &(std.num_book));

    printf("Введите факультет: ");
    scanf("%s", std.faculty);

    printf("Введите группу: ");
    scanf("%s", std.gtoup);

    (*size)++;

    arr = (Student*)realloc(arr,sizeof(*arr)*(*size));
    arr[*size - 1] = std;

    return arr;
}

void delEntry(Student* arr, int* size, int n)
{
    if (n > *size)
        return;

    for (int i = n - 1; i < (*size) - 1; i++)
        arr[i] = arr[i + 1];

    (*size)--;

    arr = (Student*)realloc(arr,sizeof(Student)*(*size));
}

void reEntry(Student* arr, int size, int n)
{
    if (n > size)
        return;

    printf("Введите фамилию: ");
    arr[n - 1].last_name = get_string();

    printf("Введите номер зачетной книжки: ");
    scanf("%d", &(arr[n - 1].num_book));

    printf("Введите факультет: ");
    scanf("%s", arr[n - 1].faculty);

    printf("Введите группу: ");
    scanf("%s", arr[n - 1].gtoup);
}
void findEntry(Student* arr,int size,int mod,char* str)
{
    int res = 0;
    for (int i = 0; i < size; ++i)
    {
        switch (mod)
        {
            case 1:
            {
                if (!(strcmp(str,arr[i].last_name)))
                {
                    printf("\nЗапись №%d\n", i + 1);
                    printf("Фамилия: %s\n", arr[i].last_name);
                    printf("Номер зачетной книжки: %d\n", arr[i].num_book);
                    printf("Факультет: %s\n", arr[i].faculty);
                    printf("Группа: %s\n", arr[i].gtoup);
                }
                res++;
                break;
            }
            case 2:
            {
                if (atoi(str) == arr[i].num_book)
                {
                    printf("\nЗапись №%d\n", i + 1);
                    printf("Фамилия: %s\n", arr[i].last_name);
                    printf("Номер зачетной книжки: %d\n", arr[i].num_book);
                    printf("Факультет: %s\n", arr[i].faculty);
                    printf("Группа: %s\n", arr[i].gtoup);
                }
                res++;

                break;
            }
            case 3:
            {
                if (!(strcmp(str, arr[i].faculty)))
                {
                    printf("\nЗапись №%d\n", i + 1);
                    printf("Фамилия: %s\n", arr[i].last_name);
                    printf("Номер зачетной книжки: %d\n", arr[i].num_book);
                    printf("Факультет: %s\n", arr[i].faculty);
                    printf("Группа: %s\n", arr[i].gtoup);
                }
                res++;

                break;
            }
            case 4:
            {
                if (!(strcmp(str, arr[i].gtoup)))
                {
                    printf("\nЗапись №%d\n", i + 1);
                    printf("Фамилия: %s\n", arr[i].last_name);
                    printf("Номер зачетной книжки: %d\n", arr[i].num_book);
                    printf("Факультет: %s\n", arr[i].faculty);
                    printf("Группа: %s\n", arr[i].gtoup);
                }
                res++;

                break;
            }
        default:
            break;
        }
    }

    if (res == 0)
    {
        printf("\nЗапись не найдена\n");
    }
}

int countStud(Student* arr, int size, char* str)
{
    int res = 0;
    for (int i = 0; i < size; ++i)
    {
            if (!(strcmp(str, arr[i].faculty)))
            {
                res++;
            }
    }

    return res;
}

Student* openFile(int* size,char * nameFile)
{
    Student* arr;
    FILE* f = fopen(nameFile, "rb");

    fread(size, sizeof(int), 1, f);

    arr = (Student*)malloc(sizeof(Student)*(*size));

    for (int i = 0; i < *size; i++)
    {
        int n;
        fread(&n, sizeof(int), 1, f);
        arr[i].last_name = (char*)malloc(sizeof(char) * (n + 1));
        fread(arr[i].last_name, sizeof(char), n, f);
        arr[i].last_name[n] = '\0';
        fread(&(arr[i].num_book), sizeof(int), 1, f);
        fread(arr[i].faculty, sizeof(arr[i].faculty), 1, f);
        fread(arr[i].gtoup, sizeof(arr[i].gtoup), 1, f);
    }
    fclose(f);
    return arr;
}

void saveFile(Student* arr, int size, char* str)
{
    FILE* f = fopen(str, "wb");

    fwrite(&size,sizeof(int),1,f);
    for (int i = 0; i < size; ++i)
    {
        int len = strlen(arr[i].last_name);
        fwrite(&len,sizeof(int),1,f);

        fwrite(arr[i].last_name,sizeof(char),len,f);
        fwrite(&arr[i].num_book,sizeof(int),1,f);
        fwrite(arr[i].faculty,sizeof(arr[i].faculty),1,f);
        fwrite(arr[i].gtoup,sizeof(arr[i].gtoup),1,f);
    }
    fclose(f);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Student* arr = NULL;
    int size = 0;
    char c;

    while (true)
    {
        system("cls");
        printf("1 - Ввод новой записи\n2 - Загрузка из файла\n3 - Сохранение в файл\n4 - Просмотр записей\n5 - Сортировка записей\n6 - Удаление записи\n7 - Изменение записи\n8 - Поиск записи\n9 - Вычислить количество студентов\n0 - Выход\n");
        printf("Ввод: ");
        c = getch();

        switch (c)
        {
        case '1':
            system("cls");
            arr = addEntry(arr, &size);
            break;
        case '2':
        {
            system("cls");
            printf("Введите имя файла: ");
            char *str = get_string();
            if (arr != NULL)
                free(arr);
            arr = openFile(&size , str);
            break;
        }

        case '3':
        {
            system("cls");
            printf("Введите имя файла: ");
            char* str = get_string();
            saveFile(arr, size, str);
            break;
        }
        case '4':
        {
            system("cls");
            printEntry(arr, size);
            getch();
            break;
        }
        case '5':
        {
            system("cls");
            qsort(arr, size, sizeof(Student), (int(*) (const void*, const void*)) comp);
            printf("Сортировка завершена.......");
            getch();
            break;
        }
        case '6':
        {
            system("cls");
            printEntry(arr, size);
            printf("\nКакую запись удалить? ");
            int n;
            scanf("%d", &n);
            delEntry(arr, &size, n);
            break;
        }
        case '7':
        {
            system("cls");
            printEntry(arr, size);
            printf("\nКакую запись изменить? ");
            int n;
            scanf("%d", &n);
            reEntry(arr, size, n);
            break;
        }
        case '8':
        {
            system("cls");
            int mod;
            char* str;
            printf("Поиск по:\n1 - Фамилии\n2 - Номеру зачетной книжки\n3 - Факультету\n4 - Группе\n");
            mod = getch() - '0';
            printf("\nЧто нужно найти? ");
            str = get_string();
            system("cls");
            findEntry(arr, size,mod, str);
            getch();
            break;
        }
        case '9':
        {
            system("cls");
            printf("\nКакой факультет? ");
            char* str = get_string();
            int kol = countStud(arr, size, str);
            printf("Количество студентов на факультете %s: %d", str,kol);
            getch();
        }
            break;
        case '0':
        {
            if (arr != NULL)
                free(arr);
            exit(0);
        }
            break;
        default:
            break;
        }
    }
}
