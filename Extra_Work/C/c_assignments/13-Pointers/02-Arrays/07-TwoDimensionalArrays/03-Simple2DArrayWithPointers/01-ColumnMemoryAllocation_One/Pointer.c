#include<stdio.h>
#include<stdlib.h>

#define NUM_ROWS 5
#define NUM_COLUMNS 3

int main()
{
	int i, j;
	int *griArray[NUM_ROWS];
	
	for(i = 0; i < NUM_ROWS; i++)
	{
		griArray[i] = (int *)malloc(NUM_COLUMNS * sizeof(int));
		if(griArray == NULL)
		{
			printf("\n Error : Fail to allocate memory ");
			exit(0);
		}
		else
		{
			printf("\n Memory allocation successful");
		}	
		
	}
	
	// assign value to 2d array
	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			griArray[i][j] = (i + 1) * (j + 1);
		}
	}
	
	// display
	printf("\n\n 2D array : ");
	for(i = 0; i < NUM_ROWS; i++)
	{
		printf("\n");
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			printf("\n iArray[%d][%d] is : %d ", i, j, griArray[i][j]);
		}
	}
	return(0);
}

/* output *

 Memory allocation successful
 Memory allocation successful
 Memory allocation successful
 Memory allocation successful
 Memory allocation successful

 2D array :

 iArray[0][0] is : 1
 iArray[0][1] is : 2
 iArray[0][2] is : 3

 iArray[1][0] is : 2
 iArray[1][1] is : 4
 iArray[1][2] is : 6

 iArray[2][0] is : 3
 iArray[2][1] is : 6
 iArray[2][2] is : 9

 iArray[3][0] is : 4
 iArray[3][1] is : 8
 iArray[3][2] is : 12

 iArray[4][0] is : 5
 iArray[4][1] is : 10
 iArray[4][2] is : 15
 
 */










