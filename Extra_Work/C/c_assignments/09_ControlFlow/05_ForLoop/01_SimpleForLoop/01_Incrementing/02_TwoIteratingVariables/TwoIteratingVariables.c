#include<stdio.h>
int main()
{
	int i,j;
	printf("\n Printing digits 1 to 10 and 10 to 100");
	
	for(i = 1, j = 10; i <= 10, j <= 100; i++, j = j + 10)
	{
		printf("\n %d \t %d", i, j);
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