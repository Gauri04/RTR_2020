#include<stdio.h>

int main()
{
	void MathematicalOperations(int, int, int *, int *, int *, int *, int *);
	
	int gra;
	int grb;
	
	int grSum, grDifference, grProduct, grRemainder, grQuotient;
	
	printf("\n Enter integer value for a : ");
	scanf("%d", &gra);
	
	printf("\n Enter integer value for b : ");
	scanf("%d", &grb);
	
	// all the parameters except gra and grb are out parameteres which will contain -
	// the results of mathematical operations
	MathematicalOperations(gra, grb, &grSum, &grDifference, &grProduct, &grRemainder, &grQuotient);
	
	printf("\n Sum : %d", grSum);
	printf("\n Difference : %d", grDifference);
	printf("\n Product : %d", grProduct);
	printf("\n Remainder : %d", grRemainder);
	printf("\n Quotient : %d", grQuotient);
	
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
 Enter integer value for a : 100

 Enter integer value for b : 50

 Sum : 150
 Difference : 50
 Product : 5000
 Remainder : 0
 Quotient : 2
 
 */
 
 













