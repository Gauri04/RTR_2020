#include<stdio.h>

int main()
{
	double grNum;
	double *grPtr = NULL;				// grPtr is pointer type of double
	
	grNum = 455.6755;	
	
	printf("\n value of num : %lf", grNum);
	printf("\n Address of num : %p", &grNum);
	printf("\n Value at address of num : %lf", *(&grNum));
	
	//ptr
	grPtr = &grNum;
	printf("\n Pointer \n Value of num : %lf", grNum);
	printf("\n Value of ptr : %p", grPtr);
	printf("\n Value at address of num : %lf", *grPtr);
	
	return(0);
}

/* ouput *
 value of num : 455.675500
 Address of num : 00DDF79C
 Value at address of num : 455.675500
 Pointer
 Value of num : 455.675500
 Value of ptr : 00DDF79C
 Value at address of num : 455.675500
 
 */



