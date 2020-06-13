#include<stdio.h>

int main()
{
	int i, j;
	
	i = 1;
	do
	{
		printf("\n i : %d", i);
		
		j = 1;
		do
		{
			printf("\n \t j : %d", j);
			j++;
		}while(j <= 5);
		
		i++;
	}while(i <= 10);
	
	return(0);
}

/* output *

 i : 1
         j : 1
         j : 2
         j : 3
         j : 4
         j : 5
 i : 2
         j : 1
         j : 2
         j : 3
         j : 4
         j : 5
 i : 3
         j : 1
         j : 2
         j : 3
         j : 4
         j : 5
 i : 4
         j : 1
         j : 2
         j : 3
         j : 4
         j : 5
 i : 5
         j : 1
         j : 2
         j : 3
         j : 4
         j : 5
 i : 6
         j : 1
         j : 2
         j : 3
         j : 4
         j : 5
 i : 7
         j : 1
         j : 2
         j : 3
         j : 4
         j : 5
 i : 8
         j : 1
         j : 2
         j : 3
         j : 4
         j : 5
 i : 9
         j : 1
         j : 2
         j : 3
         j : 4
         j : 5
 i : 10
         j : 1
         j : 2
         j : 3
         j : 4
         j : 5
		 
*/




