#include<stdio.h>
#include<stdlib.h>

int main()
{
	int **griPtrArray = NULL;
	int i, j, grNumRows, grNumColumns;
	
	printf("\n Enter number of rows : \n");
	scanf("%d", &grNumRows);
	
	printf("\n Enter number of columns : \n");
	scanf("%d", &grNumColumns);
	
	// memory allocation
	griPtrArray = (int **) malloc(grNumRows * sizeof(int *));
	if(griPtrArray == NULL)
	{
		printf("\n Error : Fail to allocate memory");
		exit(0);
	}
	else
	{
		printf("\n Memory allocation to successful");
	}	
	
	for(i = 0; i < grNumRows; i++)
	{
		griPtrArray[i] = (int *)malloc(grNumColumns * sizeof(int));
		if(griPtrArray == NULL)
		{
			printf("\n Error : Fail to allocate memory");
			exit(0);
		}
		else
		{
			printf("\n Memory allocation to successful");
		}	
		
	}
	
	// assignment
	for(i = 0; i < grNumRows; i++)
	{
		for(j = 0; j < grNumColumns; j++)
		{
			griPtrArray[i][j] = (i * 1) + (j * 1);
		}
	}
	
	// display
	printf("\n\n");
	for(i = 0; i < grNumRows; i++)
	{
		printf("\n Base address of row : %d : ptrArray[%d] is : %p \t\t at address %p", 
			i, i, griPtrArray[i] , &griPtrArray[i]);
	}
	
	for(i = 0; i < grNumRows; i++)
	{
		for(j = 0; j < grNumColumns; j++)
		{
			printf("\n ptrArray[%d][%d] is : %d at address %p", i, j, griPtrArray[i][j], &griPtrArray[i][j]);
		}
	}
	
	// freeing memory
	for(i = (grNumRows - 1); i >= 0; i--)
	{
		if(griPtrArray[i])
		{
			free(griPtrArray[i]);
			griPtrArray[i] = NULL;
			printf("\n Memory allocated for 2D array %d row is freed", i);
		}
		
	}
	
	if(griPtrArray)
	{
		free(griPtrArray);
		griPtrArray = NULL;
		printf("\n Memory allocated for 2D array is now freed");
	}
	
	
	return(0);
	
}

/* output *

 Enter number of rows :
5

 Enter number of columns :
3

 Memory allocation to successful
 Memory allocation to successful
 Memory allocation to successful
 Memory allocation to successful
 Memory allocation to successful
 Memory allocation to successful


 Base address of row : 0 : ptrArray[0] is : 01423458             at address 01423438
 Base address of row : 1 : ptrArray[1] is : 01423470             at address 0142343C
 Base address of row : 2 : ptrArray[2] is : 01423488             at address 01423440
 Base address of row : 3 : ptrArray[3] is : 014234A0             at address 01423444
 Base address of row : 4 : ptrArray[4] is : 014234B8             at address 01423448
 ptrArray[0][0] is : 0 at address 01423458
 ptrArray[0][1] is : 1 at address 0142345C
 ptrArray[0][2] is : 2 at address 01423460
 ptrArray[1][0] is : 1 at address 01423470
 ptrArray[1][1] is : 2 at address 01423474
 ptrArray[1][2] is : 3 at address 01423478
 ptrArray[2][0] is : 2 at address 01423488
 ptrArray[2][1] is : 3 at address 0142348C
 ptrArray[2][2] is : 4 at address 01423490
 ptrArray[3][0] is : 3 at address 014234A0
 ptrArray[3][1] is : 4 at address 014234A4
 ptrArray[3][2] is : 5 at address 014234A8
 ptrArray[4][0] is : 4 at address 014234B8
 ptrArray[4][1] is : 5 at address 014234BC
 ptrArray[4][2] is : 6 at address 014234C0
 Memory allocated for 2D array 4 row is freed
 Memory allocated for 2D array 3 row is freed
 Memory allocated for 2D array 2 row is freed
 Memory allocated for 2D array 1 row is freed
 Memory allocated for 2D array 0 row is freed
 Memory allocated for 2D array is now freed
 
 */
 
 













