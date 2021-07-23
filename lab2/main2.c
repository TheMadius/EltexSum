#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char * getWord(FILE * f)
{
    char ch;
    int len = 0;
    char *word = malloc(sizeof(char));

    word[0]='\0';

    while (!feof(f))
    {
        ch = fgetc(f);

        if(ch == ' ' || ch == ',' || ch == '\n')
        {
            return word;
        }
        else
        {
            len++;
            word = realloc(word,sizeof(*word)*(len + 1));
            word[len - 1] = ch;
            word[len] = '\0';
        }
    }
    return word;
}

int getPos(char *w ,char *** words, int size)
{
    int pos = 0;

    for(int i = 0 ; i < size; i++)
    {
        char ** p = words[0];

        for(;p;p++)
        {
            int res = strcmp(w,*p);

            if(res < 0 )
                return pos;
            pos++;
        }
    }

    return pos;
}

void pressWord(char *w,char ***words,int pos, int size)
{
    int p = 0;

    for(int i = size - 1 ; i >= 0; i--)
    {
        char ** p = words[0];
        for(;p;p++);

    }
}

char *** getWords(int size, char* fileName)
{
    FILE * f = fopen(fileName,"r");
    char ***words = NULL;
    int l = 0;

    while(!feof(f))
    {
        char * w = getWord(f);

        printf("%s\n",w);
        
        int pos = getPos(w, words, l);
        
        printf("%d\n",pos);

        if(pos >= (size - 1)*l)
        {
            l++;
            words = realloc(words,sizeof(char**)*l);
            words[l-1] = malloc(sizeof(char*)*size);
            words[l-1][0] = NULL;
        }
        
        //pressWord(w,words,pos,l);

    }

    return words;
}

int main(int argc, char** argv)
{
    int size = atoi(argv[1]) + 1;
    char * fileName = malloc(sizeof(*fileName)*50);
    char ***words ;
    printf("Enter file name: ");
    scanf("%s",fileName);

    words = getWords(size, fileName);
}