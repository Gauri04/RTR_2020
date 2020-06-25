#include<stdio.h>


extern int globalCount;

void ChangeCount1()
{
	globalCount = 20;
	printf("\n globalCount from File1: %d", globalCount);
}


