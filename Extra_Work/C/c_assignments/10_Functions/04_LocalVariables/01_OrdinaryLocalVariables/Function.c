#include<stdio.h>

int main()
{
	int a = 5;
	void ChangeCount(void);
	
	printf("\n A : %d", a);
	
	ChangeCount();
	ChangeCount();
	
	return(0);
}

void ChangeCount(void)
{
	int localCount = 0;
	localCount = localCount + 1;
	printf("\n localCount : %d", localCount);
}

/* ouput *
 A : 5
 localCount : 1
 localCount : 1
 
 */


