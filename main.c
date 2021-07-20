#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "math.h"

int reWord(char *str)
{
    int len = strlen(str);

    for(int i = 0; i < len / 2; i++)
    {
        if(str[i] != str[len - 1 - i])
            return 0;
    }
    return 1;
}

char *gerRandStr(int len)
{
    char *str = (char*)malloc(sizeof(char)*(len+1));

    srand(time(NULL));

    for(int i = 0; i < len; i++)
        {
            char r = 'a' + rand()%('z' - 'a' + 2);
            if(r == 123)
                r = 32;
            str[i] = r;
        }

    str[len] = '\0';
    return str;
}

char *gerRandStrA(int len)
{
    char *str = (char*)malloc(sizeof(char)*(len+1));

    srand(time(NULL));

    for(int i = 0; i < len / 2; i++)
    {   
        char r = 'a' + rand()%('z' - 'a' + 2);
        if(r == 123)
            r = 32;

        str[i] = r;
        str[len - 1 - i] = r;
    }

    if(len%2 != 0)
    {
        char r = 'a' + rand()%('z' - 'a' + 2);
        if(r == 123)
            r = 32;
        str[len/2] = r;
    }

    str[len] = '\0';
    return str;
}

char * getStr(int len)
{
    srand(time(NULL));
    double r = ((double)rand())/RAND_MAX;    

    if(r >= sin(len))
        return gerRandStrA(len);
    else
        return gerRandStr(len);

}

int main(int argc, char** argv)
{
    for(int i = 0; i < atoi(argv[1]);i++)
    {
        char *str = getStr(atof(argv[2]));

        if(reWord(str))
            printf("%s\n",str);

        free(str);
    }
    
}