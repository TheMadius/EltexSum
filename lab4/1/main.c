#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

bool isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

char * enterData()
{
    char * arr;
    int size = 0;
    char c = getchar();
    char *digit = malloc(sizeof(char));
    
    arr = malloc(sizeof(char));
    arr[0] = '\0';
    digit[0] = '\0';

    while(c != '\n')
    {
        if(isDigit(c))
        {
            size++;
            digit = realloc(digit,sizeof(char)*(size+1));
            digit[size] = '\0';
            digit[size - 1] = c;
        }
        else
        {
            if(size != 0)
            {
                int num = atoi(digit);
                int n = strlen(arr);
                int * temp;
                
                arr = realloc(arr,sizeof(char)*(n + sizeof(int) + 2));
                arr[n + sizeof(int)] = '\0';
                arr[n] = '\1';
                temp = (int *) arr + n + 1;
                *temp = num; 

                size = 0;
                free(digit);
                
                digit = malloc(sizeof(char));
                digit[0] = '\0';

            }

                int n = strlen(arr);
                n++;
                arr = realloc(arr,sizeof(char)*(n+1));
                arr[n] = '\0';
                arr[n - 1] = c; 
        }

        c = getchar();
    }
    return arr;
}

int main()
{
    int n;
    char * res;

    printf("Enter count:");
    scanf("%d",&n);
    getchar();
    res = enterData();
    
    printf("%s\n",res);
}