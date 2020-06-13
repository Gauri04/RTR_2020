#include<stdio.h>

int main()
{
	int i;
	char ch;
	
	printf("\n Enter 'y' or 'Y' to begin loop");
	printf("\n Enter 'q' or 'Q' to quit the loop");
	
	ch = getch();
	if(ch = 'y' || ch == 'Y')
	{
		while(1)
		{
			printf("\n In loop");
			ch = getch();
			if(ch == 'q' || ch == 'Q')
				break;
			
		}
		printf("\n exiting user controlled loop");
	}
	
	return(0);
}

/* output *

 Enter 'y' or 'Y' to begin loop
 Enter 'q' or 'Q' to quit the loop
 In loop
 In loop
 In loop
 In loop
 In loop
 exiting user controlled loop
 */



