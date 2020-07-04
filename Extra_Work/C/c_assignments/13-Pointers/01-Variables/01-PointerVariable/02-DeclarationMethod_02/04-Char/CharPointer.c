#include<stdio.h>

int main()
{
	char grCh;
	char* grPtr = NULL;

	grCh = 'g';
	
	printf("\n Char value : %c", grCh);
	printf("\n Address of char : %p", &grCh);
	printf("\n Value at address of char : %c", *(&grCh));
	
	//ptr
	grPtr = &grCh;
	printf("\n Char Value : %c", grCh);
	printf("\n Address of char from ptr : %p", grPtr);
	printf("\n Value at address of char : %c", *grPtr);
	
	return(0);
	
}

/* output *
 Char value : g
 Address of char : 010FFB1F
 Value at address of char : g
 Char Value : g
 Address of char from ptr : 010FFB1F
 Value at address of char : g
 
 */

