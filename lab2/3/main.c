/*
Функция получает линейный массив целых, находит в нем последовательности подряд возрастающих значений и возвращает их в динамическом массиве указателей 
на линейные массивы (аналог двумерного массива). В каждом из линейных динамических массивов содержится копия возрастающей последовательности, начиная с 
индекса 1, а под индексом 0 содержится его длина. Невозрастающие значения включаются в отдельный массив, добавляемый в конец (или начало) массива указателей.
*/

#include "stdio.h"
#include "stdlib.h"

int * getSub(int *arr,int start,int end)
{
    int * res = malloc(sizeof(int)*(end - start + 2));

    res[0] = end - start + 1;

    for(int i = 1; i <= res[0]; i++)
    {
        res[i] = arr[start + i - 1];
    }
    return res;
}

int ** getChain(int * arr,int count,int *size)
{
    int start = 0;
    int end = 0;
    int countLine = 0;
    int ** arrM = NULL;
    int * out = malloc(sizeof(int));
    out[0] = 0;

    for(int i = 0; i < count; i++)
    {
        start = i;
        for( ;arr[i] < arr[(i == count - 1)? i : i + 1 ]; i++);
        end = i;

        if(start == end)
        {
            out[0]++;
            out = realloc(out, sizeof(int)*(out[0]+1));
            out[out[0]] = arr[i];
        }
        else
        {
            countLine++;
            arrM = realloc(arrM, sizeof(char*)*countLine);
            arrM[countLine - 1] = getSub(arr,start,end);
        }
    }
    if(out[0] != 0)
    {
        countLine++;
        arrM = realloc(arrM, sizeof(char*)*countLine);
        arrM[countLine - 1] = out;
    }
    
    *size = countLine;

    return arrM;
}

void printArr(int ** arrChain,int size)
{
    for(int i = 0; i < size;i++)
    {
        int len = arrChain[i][0];
        printf("(len = %d) ",len);

        for(int k = 1 ; k <= len;k++)
        {
            printf("%d ",arrChain[i][k]);
        } 
        
        printf("\n");
    }
}

int main()
{
    int **arrChain;
    int count,size;
    int *arr;

    printf("Enter count num: ");
    scanf("%d",&count);

    arr = malloc(sizeof(int)*count);

    for(int i = 0; i < count;i++)
    {
        printf("%d) ", i + 1);
        scanf("%d",&arr[i]);
    }

    arrChain = getChain(arr,count,&size);

    printArr(arrChain,size);

}