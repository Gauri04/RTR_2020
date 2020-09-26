#include<stdio.h>

int main()
{
	int *array = NULL;
	int numberOfElements;
	int i, j, temp;
	
	
	printf("\n Enter the number of elements you want to insert in an array : ");
	scanf("%d", &numberOfElements);
	
	array = (int *)malloc(numberOfElements * sizeof(int));
	if(array == NULL)
	{
		printf("\n Error : Unalbe to allocate memory to array. Exiting now..");
		exit(0);
	}
	
	printf("\n\n Enter the elements : ");
	
	for(i = 0; i < numberOfElements; i++)
		scanf("%d", &array[i]);
	
	printf("\n\n Entered elements are : ");
	for(i = 0; i < numberOfElements; i++)
		printf("\n%d", array[i]);
	
	for(i = 1; i < numberOfElements; i++)
	{
		temp = array[i];
		j = i - 1;
		
		for(j = i-1; j >= 0 && temp < array[j]; j--)
		{
			array[j + 1] = array[j];
		}
		
		array[j + 1] = temp;
	}
	
	printf("\n\n The sorted elements are : ");
	for(i = 0; i < numberOfElements; i++)
		printf("\n%d", array[i]);
	
	return(0);
	
}

/* output *

 Enter the number of elements you want to insert in an array : 5


 Enter the elements :
20
10
0
90
0


 Entered elements are :
20
10
0
90
0

 The sorted elements are :
0
0
10
20
90

*/



