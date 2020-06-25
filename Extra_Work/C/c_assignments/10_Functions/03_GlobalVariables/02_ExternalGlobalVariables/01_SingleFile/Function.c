#include<stdio.h>

int main()
{
	void ChangeCount();
	extern int globalCount;
	
	printf("\n Value of global count before changeCount() is %d", globalCount);
	ChangeCount();
	printf("\n Value of global count after changeCount() is %d", globalCount);
	return(0);
}

int globalCount = 0;

void ChangeCount()
{
	globalCount = 5;
	printf("\n GlobalCount : %d", globalCount);
}

/* ouput *

 Value of global count before changeCount() is 0
 GlobalCount : 5
 Value of global count after changeCount() is 5
 
 */