#include<stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	void Add();
	int Subtract();
	void Multiply(int, int);
	int Divide(int, int);
	
	int a_multiplication,b_multiplication;
	int a_division, b_division, result_division;
	int result_subtraction;
	
	Add();
	
	result_subtraction = Subtract();
	printf("\n Subtraction = %d", result_subtraction);
	
	printf("\n Enter two numbers : ");
	scanf("%d%d", &a_multiplication, &a_multiplication);
	Multiply(a_multiplication,a_multiplication);
	
	printf("\n Enter two numbers : ");
	scanf("%d%d", &a_division, &b_division);
	result_division = Divide(a_division,b_division);
	printf("\n Division = %d", result_division);
	
	return(0);
}

void Add()
{
	int a,b,result;
	
	printf("\n Enter two numbers : ");
	scanf("%d%d", &a, &b);
	result = a + b;
	printf("\n addition : %d", result);
}

int Subtract()
{
	int num1, num2,subtraction;
	
	printf("\n Enter two numbers : ");
	scanf("%d%d", &num1, &num2);
	
	subtraction = num1 - num2;
	return(subtraction);
}

void Multiply(int x, int y)
{
	int multiply;
	multiply = x * y;
	printf("\n Multiplication = %d", multiply);
}

int Divide(int x, int y)
{
	int division;
	division = x / y;
	return(division);
}

/* output *

  Enter two numbers : 3 3

 addition : 6
 Enter two numbers : 4 5

 Subtraction = -1
 Enter two numbers : 2 3

 Multiplication = 9
 Enter two numbers : 40 4

 Division = 10
 */





