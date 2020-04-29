#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define size 5

pthread_mutex_t mutex;
pthread_t t_prod[10], t_cons[10];
sem_t s_full, s_empty;

int count = 0;
int list[size];

void *producer(void *x)
{
    while (1)
    {
        sleep(rand() % 5 + 1);
        int ins = rand();
        // sem_wait(&s_empty);
        pthread_mutex_lock(&mutex);
        printf("\nproduced the item : %d\n", ins);
        list[count++] = ins;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *consumer(void *x)
{
    while (1)
    {
        sleep(rand() % 5 + 1);
        int del;
        pthread_mutex_lock(&mutex);
        if (count != 0)
        {
            del = list[--count];
            printf("consumed the item :  %d\n", del);
        }

        pthread_mutex_unlock(&mutex);
    }
    // sem_post(&s_empty);
    pthread_exit(NULL);
}

int main()
{
    // const long int stime = strtol(argv[1], NULL, 0);
    sem_open("sem", O_CREAT | O_EXCL, S_IRWXU, 5);
    int i, j;
    for (i = 0; i < 10; i++)
        pthread_create(&t_prod[i], NULL, producer, NULL);
    for (i = 0; i < 10; i++)
        pthread_create(&t_cons[i], NULL, consumer, NULL);

    sleep(20);
    return (0);
}