#include<stdio.h>
#define NUM_ELEMENTS 10
int main()
{
	int a[NUM_ELEMENTS];
	int num, sum = 0;
	int i;
	
	printf("\n Enter integer elements in array : \n");
	for(i = 0; i < NUM_ELEMENTS; i++)
	{
		scanf("%d",&num);
		a[i] = num;
	}
	
	for(i = 0; i < NUM_ELEMENTS; i++)
	{
		sum = sum + a[i];
	}
	printf("\n Sum of elements of array : %d", sum);
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

 Sum of elements of array : 55
 */