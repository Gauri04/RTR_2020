#include<stdio.h>

extern int globalCount;

void ChangeCount2()
{
	globalCount = 30;
	printf("\n globalCount from File1: %d", globalCount);
}


