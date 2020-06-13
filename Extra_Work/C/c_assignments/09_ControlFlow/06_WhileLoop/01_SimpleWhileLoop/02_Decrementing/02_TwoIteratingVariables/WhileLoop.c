#include<stdio.h>

int main(void)
{
	int i,j;
	
	i = 10;
	j = 100;
	
	while(i >= 0, j >= 10)
	{
		printf("\n %d \t %d", i,j);
		i--;
		j = j - 10;
		
	}
	return(0);
}

/* output *

 10      100
 9       90
 8       80
 7       70
 6       60
 5       50
 4       40
 3       30
 2       20
 1       10
 
 */

