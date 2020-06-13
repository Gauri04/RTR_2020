#include<stdio.h>

int main(void)
{
	int i,j;
	
	printf("\n Printing digits 1 to 10 and 10 to 100");
	
	i = 1;
	j = 10;
	
	while(i <= 10, j <= 100)
	{
		printf("\n %d \t %d", i, j);
		
		i++;
		j = j + 10; 
	}			
	
	return(0);
}

/* output *

 Printing digits 1 to 10 and 10 to 100
 1       10
 2       20
 3       30
 4       40
 5       50
 6       60
 7       70
 8       80
 9       90
 10      100
 */
 

