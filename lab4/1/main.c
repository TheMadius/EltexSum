#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#pragma warning(disable:4996)

bool isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

char* enterData()
{
    char* arr;
    int size = 0;
    int n = 0;
    char c = getchar();
    char* digit = (char*)malloc(sizeof(char));

    arr = (char*)malloc(sizeof(char));
    arr[0] = '\0';
    digit[0] = '\0';

    while (true)
    {
        if (isDigit(c))
        {
            size++;
            digit = (char*)realloc(digit, sizeof(char) * (size + 1));
            digit[size] = '\0';
            digit[size - 1] = c;
        }
        else
        {
            if (size != 0)
            {
                int num = atoi(digit);
                int* temp;

                arr = (char*)realloc(arr, sizeof(char) * (n + sizeof(int) + 2));
                arr[n + 1 + sizeof(int)] = '\0';
                arr[n] = '\1';

                temp = (int*)(arr + n + 1);
                *temp = num;

                size = 0;
                free(digit);

                digit = (char*)malloc(sizeof(char));
                digit[0] = '\0';
                n += sizeof(int) + 1;
            }

            if (c == '\n')
                break;

            n++;
            arr = (char*)realloc(arr, sizeof(char) * (n + 1));
            arr[n] = '\0';
            arr[n - 1] = c;
        }

        c = getchar();
    }
    return arr;
}

void printStr(char* arr)
{
    char* temp = arr;
    for (; *temp; temp++)
    {
        if (*temp == '\1')
        {
            int* num;
            temp++;
            num = (int*)(temp);
            temp += sizeof(int) - 1;

            printf("%d", *num);
        }
        else
        {
            printf("%c", *temp);
        }
    }

    printf("\n");
}

int main()
{
    int n;
    char** res;

    printf("Enter count:");
    scanf("%d", &n);
    getchar();

    res = (char **)malloc(sizeof(char*)*n);

    for (int i = 0; i < n; ++i)
    {
        printf("Enter string #%d: ",i+1);
        res[i] = enterData();
    }
    printf("Result:\n");

    for (int i = 0; i < n; ++i)
    {
        printStr(res[i]);
    }
}
