#include<stdio.h>
int main(void)
{
	int i, j;
	
	for(i = 1; i <= 10; i++)
	{
		printf("\n %d", i);
		for(j = 1; j <= 5; j++)
		{
			printf("\n \t %d", j);
		}
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



