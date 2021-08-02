#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"
#include "stdbool.h"

int main()
{

    close(STDERR_FILENO);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);

    umask(0);

    chdir("/");

    while(true)
    {
    }

}