#include<stdio.h>
#include<stdlib.h>

#define NUM_ROWS 5
#define NUM_COLUMNS 3

int main()
{
	int *griArray[NUM_ROWS]; 
	int i, j;
	
	// memory allocation to 2d array
	for(i = 0; i < NUM_ROWS; i++)
	{
		// Memory will be allocated such that
		// Row 0 will have num - 0 columns i.e 5 - 0 = 5
		// Row 1 will have num - 1 columns i.e 5 - 1 = 4
		// so on and Row 4 will ahve num - 4 columns i.e 5 - 4 = 1
		
		griArray[i] = (int *)malloc((NUM_COLUMNS - i) * sizeof(int));
		if(griArray == NULL)
		{
			printf("\n Error : Fail to allocate memory to row %d", i);
			exit(0);
		}
		else
		{
			printf("\n Memory allocation to row %d successful", i);
		}	
		
	}
	
	// assignment
	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < (NUM_COLUMNS - i); j++)
		{
			griArray[i][j] = (i * 1) + (j * 1);
		}
	}
	
	// display
	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < (NUM_COLUMNS - i); j++)
		{
			printf("\n iArray[%d][%d] is : %d \t at address %p", i, j, griArray[i][j], &griArray[i][j]);
		}
	}
	
	return(0);
}

/* output *

 Memory allocation to row 0 successful
 Memory allocation to row 1 successful
 Memory allocation to row 2 successful
 Memory allocation to row 3 successful
 Memory allocation to row 4 successful
 iArray[0][0] is : 0     at address 013C25E0
 iArray[0][1] is : 1     at address 013C25E4
 iArray[0][2] is : 2     at address 013C25E8
 iArray[1][0] is : 1     at address 013C4FD8
 iArray[1][1] is : 2     at address 013C4FDC
 iArray[2][0] is : 2     at address 013C3600
 
 */





