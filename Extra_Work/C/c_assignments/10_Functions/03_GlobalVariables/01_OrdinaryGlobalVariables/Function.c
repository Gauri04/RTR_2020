#include<stdio.h>

int globalCount = 0;

int main()
{
	void ChangeCount1();
	void ChangeCount2();
	void ChangeCount3();
	
	ChangeCount1();
	ChangeCount2();
	ChangeCount3();
	
	return(0);
	
}

void ChangeCount1()
{
	globalCount = 10;
	printf("\n changeCount1() Global count : %d", globalCount);
}

void ChangeCount2()
{
	globalCount++;
	printf("\n changeCount2() Global count : %d", globalCount);
}

void ChangeCount3()
{
	globalCount = 30;
	printf("\n changeCount3() Global count : %d", globalCount);
}

/* ouput *

 changeCount1() Global count : 10
 changeCount2() Global count : 11
 changeCount3() Global count : 30
 
 */










