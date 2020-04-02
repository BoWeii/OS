#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int pipeFds[2];
    char buffer[1000];
    char childBuffer[1000];
    if (pipe(pipeFds) < 0)
    {
        printf("Something went wrong creating the pipe! %s\n", strerror(errno));
        exit(1);
    }

    switch (fork())
    {

    case -1:
        printf("Error forking child process. %s\n", strerror(errno));
        exit(1);
    case 0:
        printf("0");
        close(pipeFds[1]);
        ssize_t num_bytes_child = read(pipeFds[0], childBuffer, sizeof(childBuffer));
        close(pipeFds[0]);
        int targetDesc = open(argv[2], O_CREAT | O_WRONLY);
        write(targetDesc, childBuffer, num_bytes_child);
        printf("success");
        break;
    default:
        printf("else ");
        close(pipeFds[0]);
        int fileInDesc = open(argv[1], O_RDONLY);
        ssize_t num_bytes = read(fileInDesc, buffer, sizeof(buffer));
        write(pipeFds[1], buffer, num_bytes);
        close(pipeFds[1]);
    };

    return 0;
}