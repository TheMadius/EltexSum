#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

typedef struct node
{
    char c;
    float v;
} Node;


char ** get_string_arr()
{
    char c;
    int len = 0;
    int count = 0; 
    char **res = malloc(sizeof(*res));
    res[0] = NULL;

    c = getchar();

    while(c != '\n')
    {
        char *word = malloc(sizeof(*word));
        len = 0;
        word[0] = '\0';
          
        while(c != ' ' && c != '\n')
        {
            len++;
            word = realloc(word,sizeof(*word)*(len));
            word[len - 1] = c;
            word[len] = '\0';
            c = getchar();
        }
                
        if(word[0] != '\0')
        {
            count++;
            res = realloc(res,sizeof(*res)*(count));
            res[count -1] = word;
            res[count] = NULL;
        }
        else
        {
            free(word);
        }

        if(c == '\n')
            break;

        c = getchar();
    }

    return res;
}

Node ** addElement(Node ** stat,char c)
{
    Node **p = stat;
    bool flag = false;
    int count = 0;

    for(;*p;p)
    {
        Node *temp = *p;
        count++;
        if(temp->c == c)
        {
            temp->v += 1;
            flag = true;
        }
    }

    if(!flag)
    {
        count++;
        stat = realloc(stat,sizeof(*stat)*(count+1));
        stat[count] = NULL;
        stat[count - 1] = malloc(sizeof(Node));
        stat[count - 1]->v = 1;
        stat[count - 1]->c = c;
    }

    return stat;
}

Node ** get_stat(char**word)
{
    int count = 0;

    Node ** stat = malloc(sizeof(*stat));
    stat[0] = NULL;

    for(;*word;word++)
    {
        char*p = *word;
        int len = strlen(p);
        count += len;
        for(;*p;p)
        {
           addElement(stat,*p); 
        }
    }

    return stat;
}

void printWord(char **arr)
{
    char **temp = arr;
    int i = 1;
    for(;*temp;temp++)
    {
        printf("%d)%s\n",i,*temp);
        i++;
    }
}

void delWord(char **arr)
{
    char **temp = arr;
    for(;*temp;temp++)
    {
        free(*temp);
    }
    free(arr);
}

int main()
{
    char** arr;
    arr = get_string_arr();
    printWord(arr);

    delWord(arr);
}