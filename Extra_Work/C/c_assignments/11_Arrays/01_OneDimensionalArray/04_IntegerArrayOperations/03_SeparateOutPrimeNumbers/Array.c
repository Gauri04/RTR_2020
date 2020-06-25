#include<stdio.h>
#define NUM_ELEMENTS 10

int main()
{
	int a[NUM_ELEMENTS];
	int num;
	int i, j, count = 0;
	
	printf("\n Enter integer elements in array : \n");
	for(i = 0; i < NUM_ELEMENTS; i++)
	{
		scanf("%d",&num);
		if(num < 0)													// If num is -ve then convert it to +ve
			num = -1 * num;
			
		a[i] = num;
	}
	
	printf("Prime number in the array : \n");
	
	for(i = 0; i < NUM_ELEMENTS; i++)
	{
		for(j = 1; j <= a[i]; j++)
		{
			if((a[i] % j) == 0)
				count++;
		}
		
		if(count == 2)
			printf("\n %d",a[i]);
		
		count = 0;
	}
	
	return(0);
	
}

/* output *
 Enter integer elements in array :
1
2
3
4
5
6
7
8
9
10
Prime number in the array :

 2
 3
 5
 7
 */
 

