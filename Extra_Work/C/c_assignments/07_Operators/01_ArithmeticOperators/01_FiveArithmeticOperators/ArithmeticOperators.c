#include<stdio.h>

int main(void)
{
	int a;
	int b;
	int result;
	
	//code
	printf("\n\n");
	printf("Enter A number :");
	scanf("%d", &a);
	
	printf("\n Enter Another number :");
	scanf("%d", &b);
	
	printf("\n\n");
	
	result = a + b;
	printf("addition of A = %d and B = %d is %d.\n", a,b,result);
	
	result = a - b;
	printf("subtraction of A= %d and b= %d gives %d\n", a,b,result);
	
	result = a * b;
	printf("multiplication of A= %d and B= %d gives %d.\n", a,b,result);
	
	result = a / b;
	printf("division of A= %d and B= %d gives %d.\n", a,b,result);
	
	result = a % b;
	printf("division of A= %d and B= %d gives remainder %d.\n", a,b,result);
	
	return(0);
}


/* output *
Enter A number :6

 Enter Another number :3


addition of A = 6 and B = 3 is 9.
subtraction of A= 6 and b= 3 gives 3
multiplication of A= 6 and B= 3 gives 18.
division of A= 6 and B= 3 gives 2.
division of A= 6 and B= 3 gives remainder 0.
*/
