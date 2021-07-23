/*
Функция получает строку, находит самый внутренний фрагмент в скобках и вырезает его. Операция повторяется до тех пор, 
пока не останется скобок. Полученные фрагменты и остаток строки вернуть в динамическом массиве указателей.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char * getSub(int start, int end, char * arr)
{
    int len = end - start;
    char * str = malloc(sizeof(*str)*(len+1));

    for(int i = start; i < end; i++)
    {
        str[i - start] = arr[i];
    }
    str[len] = '\0';
    
    return str;
}

char ** getSubStrings(char* str, int * n)
{
    if(str == NULL)
    {
        return NULL;
    }

    char ** arr = NULL;
    int len = strlen(str);
    int start, end;
    int size = 0;

    for(int i = 0; i < len; i++)
    {
        if('(' == str[i])
        {
            i++;
            start = i++;

            while (str[i] != ')')
            {
                i++;

                if(i >= len)
                {   
                    *n = size;
                    return arr;
                }
            }

            end = i;

            size ++;
            arr = realloc(arr,sizeof(*arr)*(size));

            arr[size - 1] = getSub(start,end,str);  
        }    
    }

    *n = size;
    return arr;
}

void printText(char **arrStr,int len)
{
    if(len == 0 || arrStr == NULL)
    {
        printf("Null\n");
        return;
    }
    for(int i = 0; i < len;i++)
    {
        printf("%d) %s\n",i+1,arrStr[i]);
    }
}


int main()
{
    char * str = malloc(sizeof(*str)*256);
    char ** arrStr;
    int len;

    printf("Enter string: ");
    scanf("%s",str);

    arrStr = getSubStrings(str,&len);

    printText(arrStr,len);
}