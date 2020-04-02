#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
int forkk(int data){
    switch (fork())
    {
    case -1:
        printf("Error forking child process. %s\n", strerror(errno));
        exit(1);
    case 0:
    
        while (data != 1)
        {
            printf("in child data=%d \n", data);
            if (data % 2 == 0)
                data = data / 2;
            else
                data = 3 * data + 1;
        }
        printf("child process completed !!\n");
        break;
    default:
        wait(NULL);
        printf("parent process completed !!\n");
    }
    return data;
}

int main()
{
    int data = 8,result=0;
    printf("input a intger: ");
    scanf("%d", &data );
    result=forkk(data);
    printf("in main =%d\n",result);
    return 0;
}

