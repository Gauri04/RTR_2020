#include<stdio.h>
int main(void)
{
	
	int a,b, result;
	char option, option_division;
	
	printf("\n Enter value for 'A' and 'B' :");
	scanf("%d %d", &a, &b);
	
	printf("\n Enter option for :");
	printf("\n 'A' or 'a' for addition");
	printf("\n 'S' or 's' for subtraction");
	printf("\n 'M' or 'm' for multiplication");
	printf("\n 'D' or 'd' for division \n : ");
	
	option = getch();
	
	if(option == 'A' || option == 'a')
	{
		result = a + b;
		printf("\n Addition of A : %d and B : %d is %d", a, b, result);
	}
	
	else if(option == 'S' || option == 's')
	{
		if(a >= b)
		{
			result = a - b;
			printf("\n Subtraction of A : %d - B : %d is %d", a, b, result);
		}
		else
		{
			result = b - a;
			printf("\n Subtraction of B : %d - A : %d is %d", b, a, result);
		}
		
	}
	
	else if(option == 'm' || option == 'M')
	{
		result = a * b;
		printf("\n Multiplication of A : %d and B : %d is %d", a, b, result);
	}
	
	else if(option == 'D' || option == 'd')
	{
		printf("\n Enter the option in character :");
		printf("\n 'Q' or 'q' for quotient");
		printf("\n 'R' or 'r' for remainder \n :");
		
		option_division = getch();
		
		if(option_division == 'Q' || option_division == 'q')
		{
			if(a >= b)
			{
				result = a / b;
				printf("\n Division of A : %d divided by B : %d gives quotient %d", a, b, result);
			}
			else
			{
				result = a / b;
				printf("\n Division of B : %d divided by A : %d gives quotient %d", b, a, result);
			}
		}
		
		else if(option_division == 'R' || option_division == 'r')
		{
			if(a >= b)
			{
				result = a % b;
				printf("\n Division of A : %d divided by B : %d gives remainder %d", a, b, result);
			}
			else
			{
				result = a % b;
				printf("\n Division of B : %d divided by A : %d gives remainder %d", b, a, result);
			}
		}
		
		else
		{
			printf("\n Invalid character entered for division");
		}
		
	}
	
	else
	{
		printf("\n Invalid character entered");
	}
	
	return(0);
}

/* output *
 Enter value for 'A' and 'B' :20 10

 Enter option for :
 'A' or 'a' for addition
 'S' or 's' for subtraction
 'M' or 'm' for multiplication
 'D' or 'd' for division
 :
 Enter the option in character :
 'Q' or 'q' for quotient
 'R' or 'r' for remainder
 :
 Division of A : 20 divided by B : 10 gives remainder 0
 
 */

