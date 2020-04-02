#include <stdio.h> 
#include <stdlib.h> 
#include <sys/ptrace.h>
#include <errno.h>
  
int main(int argc, char *argv[]) 
{ 
    FILE *fptr1, *fptr2; 
    char filename[100], c; 
  
    // Open one file for reading 
    fptr1 = fopen(argv[1], "r"); 
    if (fptr1 == NULL) 
    { 
        printf("Cannot open file %s ,%s \n", argv[1],strerror(errno)); 
        exit(0); 
    } 

    // Open another file for writing 
    fptr2 = fopen(argv[2], "w"); 
    if (fptr2 == NULL) 
    { 
         printf("Cannot open file %s ,%s \n", argv[2],strerror(errno)); 
        exit(0); 
    } 
  
    // Read contents from file 
    c = fgetc(fptr1); 
    while (c != EOF) 
    { 
        fputc(c, fptr2); 
        c = fgetc(fptr1); 
    } 
  
    printf("\nContents copied to %s", argv[2]); 
  
    fclose(fptr1); 
    fclose(fptr2); 
    return 0; 
}
