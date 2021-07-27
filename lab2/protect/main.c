#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

typedef struct node
{
    char c;
    float v;
} Node;


char** get_string_arr()
{
    char c;
    int len = 0;
    int count = 0;
    char** res = (char**)malloc(sizeof(*res));
    res[0] = NULL;

    c = getchar();

    while (c != '\n')
    {
        char* word = (char*)malloc(sizeof(*word));
        len = 0;
        word[0] = '\0';

        while (c != ' ' && c != '\n')
        {
            len++;
            word = (char*)realloc(word, sizeof(*word) * (len));
            word[len - 1] = c;
            word[len] = '\0';
            c = getchar();
        }

        if (word[0] != '\0')
        {
            count++;
            res = (char**)realloc(res, sizeof(*res) * (count));
            res[count - 1] = word;
            res[count] = NULL;
        }
        else
        {
            free(word);
        }

        if (c == '\n')
            break;

        c = getchar();
    }

    return res;
}

int getCount(Node** p)
{
    int count = 0;
    for (; *p; p++)
    {
        count++;
    }
    return count;
}

Node** addElement(Node** stat, char c)
{
    Node** p = stat;
    bool flag = false;
    int count = getCount(p);

    for (; *p; p++)
    {
        Node* temp = *p;

        if (temp->c == c)
        {
            temp->v += 1;
            flag = true;
        }
    }

    if (!flag)
    {
        count++;
        stat = (Node**)realloc(stat, sizeof(*stat) * (count + 1));
        stat[count] = NULL;
        stat[count - 1] = (Node*)malloc(sizeof(Node));
        stat[count - 1]->v = 1;
        stat[count - 1]->c = c;
    }
    return stat;
}

Node** get_stat(char** word)
{
    int count = 0;

    Node** stat = (Node**)malloc(sizeof(*stat));
    stat[0] = NULL;

    for (; *word; word++)
    {
        char* p = *word;
        int len = strlen(p);
        count += len;
        for (; *p; p++)
        {
            stat = addElement(stat, *p);
        }
    }

    Node** temp = stat;
    for (; *temp; temp++)
        (*temp)->v /= count;

    return stat;
}

void printWord(char** arr)
{
    char** temp = arr;
    int i = 1;
    for (; *temp; temp++)
    {
        printf("%d)%s\n", i, *temp);
        i++;
    }
}
void printStat(Node** arrSt)
{
    if (arrSt == NULL)
    {
        return;
    }

    float max = (*arrSt)->v;
    char cMax = (*arrSt)->c;

    for (;*arrSt;arrSt++)
    {
        printf("Char: %c Frequency: %f\n", (*arrSt)->c, (*arrSt)->v);
        if (max < (*arrSt)->v)
        {
            max = (*arrSt)->v;
            cMax = (*arrSt)->c;
        }
    }
    printf("\nMax: Char: %c(frequency: %f)\n", cMax, max);
}

int main()
{
    char ** arr;
    Node ** arrSt;

    printf("Enter text: ");
    arr = get_string_arr();

    printf("Result:\n");
    printWord(arr);

    printf("\nFrequency:\n");
    arrSt = get_stat(arr);

    printStat(arrSt);


}
