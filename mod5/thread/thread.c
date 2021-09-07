#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct {
    int id;
    int spead_mine;
    int *stock;
} DataInPthread;

pthread_mutex_t m;

void * mine(void * argv)
{
    srand(time(NULL));

    DataInPthread *data = (DataInPthread *) argv;

    while (true)
     {    
        int r = 1 + rand() % 2;
        sleep(r);

        pthread_mutex_lock(&m);

        if(*(data->stock) <= 0) {
            printf("The miner # %d has finished working as the mine is empty\n",data->id);
            pthread_mutex_unlock(&m);
            break;
        }

        *(data->stock) -= data->spead_mine;

        printf("Mine id = %d, left in the mine %d\n",data->id,(*(data->stock) < 0)?0:*(data->stock));

        pthread_mutex_unlock(&m);
    }

    free(data);
}

int main(int argc, char **argv)
{
    int countMin = atoi(argv[1]);
    int spead = atoi(argv[3]);
    int *stock = malloc(sizeof(int));

    pthread_t *miners = malloc(sizeof(pthread_t)*countMin);

    *stock = atoi(argv[2]);

    pthread_mutex_init(&m, NULL);

    for(int i = 0; i < countMin; i++)
    {
        DataInPthread *data = malloc(sizeof(DataInPthread));
        
        data->id = i;
        data->spead_mine = spead;
        data->stock = stock;

        pthread_create(&miners[i], NULL, mine, data);
    }

    for(int i = 0; i < countMin; i++)
    {
        pthread_join(miners[i], NULL);
    }

    free(stock);
    free(miners);
    pthread_mutex_destroy(&m);

    return 0;
}