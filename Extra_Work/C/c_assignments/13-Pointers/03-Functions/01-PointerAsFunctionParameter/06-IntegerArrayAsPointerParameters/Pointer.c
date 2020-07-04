#include<stdio.h>
#include<stdlib.h>

int main()
{
	void MultiplyArrayElementsByNumber(int *, int, int);
	
	int *griArray = NULL;
	int grNumElements, i, grNum;
	
	printf("\n Enter gow many elements to be inserted in array : ");
	scanf("%d", &grNumElements);
	
	griArray = (int *)malloc(grNumElements * sizeof(int));
	
	if(griArray == NULL)
	{
		printf("\n Could not allocate memory");
		exit(0);
	}
	
	printf("\n Enter the elements : \n");
	for(i = 0; i < grNumElements; i++)
	{
		scanf("%d", &griArray[i]);
	}
	
	printf("\n Entered array is : ");
	for(i = 0; i < grNumElements; i++)
	{
		printf("\n iArray[%d] is : %d", i, griArray[i]);
	}
	
	printf("\n Enter the value by which you want to multiply each arra element : ");
	scanf("%d", &grNum);
	
	MultiplyArrayElementsByNumber(griArray, grNumElements, grNum);
	printf("\n Array after calling MultiplyArrayElementsByNumber is : ");
	for(i = 0; i < grNumElements; i++)
	{
		printf("\n iArray[%d] is : %d", i, griArray[i]);
	}
	
	if(griArray)
	{
		free(griArray);
		griArray = NULL;
	}
	return(0);
}

void MultiplyArrayElementsByNumber(int *arr, int numElements, int n)
{
	int i;
	for(i = 0; i < numElements; i++)
	{
		arr[i] = arr[i] * n;
	}
}

/* output *
 Enter gow many elements to be inserted in array : 5

 Enter the elements :
10
20
30
40
50

 Entered array is :
 iArray[0] is : 10
 iArray[1] is : 20
 iArray[2] is : 30
 iArray[3] is : 40
 iArray[4] is : 50
 Enter the value by which you want to multiply each arra element : 5

 Array after calling MultiplyArrayElementsByNumber is :
 iArray[0] is : 50
 iArray[1] is : 100
 iArray[2] is : 150
 iArray[3] is : 200
 iArray[4] is : 250
 
 */








































