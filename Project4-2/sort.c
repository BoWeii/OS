#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
int data[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
int result[10];
pthread_mutex_t mutex;

void *sort1()
{
    // printf("1 thread\n");
    int i, j, temp;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (data[j] > data[i])
            {
                int temp = data[j];
                data[j] = data[i];
                data[i] = temp;
            }
        }
    }

    pthread_mutex_lock(&mutex);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
    pthread_exit(NULL); // 離開子執行緒
}
void *sort2()
{
    // printf("2 thread\n");
    int i, j, temp;
    for (int i = 5; i < 10; ++i)
    {
        for (int j = 5; j < i; ++j)
        {
            if (data[j] > data[i])
            {
                int temp = data[j];
                data[j] = data[i];
                data[i] = temp;
            }
        }
    }

    pthread_mutex_lock(&mutex);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
    pthread_exit(NULL); // 離開子執行緒
}

void *merge()
{
    int a[5], b[5];
    for (int i = 0; i < 5; i++)
    {
        a[i] = data[i];
        b[i] = data[i + 5];
    }
    int a_index = 0, b_index = 0;
    for (int i = 0; i < 10; i++)
    {
        if (a_index >= 5)
            result[i] = b[b_index++];
        else if (b_index >= 5)
            result[i] = a[a_index++];
        else if (a[a_index] > b[b_index])
            result[i] = b[b_index++];
        else
            result[i] = a[a_index++];
    }
    pthread_exit(NULL); // 離開子執行緒
}

int main()
{
    pthread_t t[3];
    int a[2] = {0, 5};

    pthread_create(&t[0], NULL, sort1, NULL);
    pthread_create(&t[1], NULL, sort2, NULL);
    pthread_create(&t[2], NULL, merge, NULL);
    for (int i = 0; i < 3; i++)
        pthread_join(t[i], NULL); // 等待子執行緒執行完成

    // pthread_join(t[2], NULL);
    printf("origin:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d, ", data[i]);
    }
    printf("\nafter:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d, ", result[i]);
    }
    return 0;
}