#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define DOT 1000000
double total = 0;

void *child()
{

    double X = ((double)rand() / RAND_MAX)*2-1;
    for (int i = 0; i < DOT; ++i)
    {
        double X = ((double)rand() / RAND_MAX)*2-1;
        double Y = ((double)rand() / RAND_MAX)*2-1;
        double sum=X * X + Y * Y;
        if (sum < 1)
        {
            total += 1;
        }
    }
    pthread_exit(NULL); // 離開子執行緒
}

int main()
{
    pthread_t t;
    pthread_create(&t, NULL, child,NULL);
    
    pthread_join(t, NULL); // 等待子執行緒執行完成
    printf("Pi = %f", 4*total/(DOT));
    return 0;
}