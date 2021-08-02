#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

int main()
{

    int fd, result;
    size_t size;
    char resstring[14];
    char name[] = "aaa.fifo";

    (void)umask(0);

    if ((fd = open(name, O_RDONLY)) < 0)
    {

        printf("Can\'t open FIFO for reading\n");
        exit(-1);
    }

    size = read(fd, resstring, 14);

    if (size < 0)
    {

        printf("Can\'t read string\n");
        exit(-1);
    }

    printf("%s\n", resstring);

    close(fd);

    return 0;
}