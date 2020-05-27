#include<stdio.h>

int main(void)
{
	int a;
	int b;
	int x;
	
	printf("\n\n");
	printf("Enter a number ");
	scanf("%d", &a);
	printf("Enter another number ");
	scanf("%d", &b);
	
	// saving original value of a to another variable
	x = a;
	a+= b; // a= a+b
	printf("\n addition of a : %d and b : %d is %d", x,b,a);
	
	x = a;
	a-= b;
	printf("\n subtraction of a : %d and b : %d is %d", x,b,a);
	
	x = a;
	a*= b;
	printf("\n multiplication of a : %d and b : %d is %d", x,b,a);
	
	x = a;
	a/= b; // a = a/b
	printf("\n division of a : %d and b : %d gives quotient %d", x,b,a);
	
	x = a;
	a%= b;
	printf("\n division of a : %d and b : %d gives remainder %d", x,b,a);
	
	return(0);
	
}

/** output **

Enter a number 10
Enter another number 5

 addition of a : 10 and b : 5 is 15
 subtraction of a : 15 and b : 5 is 10
 multiplication of a : 10 and b : 5 is 50
 division of a : 50 and b : 5 gives quotient 10
 division of a : 10 and b : 5 gives remainder 0
 */










