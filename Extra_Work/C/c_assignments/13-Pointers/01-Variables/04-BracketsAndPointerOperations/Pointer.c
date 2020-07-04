#include<stdio.h>

int main()
{
	int grNum;
	int *grPtr = NULL;
	int grAns;
	grNum = 5;
	grPtr = &grNum;
	
	printf("\n num : %d", grNum);
	printf("\n address of num : %p", &grNum);
	printf("\n Value at address of num : %d", *(&grNum));
	printf("\n\n Value of num : %d", grNum);
	printf("\n Address of num from ptr : %p", grPtr);
	printf("\n Value at address of num from ptr : %d", *grPtr);
	
	// operations
	printf("\n \n *** Pointer *** \n ptr : %p", grPtr);
	// Address + 10
	printf("\n Answer (ptr + 10) is : %p", (grPtr + 10));
	// Value at address + 10
	printf("\n Answer of *(ptr + 10) is : %d", *(grPtr + 10));
	// Value + 10
	printf("\n Answer pf (*ptr + 10) is : %d", (*grPtr + 10));
	
	// pre-increment ptr RTL (Right to Left increment), ptr = 6
	++*grPtr;
	printf("\n Answer of ++*ptr : %d", *grPtr);
	
	// RTL increment i.e ptr++ then display value of it. 
	*grPtr++;
	printf("\n Answer of *ptr++ is : %d", *grPtr);
	
	(*grPtr)++;
	printf("\n Answer of (*ptr)++ is : %d", *grPtr);
	
	return(0);
}




