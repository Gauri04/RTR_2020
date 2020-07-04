#include<stdio.h>

int main()
{
	void SwapNumbers(int*, int*);
	int gra, grb;
	
	printf("\n Enter integer value for a : ");
	scanf("%d", &gra);
	
	printf("\n Enter integer value for b : ");
	scanf("%d", &grb);
	
	printf("\n\n Before Swapping : ");
	printf("\n a : %d", gra);
	printf("\n b : %d", grb);
	
	SwapNumbers(&gra,&grb);
	
	printf("\n\n After Swapping: ");
	printf("\n a : %d", gra);
	printf("\n b : %d", grb);
	
	return(0);
}

void SwapNumbers(int *x, int *y)
{
	int temp;
	
	printf("\n\n **** In SwapNumber *****");
	
	printf("\n\t Before Swapping : ");
	printf("\n\t x : %d", *x);
	printf("\n\t y : %d", *y);
	
	temp = *x;
	*x = *y;
	*y = temp;
	
	printf("\n\t After Swapping : ");
	printf("\n\t x : %d", *x);
	printf("\n\t y : %d", *y);
	
	printf("\n\n **** End of SwapNumber ****");	
}

/* output *

 Enter integer value for a : 10

 Enter integer value for b : 20


 Before Swapping :
 a : 10
 b : 20

 **** In SwapNumber *****
         Before Swapping :
         x : 10
         y : 20
         After Swapping :
         x : 20
         y : 10

 **** End of SwapNumber ****

 After Swapping:
 a : 20
 b : 10
 
 */




