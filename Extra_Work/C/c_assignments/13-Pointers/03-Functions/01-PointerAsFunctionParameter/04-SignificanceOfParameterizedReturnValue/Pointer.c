#include<stdio.h>

enum
{
	NEGATIVE = -1,
	ZERO,
	POSITIVE
};

int main()
{
	int Difference(int, int, int*);
	int gra, grb;
	int grAnswer, grRet;
	
	printf("\n Enter integer value for a : ");
	scanf("%d", &gra);
	
	printf("\n Enter integer value for b : ");
	scanf("%d", &grb);
	
	grRet = Difference(gra, grb, &grAnswer);
	printf("\n Difference of %d and %d is : %d", gra, grb, grAnswer);
	
	if(grRet == POSITIVE)
		printf("\n Difference of %d and %d is positive", gra, grb);
	else if(grRet == NEGATIVE)
		printf("\n Difference of %d and %d is negative", gra, grb);
	else
		printf("\n Difference of %d and %d is zero", gra, grb);
	
	return(0);	
	
}


int Difference(int a, int b, int *diff)
{
	// diff is an out parameter therefore no need to return
	*diff = a - b;
	
	if(*diff > 0)
		return(POSITIVE);
	else if(*diff < 0)
		return(NEGATIVE);
	else
		return(ZERO);
	
}


/* output *

 Enter integer value for a : 10

 Enter integer value for b : 20

 Difference of 10 and 20 is : -10
 Difference of 10 and 20 is negative
 
 */




