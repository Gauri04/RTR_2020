#include<stdio.h>

int main()
{
	int iNum, num, i;
	
	printf("\n Enter an iteration from which iteration should begin : ");
	scanf("%d", &iNum);
	printf("\n To how many digits do you want to print from this number : ");
	scanf("%d", &num);
	
	printf("\n Printing from %d to %d ", iNum, (iNum + num));
	
	for(i = iNum; i <= (iNum + num); i++)
	{
		printf("\n %d", i);
	}
	return(0);
	
	
}

/* output *
 Enter an iteration from which iteration should begin : -2

 To how many digits do you want to print from this number : 8

 Printing from -2 to 6
 -2
 -1
 0
 1
 2
 3
 4
 5
 6
 */


