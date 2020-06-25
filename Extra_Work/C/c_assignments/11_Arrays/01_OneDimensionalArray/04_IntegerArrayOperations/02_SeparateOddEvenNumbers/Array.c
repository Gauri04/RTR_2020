#include<stdio.h>
#define NUM_ELEMENTS 10

int main()
{
	int a[NUM_ELEMENTS];
	int num;
	int i;
	
	printf("\n Enter integer elements in array : \n");
	for(i = 0; i < NUM_ELEMENTS; i++)
	{
		scanf("%d",&num);
		a[i] = num;
	}
	
	printf("\n Even elements in array : \n");
	for(i = 0; i < NUM_ELEMENTS; i++)
	{
		if(a[i] % 2 == 0)
			printf("\n \t %d", a[i]);
	}
	
	printf("\n Odd elements in array : \n");
	for(i = 0; i < NUM_ELEMENTS; i++)
	{
		if(a[i] % 2 != 0)
			printf("\n \t %d", a[i]);
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

 Even elements in array :

         2
         4
         6
         8
         10
 Odd elements in array :

         1
         3
         5
         7
         9
*/


