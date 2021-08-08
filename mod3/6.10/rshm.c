#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>

int main(int argc,char** argv)
{
    int shm_id;
    int * arr; 
    char * lis;
    key_t key;
    char nameFile[] = "Makefile";

    if((key = ftok(nameFile, 0)) < 0)
    {
        perror("Error key generator");
        exit(1);
    }

    if((shm_id = shmget(key, sizeof(int) , 0)) < 0)
    {
        perror("Error get");
        exit(2);
    }

    if((arr = (int *)shmat(shm_id,NULL,0)) == (int*)(-1))
    {
        perror("Error read shm");
        exit(3);
    }

    if((shm_id = shmget(key,sizeof(char)*(*arr)+ sizeof(int) + 1, 0)) < 0)
    {
        perror("Error get");
        exit(2);
    }

    if((lis = (char *)shmat(shm_id,NULL,0)) == (char*)(-1))
    {
        perror("Error read shm");
        exit(3);
    }

    lis+=sizeof(int);

    printf("%s\n",lis);

    if(shmdt(arr) < 0)
    {
        perror("Error");
        exit(4);
    }

    lis-=sizeof(int);

    if(shmdt(lis) < 0)
    {
        perror("Error");
        exit(4);
    }

    shmctl(shm_id,IPC_RMID,NULL);

    return 0;
}