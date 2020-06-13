#include<stdio.h>

int main()
{
	char ch;
	
	printf("\n Press 'q' or 'Q' to quit the loop once it begins");
	printf("\n Press 'y' or 'Y' to begin the loop");
	
	ch = getch();
	
	if(ch == 'y' || ch == 'Y')
	{
		do
		{
			printf("\n In loop..");
			ch = getch();
			if(ch == 'q' || ch == 'Q')
				break;
		}while(1);
	}
	printf("\n exiting user controlled infinite loop");
	return(0);
	
}

/* output *

 Press 'q' or 'Q' to quit the loop once it begins
 Press 'y' or 'Y' to begin the loop
 In loop..
 In loop..
 In loop..
 In loop..
 In loop..
 In loop..
 exiting user controlled infinite loop
 */

