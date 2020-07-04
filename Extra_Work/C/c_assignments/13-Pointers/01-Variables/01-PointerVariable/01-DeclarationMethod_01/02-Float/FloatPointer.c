#include<stdio.h>

int main()
{
	float grNum;
	float *grPtr = NULL;				// grPtr is pointr to float
	
	grNum = 9.5f;
	
	printf("\n Value of num : %f", grNum);
	printf("\n Address of num : %p", &grNum);
	printf("\n Value at address of num : %f", *(&grNum));
	
	
	//ptr
	grPtr = &grNum;
	printf("\n\n Pointer");
	printf("\n Value of num : %f", grNum);
	printf("\n Address of num from ptr : %p", grPtr);
	printf("\n Value at address of num : %f", *grPtr);
	
	return(0);
}

/* ouput *

 Value of num : 9.500000
 Address of num : 012FF81C
 Value at address of num : 9.500000

 Pointer
 Value of num : 9.500000
 Address of num from ptr : 012FF81C
 Value at address of num : 9.500000
 
 */
 
 