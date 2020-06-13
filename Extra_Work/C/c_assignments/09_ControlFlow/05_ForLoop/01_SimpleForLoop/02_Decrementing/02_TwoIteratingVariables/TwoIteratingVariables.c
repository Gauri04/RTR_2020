#include<stdio.h>

int main()
{
	int i, j;
	
	printf("\n Printing digits 10 to 1 and 100 to 10");
	
	for(i = 10, j = 100; i >= 1, j >= 10; i--, j = j - 10)
	{
		printf("\n %d \t %d", i, j);
	}
	
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
