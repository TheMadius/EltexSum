/*
Программа для иллюстрации работы двух нитей исполнения
Каждая нить исполнения просто увеличивает на 1 разделяемую переменную a.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *mythread(void *dummy)
{

pthread_t mythid; 

mythid = pthread_self();

a = a+1;

printf("Thread %ld, Calculation result = %d\n", mythid, a);

return NULL;
}

int main()
{
pthread_t thid[2], mythid;
int result;
for(int i = 0; i < 2; i++)
    result = pthread_create( &thid[i], (pthread_attr_t *)NULL, mythread, NULL);

if(result != 0){
printf ("Error on thread create, return value = %d\n", result);
exit(-1);
}

for(int i = 0; i < 2; i++)
    printf("Thread created, thid = %ld\n", thid[i]);

mythid = pthread_self();

a = a+1;

printf("Thread %ld, Calculation result = %d\n", mythid, a);

for(int i = 0; i < 2; i++)
    pthread_join(thid[i], (void **)NULL);

return 0;
}