#include<stdio.h>

int main()
{
	char option, ch = '\0';
	
	printf("\n Once the infinite loop begins, enter 'Q' or 'q' to Quit the loop");
	printf("\n Enter 'Y' or 'y' to initiate user controlled infinite loop :");
	
	option = getch();
	if(option == 'Y' || option == 'y')
	{
		for(;;)
		{
			printf("\n In loop..");
			ch = getch();
			if(ch == 'Q' || ch == 'q')
			break;
		}
	}
	
	printf("\n Exiting user controlled for loop");
	return(0);
}

/* output *

 Once the infinite loop begins, enter 'Q' or 'q' to Quit the loop
 Enter 'Y' or 'y' to initiate user controlled infinite loop :
 In loop..
 In loop..
 In loop..
 In loop..
 Exiting user controlled for loop
 */
