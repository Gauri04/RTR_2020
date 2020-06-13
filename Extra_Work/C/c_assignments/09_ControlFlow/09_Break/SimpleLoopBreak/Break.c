#include<stdio.h>
int main()
{
	int i;
	char ch;
	
	printf("\n Printing numbers ranging 0 to 100 at every user input until user enters 'q' or 'Q'");
	
	for(i =0 ; i <= 100; i++)
	{
		printf("\n %d", i);
		ch = getch();
		if(ch == 'q' || ch == 'Q')
			break;
	}
	return(0);
	
}

/* output *
 Printing numbers ranging 0 to 100 at every user input until user enters 'q' or 'Q'
 0
 1
 2
 3
 4
 5
 6
 7
 */