#include<stdio.h>

int main()
{
	int i, j;
	
	for(i = 1; i <= 20; i++)
	{
		for(j = 1; j <= 20; j++)
		{
			if(j > 1)
				break;
			else
				printf("* ");
		}
		printf("\n\n");
	}
	return(0);
	
}

/* output *
*

*

*

*

*

*

*

*

*

*

*

*

*

*

*

*

*

*

*

*


	*/

