#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

char * get_string()
{
    char *str = malloc(sizeof(char));
    char c;
    int len = 0;
    str[0] = '\0';

    c = getchar();

    while(c != '\n')
    {
        len++;
        str = realloc(str,sizeof(*str)*len);
        str[len] = '\0';
        str[len -1] = c;
        c = getchar();
    }

    return str;
}

int count_symbol(char * str)
{
    int count = 0;
    for(;*str;str++)
    {
        if('0' > *str || '9' < *str)
            count++;
    }
    return count;
}

int count_digit(char *str)
{
    int count = 0;
    for(;*str;str++)
    {
        if('0' <= *str && '9' >= *str)
            count++;
    }
    return count;
}

int main()
{
    int fb[2],fd[2];

    if(pipe(fb) < 0)
    {
        printf("Can\'t create pipe\n");
        exit(-1);
    }

    if(pipe(fd) < 0)
    {
        printf("Can\'t create pipe\n");
        exit(-1);
    }

    pid_t p = fork();

    if(p == 0)
    {
        char *str;
        int len;
        read(fb[0],&len,sizeof(int));
        str = malloc(sizeof(char)*(len+1));
        read(fb[0],str,len);
        str[len] = '\0';

        len = count_digit(str);

        write(fd[1],&len,sizeof(int));

        exit(0);
    }
    else
    {
        printf("Enter string:");
        char * str = get_string();
        int c = strlen(str);
        int d;

        write(fb[1],&c,sizeof(int));
        write(fb[1],str,c);

        c = count_symbol(str);

        read(fd[0],&d,sizeof(int));

        printf("Count symbol: %d\nCount digit: %d\n",c,d);
    }
}
