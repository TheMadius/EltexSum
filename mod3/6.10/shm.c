#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>

int get_size_file(FILE *f)
{
    int len;
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);
    return len;
}

int main(int argc, char **argv)
{
    int shm_id;
    char *arr;
    int size_file;
    FILE * f;
    key_t key;
    char nameFile[] = "Makefile";

    f = fopen("shm.c","rb");
    size_file = get_size_file(f);

    if ((key = ftok(nameFile, 0)) < 0)
    {
        perror("Error key generator");
        exit(1);
    }

    if ((shm_id = shmget(key, sizeof(char) * size_file + sizeof(int) + 1, 0666 | IPC_CREAT | IPC_EXCL)) < 0)
    {
        if (shm_id == EEXIST)
        {
            perror("Error i don't know");
            exit(2);
        }
        else
        {
            shm_id = shmget(key, sizeof(char) * size_file + sizeof(int) + 1, 0);
        }
    }


    if ((arr = (char *)shmat(shm_id, NULL, 0)) == (char *)(-1))
    {
        perror("Error read shm");
        exit(3);
    }

    *((int *)arr) = size_file;
    arr+=sizeof(int);
    fread(arr,sizeof(char),size_file,f);
    arr[size_file] = '\0';

    arr-=sizeof(int);

    if (shmdt(arr) < 0)
    {
        perror("Error");
        exit(4);
    }

    return 0;
}