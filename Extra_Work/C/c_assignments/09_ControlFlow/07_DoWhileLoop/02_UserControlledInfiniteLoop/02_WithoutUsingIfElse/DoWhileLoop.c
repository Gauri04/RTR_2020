#include<stdio.h>

int main()
{
	char ch;
	
	printf("\n Press 'q' or 'Q' to quit the loop once it begins");
	printf("\n Press 'y' or 'Y' to begin the loop");
	
	ch = getch();
	
	do
	{
		do
		{
			printf("\n In loop..");
			ch = getch();
		}while(ch != 'q' && ch != 'Q');
		
		printf("\n exiting user controlled infinite loop \n Do you want to enter the loop again ? y / n ? : ");
		ch = getch();
	
	}while(ch == 'y' || ch == 'Y');
	
	printf("\n exiting user controlled infinite loop");
	return(0);
	
}

/* output *

 Press 'q' or 'Q' to quit the loop once it begins
 Press 'y' or 'Y' to begin the loop
 In loop..
 exiting user controlled infinite loop
 Do you want to enter the loop again ? y / n ? :
 In loop..
 exiting user controlled infinite loop
 Do you want to enter the loop again ? y / n ? :
 exiting user controlled infinite loop
 
 */