#include<stdio.h>

int main()
{
	double grNum;
	double* grPtr = NULL;				// grPtr of type double*
	
	grNum = 9999.99;	
	
	printf("\n value of num : %lf", grNum);
	printf("\n Address of num : %p", &grNum);
	printf("\n Value at address of num : %lf", *(&grNum));
	
	//ptr
	grPtr = &grNum;
	printf("\n \n Pointer");
	printf("\n Value of num : %lf", grNum);
	printf("\n Value of ptr : %p", grPtr);
	printf("\n Value at address of num : %lf", *grPtr);
	
	return(0);
}

/* output *

 value of num : 9999.990000
 Address of num : 012FFAEC
 Value at address of num : 9999.990000

 Pointer
 Value of num : 9999.990000
 Value of ptr : 012FFAEC
 Value at address of num : 9999.990000
 
 */



