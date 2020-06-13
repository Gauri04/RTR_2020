#include<stdio.h>

int main()
{
	int iNumFrom, iNum, i;
	printf("\n Enter the number you want to begin iteration  with and how many digits the number should print : ");
	scanf("%d%d", &iNumFrom, &iNum);
	
	i = iNumFrom;
	while(i <= (iNumFrom + iNum))
	{
		printf("\n %d", i);
		i++;
	}
	return(0);
}

/* output *
 Enter the number you want to begin iteration  with and how many digits the number should print : 4
13

 4
 5
 6
 7
 8
 9
 10
 11
 12
 13
 14
 15
 16
 17
 
 */
