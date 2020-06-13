#include<stdio.h>

int main()
{
	int i,j,k;
	
	i = 1;
	do
	{
		printf("\n i : %d", i);
		j = 1;
		do
		{
			printf("\n \t j : %d",j);
			k = 1;
			do
			{
				printf("\n \t \t k = %d", k);
				k++;
				
			}while(k <= 3);
			
			j++;
		}while(j <= 5);
		
		i++;
	}while(i <= 10);
	
	return(0);
}

/* output *
 i : 1
         j : 1
                 k = 1
                 k = 2
                 k = 3
         j : 2
                 k = 1
                 k = 2
                 k = 3
         j : 3
                 k = 1
                 k = 2
                 k = 3
         j : 4
                 k = 1
                 k = 2
                 k = 3
         j : 5
                 k = 1
                 k = 2
                 k = 3
 i : 2
         j : 1
                 k = 1
                 k = 2
                 k = 3
         j : 2
                 k = 1
                 k = 2
                 k = 3
         j : 3
                 k = 1
                 k = 2
                 k = 3
         j : 4
                 k = 1
                 k = 2
                 k = 3
         j : 5
                 k = 1
                 k = 2
                 k = 3
 i : 3
         j : 1
                 k = 1
                 k = 2
                 k = 3
         j : 2
                 k = 1
                 k = 2
                 k = 3
         j : 3
                 k = 1
                 k = 2
                 k = 3
         j : 4
                 k = 1
                 k = 2
                 k = 3
         j : 5
                 k = 1
                 k = 2
                 k = 3
 i : 4
         j : 1
                 k = 1
                 k = 2
                 k = 3
         j : 2
                 k = 1
                 k = 2
                 k = 3
         j : 3
                 k = 1
                 k = 2
                 k = 3
         j : 4
                 k = 1
                 k = 2
                 k = 3
         j : 5
                 k = 1
                 k = 2
                 k = 3
 i : 5
         j : 1
                 k = 1
                 k = 2
                 k = 3
         j : 2
                 k = 1
                 k = 2
                 k = 3
         j : 3
                 k = 1
                 k = 2
                 k = 3
         j : 4
                 k = 1
                 k = 2
                 k = 3
         j : 5
                 k = 1
                 k = 2
                 k = 3
 i : 6
         j : 1
                 k = 1
                 k = 2
                 k = 3
         j : 2
                 k = 1
                 k = 2
                 k = 3
         j : 3
                 k = 1
                 k = 2
                 k = 3
         j : 4
                 k = 1
                 k = 2
                 k = 3
         j : 5
                 k = 1
                 k = 2
                 k = 3
 i : 7
         j : 1
                 k = 1
                 k = 2
                 k = 3
         j : 2
                 k = 1
                 k = 2
                 k = 3
         j : 3
                 k = 1
                 k = 2
                 k = 3
         j : 4
                 k = 1
                 k = 2
                 k = 3
         j : 5
                 k = 1
                 k = 2
                 k = 3
 i : 8
         j : 1
                 k = 1
                 k = 2
                 k = 3
         j : 2
                 k = 1
                 k = 2
                 k = 3
         j : 3
                 k = 1
                 k = 2
                 k = 3
         j : 4
                 k = 1
                 k = 2
                 k = 3
         j : 5
                 k = 1
                 k = 2
                 k = 3
 i : 9
         j : 1
                 k = 1
                 k = 2
                 k = 3
         j : 2
                 k = 1
                 k = 2
                 k = 3
         j : 3
                 k = 1
                 k = 2
                 k = 3
         j : 4
                 k = 1
                 k = 2
                 k = 3
         j : 5
                 k = 1
                 k = 2
                 k = 3
 i : 10
         j : 1
                 k = 1
                 k = 2
                 k = 3
         j : 2
                 k = 1
                 k = 2
                 k = 3
         j : 3
                 k = 1
                 k = 2
                 k = 3
         j : 4
                 k = 1
                 k = 2
                 k = 3
         j : 5
                 k = 1
                 k = 2
                 k = 3
				 
*/

