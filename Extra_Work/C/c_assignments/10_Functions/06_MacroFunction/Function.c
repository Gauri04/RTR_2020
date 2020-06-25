#include<stdio.h>
#define MAX_NUMBER(a,b) (a > b ? a : b)

int main()
{
	int n1, n2;
	float f1, f2;
	int result;
	float fResult;
	
	printf("\n Enter two integers to find the max : ");
	scanf("%d%d", &n1, &n2);
	result = MAX_NUMBER(n1,n2);
	printf("\n Max number : %d", result);
	
	printf("\n Enter two float numbers to find the max : ");
	scanf("%f%f", &f1, &f2);
	fResult = MAX_NUMBER(f1,f2);
	printf("\n Max number : %f", fResult);
	
	return(0);
	
}

/* ouput *
 Enter two integers to find the max : 4 5

 Max number : 5
 Enter two float numbers to find the max : 0.212 0.222

 Max number : 0.222000
 
 */