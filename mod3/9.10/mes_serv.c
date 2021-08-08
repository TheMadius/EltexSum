#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef struct mymsgbuf
{
    long mtype;
    char mtext[255];
} Data;

typedef struct
{
    int msqid;
    Data frame;
} thread_d;

void *treatment(void *argv)
{
    Data d;
    thread_d dat = *((thread_d *)argv);

    d.mtype = atoi(dat.frame.mtext);
    strcpy(d.mtext, "Done");

    int maxlen = sizeof(Data);

    if (msgsnd(dat.msqid, &d, maxlen, 0) < 0)
    {
        printf("Can\'t send message to queue\n");
        exit(-1);
    }
}

int main()
{
    int msqid;
    char pathname[] = "Makefile";
    int len, maxlen;
    key_t key;
    Data mybuf;

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

    while (1)
    {
        maxlen = sizeof(Data);

        if ((len = msgrcv(msqid, &mybuf, maxlen, 1, 0)) < 0)
        {
            printf("Can\'t receive message from queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
            exit(-1);
        }

        if (mybuf.mtype == 1)
        {
            pthread_t thred;
            thread_d db;
            db.msqid = msqid;
            db.frame = mybuf;

            pthread_create(&thred, NULL, treatment, &db);
            printf("Connect pid # %d\n", atoi(mybuf.mtext));

            pthread_detach(thred);
        }
    }

    msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);

    return 0;
}