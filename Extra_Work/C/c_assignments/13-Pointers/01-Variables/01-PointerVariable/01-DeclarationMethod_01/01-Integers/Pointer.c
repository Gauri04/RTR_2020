#include<stdio.h>

int main()
{
	int grNum;
	int *grPtr = NULL;					//grPtr is pointer to integer
	
	grNum = 10;
	
	// num
	printf("\n Address of num : %p", &grNum);
	printf("\n Value of num : %d", grNum);
	printf("\n Value at address of num : %d", *(&grNum));

	// ptr
	grPtr = &grNum;
	printf("\n\n Value of num : %d",grNum);
	printf("\n Address of num from ptr : %p", grPtr);
	printf("\n Value at address of num from ptr : %d", *grPtr);
	
	return(0);
}

/* ouput *

 Address of num : 00B5FB58
 Value of num : 10
 Value at address of num : 10

 Value of num : 10
 Address of num from ptr : 00B5FB58
 Value at address of num from ptr : 10
 
 */