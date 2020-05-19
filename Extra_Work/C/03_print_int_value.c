#include<stdio.h>

int main(int argc, char *argv[])
{
	int x = 0;
	printf("\n Please enter integer value x: ");
	scanf("%d", &x);
	if(x < 0)
	{
		printf("\n Negative value of x: %d", x);
	}
	else if(x > 0)
	{
		if(0 == x)			// code (x > 0)
			printf("X is zero");
		
		printf("positive value of x : %d", x);
	}
	else
	{
		printf("x is zero : %d", x);
	}
	
}

/** Output **
 Please enter integer value x: 0
x is zero : 0
*/


