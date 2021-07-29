/*
Последовательность строк символов. Каждая строка предваряется целым - счетчиком символов. 
Ограничение последовательности - счетчик со значением 0.
*/

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#pragma warning(disable:4996)

bool isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

char* getNull()
{
    char* arr;
    arr = (char*)malloc(sizeof(char) * sizeof(int));

    *((int*)arr) = 0;

    return arr;
}

char* enterData()
{
    char* arr;
    int size = sizeof(int);
    char c = getchar();
    arr = (char*)malloc(sizeof(char) * size);

    while (c != '\n')
    {
        size++;
        arr = (char*)realloc(arr, sizeof(char) * size);
        arr[size - 1] = c;
        c = getchar();
    }

    *((int*)arr) = size - sizeof(int);

    return arr;
}

void printStr(char** arr)
{
    int size = *((int*)(*arr));

    while (size)
    {
        char* p = *arr;
        for (int i = 0; i < size; i++)
        {
            printf("%c", *(p + sizeof(int) + i));
        }

        arr++;
        printf("\n");
        size = *((int*)*arr);
    }
}

int main()
{
    int n;
    char** res;

    printf("Enter count:");
    scanf("%d", &n);
    getchar();

    res = (char**)malloc(sizeof(char*) * (n + 1));

    for (int i = 0; i < n; ++i)
    {
        printf("Enter string #%d: ", i + 1);
        res[i] = enterData();
    }

    res[n] = getNull();

    printf("\nResult:\n");

    printStr(res);
}
