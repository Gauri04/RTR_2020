#include<stdio.h>

int main(void)
{
	int a = 5;
	int b = 10;
	
	
	printf("\n \n");
	printf("A = %d\n", a);
	printf("A = %d\n", a++);
	printf("A = %d\n", a);
	printf("A = %d\n\n", ++a);
	
	printf("B = %d\n", b);
	printf("B = %d\n", b--);
	printf("B = %d\n", b);
	printf("B = %d\n", --b);
	
	return(0);
}

/** output **
A = 5
A = 5
A = 6
A = 7

B = 10
B = 10
B = 9
B = 8
*/
