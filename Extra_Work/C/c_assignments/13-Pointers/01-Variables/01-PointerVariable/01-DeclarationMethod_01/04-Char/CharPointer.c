#include<stdio.h>

int main()
{
	char grChar;
	char *grPtr = NULL;			// grPtr is pointer to char
	
	grChar = 'c';
	printf("\n Value of char : %c", grChar);
	printf("\n Address of char : %p", &grChar);
	printf("\n Value at address of char : %c", *(&grChar));
	
	//ptr
	grPtr = &grChar;
	printf("\n\n Value of char : %c", grChar);
	printf("\n Value of ptr : %p", grPtr);
	printf("\n Value at address of num from ptr : %c", *grPtr);
	
	return(0);
	
}	

/* output *

 Value of char : c
 Address of char : 0136FC03
 Value at address of char : c

 Value of char : c
 Value of ptr : 0136FC03
 Value at address of num from ptr : c
 
 */
 
