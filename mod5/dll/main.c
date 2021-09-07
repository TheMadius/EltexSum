#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int multi(int a,int b);

extern int add(int a,int b);

int main(int argc,char** argv)
{
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    printf("Res add = %d\nRes multi = %d\n",add(a,b), multi(a,b));
}