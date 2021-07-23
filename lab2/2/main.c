#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int countWord(char ** arrWord)
{
    char** p = arrWord;
    for (; *p; p++);
    return p - arrWord;
}
char* getWord(FILE* f)
{
    char ch;
    int len = 0;
    char* word = (char*)malloc(sizeof(char));

    word[0] = '\0';

    while (!feof(f))
    {
        ch = fgetc(f);

        if (ch == ' ' || ch == ',' || ch == '\n')
        {
            return word;
        }
        else
        {
            len++;
            word = (char*)realloc(word, sizeof(*word) * (len + 1));
            word[len - 1] = ch;
            word[len] = '\0';
        }
    }
    return word;
}

int getPos(char* w, char*** words, int size)
{
    int pos = 0;

    for (int i = 0; i < size; i++)
    {
        char** p = words[i];
        for (; *p; p++)
        {
            if (strcmp(w, *p) < 0)
                return pos;
            pos++;
        }
    }
    return pos;
}

void pressWord(char* w, char*** words, int size, int count)
{
    int pos = getPos(w, words, size);
    int rePos = 0;
    char** p = NULL;

    for (int i = 0; i < size; i++)
    {
        int len = countWord(words[i]);
        p = words[i];
        for (; *p; p++)
        {
            if (rePos >= pos)
            {
                char* temp = *p;
                *p = w;
                w = temp;
            }
            rePos++;
        }
        if (rePos >= pos && len < count - 1)
        {
            *p = w;
            *(p+1) = NULL;
        }
    }
}

char*** getWords(int size, char* fileName, int *sizeOfArray)
{
    FILE* f = fopen(fileName, "r");
    char*** words = NULL;
    int len = 0;
    int countWord = 0;

    while (!feof(f))
    {
        char* w = getWord(f);
  
        if (countWord >= (size - 1) * len)
        {
            len++;
            words = (char***)realloc(words, sizeof(char**) * len);
            words[len - 1] = (char**)malloc(sizeof(char*) * size);
            words[len - 1][0] = NULL;
        }

        pressWord(w ,words, len, size);
        countWord++;
    }

    *sizeOfArray = len;

    return words;
}

void  printArr(int len, char*** words)
{
    for (int i = 0; i < len; i++)
    {
        char** p = words[i];
        for (; *p; p++)
        {
            printf("%s ", *p);
        }
        printf("\n");
    }
}

int main(int argc, char** argv)
{
    int size = atoi(argv[1]) + 1;
    int len;
    char* fileName = (char*)malloc(sizeof(*fileName) * 50);
    char*** words;
    printf("Enter file name: ");
    scanf("%s", fileName);

    words = getWords(size, fileName, &len);

    printArr(len, words);
}
