#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

int main()
{
    int fb[2];
    int count = 0;
    pipe(fb);

    while(true)
    {
        write(fb[1],"h",1);
        count++;
        printf("Size pipe %d byte\n", count);
    }
}