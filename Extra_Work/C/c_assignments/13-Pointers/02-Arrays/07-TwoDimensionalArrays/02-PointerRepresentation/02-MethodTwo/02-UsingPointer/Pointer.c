#include<stdio.h>
#include<stdlib.h>

#define NUM_ROWS 5
#define NUM_COLUMNS 3

int main()
{
	int i, j;
	int **griPtr = NULL;
	
	griPtr = (int **)malloc(sizeof(int *) * NUM_ROWS);
	
	if(griPtr == NULL)
	{
		printf("\n Error : Fail to allocate memory ");
		exit(0);
	}
	else
	{
		printf("\n MEmory allocation successful");
	}
	
	for(i = 0; i < NUM_ROWS; i++)
	{
		griPtr[i] = (int *)malloc(NUM_COLUMNS * sizeof(int));
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			*(*(griPtr + i) + j) = (i + 1) * (j + 1);
		}
	}
	
	printf("\n\n Entered array :");
	for(i = 0; i < NUM_ROWS; i++)
	{
		printf("\n Row %d", i);
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			printf("\n \t ptrRow[%d][%d] : %d, at address : %p", i, j, griPtr[i][j], &griPtr[i][j]);
		}
	}
	
	// free memory of each row
	for(i = (NUM_ROWS - 1); i >= 0; i--)
	{
		if(*(griPtr + 1))
		{
			free(*(griPtr + i));
			*(griPtr + i) = NULL;
		}
	}

	// Free
	if(griPtr)
	{
		free(griPtr);
		griPtr = NULL;
		printf("\n Memory freed successfully");
	}
	
	
	return(0);
}

/* output *
 MEmory allocation successful

 Entered array :
 Row 0
         ptrRow[0][0] : 1, at address : 00B03580
         ptrRow[0][1] : 2, at address : 00B03584
         ptrRow[0][2] : 3, at address : 00B03588
 Row 1
         ptrRow[1][0] : 2, at address : 00B03598
         ptrRow[1][1] : 4, at address : 00B0359C
         ptrRow[1][2] : 6, at address : 00B035A0
 Row 2
         ptrRow[2][0] : 3, at address : 00B035B0
         ptrRow[2][1] : 6, at address : 00B035B4
         ptrRow[2][2] : 9, at address : 00B035B8
 Row 3
         ptrRow[3][0] : 4, at address : 00B035C8
         ptrRow[3][1] : 8, at address : 00B035CC
         ptrRow[3][2] : 12, at address : 00B035D0
 Row 4
         ptrRow[4][0] : 5, at address : 00B035E0
         ptrRow[4][1] : 10, at address : 00B035E4
         ptrRow[4][2] : 15, at address : 00B035E8
		 
*/

















