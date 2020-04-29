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
    printf("\nenter the number to be produced : ");
    int ins;
    scanf("%d", &ins);
    // sem_wait(&s_empty);
    pthread_mutex_lock(&mutex);
    printf("\nproduced the item : %d\n", ins);
    list[count++] = ins;
    pthread_mutex_unlock(&mutex);
    // sem_post(&s_full);
    pthread_exit(NULL);
}

void *consumer(void *x)
{
    int del;
    // sem_wait(&s_full);
    pthread_mutex_lock(&mutex);
    del = list[--count];

    printf("consumed the item :  %d\n", del);
    pthread_mutex_unlock(&mutex);
    // sem_post(&s_empty);
    pthread_exit(NULL);
}

int main()
{
    sem_open("sem", O_CREAT | O_EXCL, S_IRWXU, 5);
    int i, j;
    printf("\nHow many items wanna produce:  ");
    scanf("%d", &i);
    for (int x = 0; x < i; x++)
    {
        pthread_create(&t_prod[x], NULL, producer, NULL);
        sleep(5);
    }
    for (int x = 0; x < i; x++)
    {
        pthread_join(t_prod[x], NULL);
    }
    printf("\nHow many items wanna consume:  ");
    scanf("%d", &j);

    for (int x = 0; x < j; x++)
    {
        if (x > i)
        {
            printf("\nCan't consume more Items more \n");
            break;
        }
        pthread_create(&t_cons[x], NULL, consumer, NULL);
        sleep(1);
    }
    for (int x = 0; x < j; x++)
    {
        pthread_join(t_cons[x], NULL);
    }
}