#include<stdio.h>

int main()
{
	int i,j,k;
	
	i = 1;
	while(i <= 10)
	{
		printf("\n %d", i);
		j = 1;
		
		while(j <= 5)
		{
			printf("\n \t %d", j);
			
			k = 1;
			while(k <= 3)
			{
				printf("\n \t \t %d", k);
				k++;
			}
			j++;
		}
		i++;
	}
	return(0);
}

/* output *
 1
         1
                 1
                 2
                 3
         2
                 1
                 2
                 3
         3
                 1
                 2
                 3
         4
                 1
                 2
                 3
         5
                 1
                 2
                 3
 2
         1
                 1
                 2
                 3
         2
                 1
                 2
                 3
         3
                 1
                 2
                 3
         4
                 1
                 2
                 3
         5
                 1
                 2
                 3
 3
         1
                 1
                 2
                 3
         2
                 1
                 2
                 3
         3
                 1
                 2
                 3
         4
                 1
                 2
                 3
         5
                 1
                 2
                 3
 4
         1
                 1
                 2
                 3
         2
                 1
                 2
                 3
         3
                 1
                 2
                 3
         4
                 1
                 2
                 3
         5
                 1
                 2
                 3
 5
         1
                 1
                 2
                 3
         2
                 1
                 2
                 3
         3
                 1
                 2
                 3
         4
                 1
                 2
                 3
         5
                 1
                 2
                 3
 6
         1
                 1
                 2
                 3
         2
                 1
                 2
                 3
         3
                 1
                 2
                 3
         4
                 1
                 2
                 3
         5
                 1
                 2
                 3
 7
         1
                 1
                 2
                 3
         2
                 1
                 2
                 3
         3
                 1
                 2
                 3
         4
                 1
                 2
                 3
         5
                 1
                 2
                 3
 8
         1
                 1
                 2
                 3
         2
                 1
                 2
                 3
         3
                 1
                 2
                 3
         4
                 1
                 2
                 3
         5
                 1
                 2
                 3
 9
         1
                 1
                 2
                 3
         2
                 1
                 2
                 3
         3
                 1
                 2
                 3
         4
                 1
                 2
                 3
         5
                 1
                 2
                 3
 10
         1
                 1
                 2
                 3
         2
                 1
                 2
                 3
         3
                 1
                 2
                 3
         4
                 1
                 2
                 3
         5
                 1
                 2
                 3
	
*/
