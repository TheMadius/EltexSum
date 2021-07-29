#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#pragma warning(disable:4996)

bool isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

char *getNull()
{
    char * arr;
    arr = malloc(sizeof(char)*sizeof(int));

    *((int *)arr) = 0;
    return arr;
}

char* enterData()
{
    char * arr;
    int size = sizeof(int);
    char c = getchar();
    arr = malloc(sizeof(char)*size);

    *((int *)arr) = 0;

    while (c != '\n')
    {
        size++;
        arr = realloc(arr,sizeof(char)*size);
        arr[size - 1] = c;
        c = getchar();
    }
    
    return arr;
}

void printStr(char** arr)
{
    int size = *((int*)(*arr));
    while(size)
    {
        char * p = *arr;
        for(int i = 0;i < size;i++)
        {
            printf("%c",*( p + sizeof(int) + i));
        }

        arr++;
        printf("\n");
        size = *((int*)arr);
    }
}

int main()
{
    int n;
    char** res;

    printf("Enter count:");
    scanf("%d", &n);
    getchar();

    res = (char **)malloc(sizeof(char*)*(n+1));

    for (int i = 0; i < n; ++i)
    {
        printf("Enter string #%d: ",i+1);
        res[i] = enterData();
    }
    res[n] = getNull();

    printf("\nResult:\n");

    printStr(res);
}
