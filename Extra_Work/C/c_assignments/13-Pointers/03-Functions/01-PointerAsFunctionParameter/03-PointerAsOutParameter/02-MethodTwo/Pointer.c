#include<stdio.h>
#include<stdlib.h>

int main()
{
	void MathematicalOperations(int, int, int *, int *, int *, int *, int *);
	
	int gra;
	int grb;
	
	int *grSum = NULL;
	int *grDifference = NULL;
	int *grProduct = NULL; 
	int *grRemainder = NULL;
	int *grQuotient = NULL;
	
	
	printf("\n Enter integer value for a : ");
	scanf("%d", &gra);
	
	printf("\n Enter integer value for b : ");
	scanf("%d", &grb);
	
	grSum = (int *)malloc(1 * sizeof(int));
	if(grSum == NULL)
	{
		printf("\n Cannot allocate memory to Sum");
		exit(0);
	}
	
	grDifference = (int *)malloc(1 * sizeof(int));
	if(grDifference == NULL)
	{
		printf("\n Cannot allocate memory to Difference");
		exit(0);
	}
	
	grProduct = (int *)malloc(1 * sizeof(int));
	if(grProduct == NULL)
	{
		printf("\n Cannot allocate memory to Product");
		exit(0);
	}
	
	grRemainder = (int *)malloc(1 * sizeof(int));
	if(grRemainder == NULL)
	{
		printf("\n Cannot allocate memory to Remainder");
		exit(0);
	}
	
	grQuotient = (int *)malloc(1 * sizeof(int));
	if(grQuotient == NULL)
	{
		printf("\n Cannot allocate memory to Quotient");
		exit(0);
	}
	
	
	// all the parameters except gra and grb are out parameteres which will contain -
	// the results of mathematical operations
	MathematicalOperations(gra, grb, grSum, grDifference, grProduct, grRemainder, grQuotient);
	
	printf("\n Sum : %d", *grSum);
	printf("\n Difference : %d", *grDifference);
	printf("\n Product : %d", *grProduct);
	printf("\n Remainder : %d", *grRemainder);
	printf("\n Quotient : %d", *grQuotient);
	
	if(grSum)
	{
		free(grSum);
		grSum = NULL;
		printf("\n Successfully freed ememory allocated to Sum");
	}
	
	if(grDifference)
	{
		free(grDifference);
		grDifference = NULL;
		printf("\n Successfully freed ememory allocated to Difference");
	}
	
	if(grProduct)
	{
		free(grProduct);
		grProduct = NULL;
		printf("\n Successfullt freed ememory allocated to Product");
	}
	
	if(grRemainder)
	{
		free(grRemainder);
		grRemainder = NULL;
		printf("\n Successfully freed ememory allocated to Remainder");
	}
	
	if(grQuotient)
	{
		free(grQuotient);
		grQuotient = NULL;
		printf("\n Successfully freed ememory allocated to Quotient");
	}
	
	
	return(0);	
}
	
void MathematicalOperations(int a, int b, int *sum, int *difference, int *product, int *remainder, int *quotient)
{
	*sum = a + b;
	*difference = a - b;
	*product = a * b;
	*remainder = a % b;
	*quotient = a / b;
}

/* output *

 Enter integer value for a : 10

 Enter integer value for b : 20

 Sum : 30
 Difference : -10
 Product : 200
 Remainder : 10
 Quotient : 0
 Successfully freed ememory allocated to Sum
 Successfully freed ememory allocated to Difference
 Successfullt freed ememory allocated to Product
 Successfully freed ememory allocated to Remainder
 Successfully freed ememory allocated to Quotient
 
 */
 
 

