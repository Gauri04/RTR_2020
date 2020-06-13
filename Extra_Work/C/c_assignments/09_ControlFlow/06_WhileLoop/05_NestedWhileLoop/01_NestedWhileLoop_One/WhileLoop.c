#include<stdio.h>

int main()
{
	int i,j;
	
	i = 1;
	while(i <= 10)
	{
		printf("\n %d", i);
		j = 1;
		while(j <= 5)
		{
			printf("\n \t %d", j);
			j++;
		}
		i++;
	}
	return(0);
}

/* output *

 1
         1
         2
         3
         4
         5
 2
         1
         2
         3
         4
         5
 3
         1
         2
         3
         4
         5
 4
         1
         2
         3
         4
         5
 5
         1
         2
         3
         4
         5
 6
         1
         2
         3
         4
         5
 7
         1
         2
         3
         4
         5
 8
         1
         2
         3
         4
         5
 9
         1
         2
         3
         4
         5
 10
         1
         2
         3
         4
         5
		 
*/


