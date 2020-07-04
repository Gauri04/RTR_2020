#include<stdio.h>
#include<stdlib.h>

int main()
{
	void MyAlloc(int **ptr, unsigned int numberOfElements);
	
	int *grpiArray = NULL;
	unsigned int grNumberOfElements, i;
	
	printf("\n How many elements you want in array : ");
	scanf("%d", &grNumberOfElements);
	
	MyAlloc(&grpiArray, grNumberOfElements);
	
	printf("\n Enter elements : \n");
	for(i = 0; i < grNumberOfElements; i++)
	{
		scanf("%d", &grpiArray[i]);
	}
	
	printf("\n Entered elements are : ");
	for(i = 0; i < grNumberOfElements; i++)
	{
		printf("\n %d", grpiArray[i]);
	}
	
	if(grpiArray)
	{
		free(grpiArray);
		grpiArray = NULL;
	}
	
	return(0);
}

void MyAlloc(int **ptr, unsigned int numberOfElements)
{
	*ptr = (int *)malloc(numberOfElements * sizeof(int));
	
	if(*ptr == NULL)
	{
		printf("\n Failed to allocate memory to newString");
		exit(0);
	}
	else
	{
		printf("\n Successfully allocated memory");
	}
}

/* output *

 How many elements you want in array : 5

 Successfully allocated memory
 Enter elements :
10
20
30
40
50

 Entered elements are :
 10
 20
 30
 40
 50
 
 */
















