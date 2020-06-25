#include<stdio.h>
#include"File1.c"
#include"File2.c"

int globalCount = 0;

int main()
{
	void ChangeCount();
	void ChangeCount1();
	void ChangeCount2();
	
	ChangeCount();
	ChangeCount1();
	ChangeCount2();
	return(0);
}

void ChangeCount()
{
	globalCount = globalCount + 1;
	printf("\n globalCount : %d", globalCount);
}

/* ouput *

 globalCount : 1
 globalCount from File1: 20
 globalCount from File1: 30
 
 */

