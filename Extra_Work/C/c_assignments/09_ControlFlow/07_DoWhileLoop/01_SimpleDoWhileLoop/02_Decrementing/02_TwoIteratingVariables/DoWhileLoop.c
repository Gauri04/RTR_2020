#include<stdio.h>

int main()
{
	int i, j;
	
	printf("\n Printing digits 10 to 1 and 100 to 10");
	i = 10;
	j = 100;
	do
	{
			printf("\n %d \t %d", i, j);
			i--;
			j = j - 10;
	}while(i >= 1, j >= 10);
	
	return(0);

}

/* output *

 Printing digits 10 to 1 and 100 to 10
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

