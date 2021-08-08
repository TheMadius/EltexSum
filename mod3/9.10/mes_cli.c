#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>

#define LAST_MESSAGE 255

typedef struct
{
    long mtype;
    char mtext[255];
} Data;

int main()
{
    int msqid;
    key_t key;
    Data mybuf;
    int len, maxlen;
    char pathname[] = "Makefile";
    pid_t p = getpid();

    if ((key = ftok(pathname, 0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    maxlen = sizeof(Data);
    mybuf.mtype = 1;

    sprintf(mybuf.mtext,"%d",p);  

    if (msgsnd(msqid, &mybuf, maxlen, 0) < 0)
    {
        printf("Can\'t send message to queue\n");
        exit(-1);
    }

    while(true)
    {
        if((msgrcv(msqid, &mybuf, maxlen, p, 0)) < 0){
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }

        if(mybuf.mtype == p)
        {
            printf("Successful connection\n");
            printf("Messag server: %s\n",mybuf.mtext);
            break;
        }
    }

    return 0;
}