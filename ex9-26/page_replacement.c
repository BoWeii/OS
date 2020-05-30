#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ReferenceLength 10

typedef struct
{
    int *PageFrameList;
    int *elementTime;
} PageFrame;

int ReferenceSZ, FrameNR;

int index1;

PageFrame memory;

int *ReferenceString;
int FIFO();
int FIFOInsert();
int LRU();
int LRUInsert();

void generateReferenceString()
{
    int i;
    srand(time(0));
    ReferenceString = (int *)malloc(sizeof(int) * ReferenceLength);
    printf("The randomized Reference String: ");
    for (i = 0; i < ReferenceLength; i++)
    {
        ReferenceString[i] = rand() % ReferenceSZ;
        printf("%d ", ReferenceString[i]);
    }
    printf("\n");
}

void initializePageFrame()
{
    int i;
    memory.PageFrameList = (int *)malloc(sizeof(int) * FrameNR);
    memory.elementTime = (int *)malloc(sizeof(int) * FrameNR);
    for (i = 0; i < FrameNR; i++)
    {
        memory.elementTime[i] = i;
        memory.PageFrameList[i] = -1;
    }
}
// void initializePageFrame2()
// {
//     int i;
//     memory.PageFrameList = (int *)malloc(sizeof(int) * FrameNR);
//     memory.elementCount = 0;
//     for (i = 0; i < FrameNR; i++)
//     {
//         memory.PageFrameList[i] = i;
//     }
// }

void printPageFrame()
{
    int i;
    for (i = 0; i < FrameNR; i++)
    {
        printf("Frame %d: %2d, ", i + 1, memory.PageFrameList[i]);
    }
    printf("\n");
}

void printReferenceString()
{
    int i;
    printf("The Same Reference String: ");
    for (i = 0; i < ReferenceLength; i++)
    {
        printf("%d ", ReferenceString[i]);
    }
    printf("\n");
}

int FIFO()
{
    int PagefaultCount = 0;
    int i;

    for (i = 0; i < ReferenceLength; i++)
    {
        PagefaultCount += FIFOInsert(ReferenceString[i]);
        printPageFrame();
    }

    return PagefaultCount;
}
int FIFOInsert(int PageNumber)
{

    for (int i = 0; i < FrameNR; i++)
    {
        if (memory.PageFrameList[i] == PageNumber)
        {
            return 0;
        }
        else if (memory.PageFrameList[i] == -1)
        {
            memory.PageFrameList[i] = PageNumber;
            index1 = (i + 1) % FrameNR;
            return 1;
        }
    }
    memory.PageFrameList[index1] = PageNumber;
    index1 = (index1 + 1) % FrameNR;
    return 1;
}
int LRU()
{
    int PagefaultCount = 0;
    int i;
    for (i = 0; i < ReferenceLength; i++)
    {
        PagefaultCount+=LRUInsert(ReferenceString[i]);
        printPageFrame();
    }
    return PagefaultCount;
}
void reduceTime()
{
    for (int i = 0; i < FrameNR; i++)
    {
        if(memory.elementTime[i]!=0) memory.elementTime[i] -= 1;
    }
}
int LRUInsert(int PageNumber)
{
    int fault=0;
    for (int i = 0; i < FrameNR; i++)
    {
        
        if (memory.PageFrameList[i] == PageNumber)//相同
        {
            memory.elementTime[i] = FrameNR  ;
            reduceTime();
            return 0;
        }
        else if (memory.PageFrameList[i] == -1)//空白
        {
            memory.PageFrameList[i] = PageNumber;
            memory.elementTime[i] = FrameNR ;
            fault=1;
        }
        if(fault) {
            reduceTime();
            return 1;
        }
    }
    for (int i = 0; i < FrameNR; i++)
    {
    
        if (memory.elementTime[i]==0){ //最舊
            memory.PageFrameList[i]=PageNumber;
            memory.elementTime[i] = FrameNR ;
            fault=1;
        }
        if(fault) {
            reduceTime();
            return 1;
        }
    }
    
    
    return 0;
}

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("Command format: Test <reference string size> <number of page frames>");
        return -1;
    }

    ReferenceSZ = atoi(argv[1]);
    FrameNR = atoi(argv[2]);
    index1 = 0;

    generateReferenceString();

    initializePageFrame();
    printf("page fault of FIFO: %d\n", FIFO());
    free(memory.PageFrameList);

    printf("\n");
    printf("\n");

    printReferenceString();

    initializePageFrame();
    printf("page fault of LRU: %d\n", LRU());

    free(memory.PageFrameList);
    free(ReferenceString);

    return 0;
}
