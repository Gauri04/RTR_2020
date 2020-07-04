#include<stdio.h>

int main()
{
	int grNum;
	int* grPtr;			//grPtr is of type int*
	
	grNum = 7;
	printf("\n Value of num : %d", grNum);
	printf("\n Address of num : %p", &grNum);
	printf("\n Value at address of num : %d", *(&grNum));
	
	// ptr
	grPtr = &grNum;
	printf("\n Value of num : %d", grNum);
	printf("\n Value of ptr : %p", grPtr);
	printf("\n Value at address of num : %d", *grPtr);
	
	return(0);
}

/* output *
 Value of num : 7
 Address of num : 00CFFA38
 Value at address of num : 7
 Value of num : 7
 Value of ptr : 00CFFA38
 Value at address of num : 7
 
 */
 
 