#include<stdio.h>

int main()
{
	int grNum;
	int *grPtr = NULL;
	int *grCopyPtr = NULL;
	
	grNum = 5;
	grPtr = &grNum;
	
	printf("\n Before Copy : ");
	printf("\n\n num : %d", grNum);
	printf("\n &num : %p", &grNum);
	printf("\n *(&num) : %d", *(&grNum));
	printf("\n ptr : %p", grPtr);
	printf("\n *ptr : %d", *grPtr);
	
	//copy
	grCopyPtr = grPtr;
	printf("\n\n ***** AFTER CPOY *****");
	printf("\n \n num : %d", grNum);
	printf("\n &num : %p", &grNum);
	printf("\n *(&num) : %d", *(&grNum));
	printf("\n ptr : %p", grPtr);
	printf("\n *ptr : %d", *grPtr);
	printf("\n copyPtr : %p", grCopyPtr);
	printf("\n *copyPtr : %d", *grCopyPtr);
	
	return(0);	
}

/* output *
 Before Copy :

 num : 5
 &num : 00AFFC98
 *(&num) : 5
 ptr : 00AFFC98
 *ptr : 5

 ***** AFTER CPOY *****

 num : 5
 &num : 00AFFC98
 *(&num) : 5
 ptr : 00AFFC98
 *ptr : 5
 copyPtr : 00AFFC98
 *copyPtr : 5
 
 */
 
 


