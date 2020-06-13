#include<stdio.h>

int main(void)
{
	int a;
	a = 5;
	
	if(a)
	{
		printf("\n If block 1, a exists and has value %d", a);
	}
	
	a = -5;
	
	if(a)
	{
		printf("\n If block 2, a exists and has value %d", a);
	}
	
	a = 0;
	if(a)
	{
		printf("\n If block 3, a exists and has value %d", a);
	}
	
	printf("\n All three stmts are done");
	
	return(0);
	
}

/* output 

 If block 1, a exists and has value 5
 If block 2, a exists and has value -5
 All three stmts are done
 */




