#include<stdio.h>
#include<stdlib.h>

int A[5];

// function delcaration
void readWriteOnStaticArray();
void allocateReadWriteFreeDynamicArray();

int main()
{
    readWriteOnStaticArray();
    allocateReadWriteFreeDynamicArray();
    return(0);
    
}

void readWriteOnStaticArray()
{
    int i;
    for(i = 0; i <5; ++i)
    {
        A[i] = (i+1) * 10;
    }

    for(i = 0; i < 5; ++i)
    {
        printf("\nA[%d] : %d", i, A[i]);
    }
}

void allocateReadWriteFreeDynamicArray()
{
    int *p = NULL;
    int i, n;

    p = (int *)malloc(5 * sizeof(int));
    if(p == NULL)
    {
        printf("\n Insufficient memory.. exiting now");
        exit(-1);
    }

    memset(p, 0, 5 * sizeof(int));                      //set array values to 0
    for(i = 0; i <5; ++i)
    {
        p[i] = (i + 1) * 100;
        *(p + i) = (i + 1) * 100;
    }

    for(i = 0; i < 5; i++)
    {
        n = p[i];
        printf("\n*(p + %d) : %d", i, (*p + i));
    }

    free(p);
    p = NULL;
}





