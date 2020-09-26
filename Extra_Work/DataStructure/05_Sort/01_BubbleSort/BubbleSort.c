#include<stdio.h>

int main(void)
{
	int numberOfElements;
	int *array = NULL;
	int i, j, temp = 0;
	
	printf("\n Enter the number of elements you want to insert in an array : ");
	scanf("%d", &numberOfElements);
	
	array = (int *)malloc(numberOfElements * sizeof(int));
	
	printf("\n Enter the elements : \n");
	for(i = 0; i < numberOfElements; i++)
	{
		scanf("%d", &array[i]);
	}
	printf("\n\n The entered elements are : \n");
	for(i = 0; i < numberOfElements; i++)
	{
		printf("\n %d", array[i]);
	}
	
	//sorting
	for(i = 0; i < numberOfElements - 1; i++)
	{
		for(j = 0; j < numberOfElements - i - 1; j++)
		{
			if(array[j] > array[j+1])
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			
		}
	}
	
	printf("\n\n The sorted elements are : \n");
	for(i = 0; i < numberOfElements; i++)
	{
		printf("\n %d", array[i]);
	}
	return(0);
}

/* output *
 Enter the number of elements you want to insert in an array : 5

 Enter the elements :
30
20
0
90
10


 The entered elements are :

 30
 20
 0
 90
 10

 The sorted elements are :

 0
 10
 20
 30
 90
 */