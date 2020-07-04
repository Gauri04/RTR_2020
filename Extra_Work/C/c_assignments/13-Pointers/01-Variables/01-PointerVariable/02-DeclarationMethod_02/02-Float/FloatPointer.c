#include<stdio.h>

int main()
{
	float grNum;
	float* grPtr = NULL; 		// grPtr is of type float*
	
	grNum = 5.5f;
	printf("\n Value of num : %f", grNum);
	printf("\n Address of num : %p", &grNum);
	printf("\n Value at address of num : %f", *(&grNum));
	
	
	// ptr
	grPtr = &grNum;
	printf("\n\n Value of num : %f", grNum);
	printf("\n Address of num from ptr : %p", grPtr);
	printf("\n Value at address of num : %f", *grPtr);
	
	return(0);
}

/* output *
 Value of num : 5.500000
 Address of num : 00B9FE20
 Value at address of num : 5.500000

 Value of num : 5.500000
 Address of num from ptr : 00B9FE20
 Value at address of num : 5.500000
 */

