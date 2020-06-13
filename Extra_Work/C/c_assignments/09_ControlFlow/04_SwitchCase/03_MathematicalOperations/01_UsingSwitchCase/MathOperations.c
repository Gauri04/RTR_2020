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
	
	switch(option)
	{
		case 'A':
		case 'a':
			result = a + b;
			printf("Result for addition of A : %d and B : %d is : %d", a, b, result);
			break;
			
		case 'S':
		case 's':
			if(a >= b)
			{
				result = a - b;
				printf("Result for subtraction of B : %d from A : %d is : %d", b, a, result);
			}
			
			else
			{
				result = b - a;
				printf("Result for subtraction of A : %d from B : %d is : %d", a, b, result);
			}
			break;
		
		case 'M':
		case 'm':
			result = a * b;
			printf("Result for multiplication of A : %d and B : %d is : %d", a, b, result);
			break;
			
		case 'D':
		case 'd':
			printf("\n Enter option in character :");
			printf("\n 'Q' or 'q' or '/' for quotient upon division");
			printf("\n 'R' or 'r' or '%' for remainder upon division : ");
			
			option_division = getch();
			switch(option_division)
			{
				case 'Q':
				case 'q':
				case '/':
					if(a >= b)
					{
						result = a / b;
						printf("Result for division of A : %d and B : %d is : %d", a, b, result);
						
					}
					else
					{
						result = b / a;
						printf("Result for division of B : %d and A : %d is : %d", b, a, result);
					}
					break;
					
				case 'D':
				case 'd':
				case '%':
					if(a >= b)
					{
						result = a % b;
						printf("Result for division of A : %d and B : %d gives remainder : %d", a, b, result);
						
					}
					else
					{
						result = b % a;
						printf("Result for division of B : %d and A : %d gives remainder : %d", b, a, result);
					}
					break;
					
				default:
					printf("\n Invalid character %c entered for division", option_division);
					break;
				
			}
				
			break;
			
		default:
			printf("\n Invalid character %c entered", option_division);
			break;
		
	}
	
	return(0);
	
}

/* output *

 Enter value for 'A' and 'B' :11 12

 Enter option for :
 'A' or 'a' for addition
 'S' or 's' for subtraction
 'M' or 'm' for multiplication
 'D' or 'd' for division
 :
 Enter option in character :
 'Q' or 'q' or '/' for quotient upon division
 'R' or 'r' or '' for remainder upon division : Result for division of B : 12 and A : 11 is : 1
 
 */


