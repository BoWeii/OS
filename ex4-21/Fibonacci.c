#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define MAX 100000
int fibseq[100];
int n = 0;

void *child()
{
    fibseq[0] = 0;
    fibseq[1] = 1;
    for (int a = 2; a < n; a++)
    {
        fibseq[a] = fibseq[a - 1] + fibseq[a - 2];
    }
    pthread_exit(NULL); // 離開子執行緒
}

int main()
{
    printf("input a interger :");
    scanf("%d", &n);
    pthread_t s;
    fibseq[1] = 1;

    pthread_create(&s, NULL, child, NULL);
    pthread_join(s, NULL);

    for (int k = 0; k < n; k++)
    {
        printf("%d,", fibseq[k]);
    }
    return 0;
}