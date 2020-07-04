#include<stdio.h>

int main()
{
	int grNum;
	int *grPtr = NULL;
	int **grPPtr = NULL;
	
	grNum = 5;
	printf("\n *** Before ptr = &num ***");
	printf("\n Value of num : %d", grNum);
	printf("\n Address of num : %p", &grNum);
	printf("\n Value at address of num : %d", *(&grNum));
	
	// ptr
	grPtr = &grNum;
	
	printf("\n\n *** After ptr = &num ***");
	printf("\n Value of num : %d", grNum);
	printf("\n Address of num : %p", grPtr);
	printf("\n Value at address of num : %d", *grPtr);
	
	// pptr
	grPPtr = &grPtr;
	
	printf("\n\n *** After pptr = &ptr ***");
	printf("\n Value of num : %d", grNum);
	printf("\n Address of num : %p", grPtr);
	printf("\n Address of ptr : %p", grPPtr);
	printf("\n Value at address of ptr : %p", *grPPtr);
	printf("\n Value at address of num : %d", **grPPtr);
	
	return(0);
}

/* output *

 *** Before ptr = &num ***
 Value of num : 5
 Address of num : 008FFA04
 Value at address of num : 5

 *** After ptr = &num ***
 Value of num : 5
 Address of num : 008FFA04
 Value at address of num : 5

 *** After pptr = &ptr ***
 Value of num : 5
 Address of num : 008FFA04
 Address of ptr : 008FFA00
 Value at address of ptr : 008FFA04
 Value at address of num : 5
 
 */












