#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
int TOTAL_DOT=1000000;
int THREAD=4;
double total = 0;
pthread_mutex_t mutex;

void *child()
{
    int temp=0;
    double X = ((double)rand() / RAND_MAX)*2-1;
    for (int i=0;i<TOTAL_DOT/THREAD;i++)
    {
        double X = ((double)rand() / RAND_MAX)*2-1;
        double Y = ((double)rand() / RAND_MAX)*2-1;
        double sum=X * X + Y * Y;
        if (sum < 1)
        {
           temp++;
        }
    }
    pthread_mutex_lock(&mutex);
    total += temp;
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
    pthread_exit(NULL); // 離開子執行緒
}

int main()
{
    pthread_t t[4];
    
    for(int i=0;i<THREAD;i++)
    {
        pthread_create(&t[i], NULL, child,NULL);
    }
    for(int i=0;i<THREAD;i++)
    {
        pthread_join(t[i], NULL); // 等待子執行緒執行完成
    }
    
    printf("Pi = %f", 4*total/(TOTAL_DOT));
    return 0;
}