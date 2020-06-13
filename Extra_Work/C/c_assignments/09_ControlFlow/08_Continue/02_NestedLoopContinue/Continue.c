#include<stdio.h>

int main()
{
	int i,j;
	
	printf("\n Printing odd numbers between 0 to 10");
	printf("\n Printing even numbers between 1 to 10 for every odd number in loop");
	
	for(i = 0; i <= 10; i++)
	{
		if(i % 2 != 0)
		{
			printf("\n i : %d", i);
			for(j = 0; j <= 10; j++)
			{
				if(j % 2 == 0)
					printf("\n \t j : %d", j);
				else
					continue;
			}
		}
		else
			continue;
	}
	return(0);
	
}

/* output *

 Printing odd numbers between 0 to 10
 Printing even numbers between 1 to 10 for every odd number in loop
 i : 1
         j : 0
         j : 2
         j : 4
         j : 6
         j : 8
         j : 10
 i : 3
         j : 0
         j : 2
         j : 4
         j : 6
         j : 8
         j : 10
 i : 5
         j : 0
         j : 2
         j : 4
         j : 6
         j : 8
         j : 10
 i : 7
         j : 0
         j : 2
         j : 4
         j : 6
         j : 8
         j : 10
 i : 9
         j : 0
         j : 2
         j : 4
         j : 6
         j : 8
         j : 10
		 
*/






