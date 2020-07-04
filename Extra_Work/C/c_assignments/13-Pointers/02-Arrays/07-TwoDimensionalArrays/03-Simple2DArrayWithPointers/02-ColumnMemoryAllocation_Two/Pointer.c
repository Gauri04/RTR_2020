#include<stdio.h>
#include<stdlib.h>

#define NUM_ROWS 5
#define NUM_COLUMNS_ONE 3
#define NUM_COLUMNS_TWO 8

int main()
{
	int i, j;
	int *griArray[NUM_ROWS];
	
	/************************* for numcolumns 3 **************************/
	for(i = 0; i < NUM_ROWS; i++)
	{
		griArray[i] = (int *)malloc(NUM_COLUMNS_ONE * sizeof(int));
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
	
	// assigning value to 2d array
	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < NUM_COLUMNS_ONE; j++)
		{
			griArray[i][j] = (i + 1) * (j + 1);
		}
	}
	
	// display
	printf("\n\n 2D array : ");
	for(i = 0; i < NUM_ROWS; i++)
	{
		printf("\n");
		for(j = 0; j < NUM_COLUMNS_ONE; j++)
		{
			printf("\n iArray[%d][%d] is : %d ", i, j, griArray[i][j]);
		}
	}
	
	// freeing memory
	for(i = (NUM_ROWS - 1); i >= 0; i--)
	{
		if(griArray)
		{
			free(griArray[i]);
			griArray[i] = NULL;
			printf("\n Memory allocated for 2D array %d row is freed", i);
		}
	}
	
	/************************************* for numcolumn 8 *****************************************/
	printf("\n \n **** Num Column is 8 *****");
	for(i = 0; i < NUM_ROWS; i++)
	{
		griArray[i] = (int *)malloc(NUM_COLUMNS_TWO * sizeof(int));
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
	
	// assigning value to 2d array
	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < NUM_COLUMNS_TWO; j++)
		{
			griArray[i][j] = (i + 1) * (j + 1);
		}
	}
	
	// display
	printf("\n\n 2D array : ");
	for(i = 0; i < NUM_ROWS; i++)
	{
		printf("\n");
		for(j = 0; j < NUM_COLUMNS_TWO; j++)
		{
			printf("\n iArray[%d][%d] is : %d ", i, j, griArray[i][j]);
		}
	}
	
	// freeing memory
	for(i = (NUM_ROWS - 1); i >= 0; i--)
	{
		if(griArray)
		{
			free(griArray[i]);
			griArray[i] = NULL;
			printf("\n Memory allocated for 2D array %d row is freed", i);
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
 Memory allocated for 2D array 4 row is freed
 Memory allocated for 2D array 3 row is freed
 Memory allocated for 2D array 2 row is freed
 Memory allocated for 2D array 1 row is freed
 Memory allocated for 2D array 0 row is freed

 **** Num Column is 8 *****
 Memory allocation to row 0 successful
 Memory allocation to row 1 successful
 Memory allocation to row 2 successful
 Memory allocation to row 3 successful
 Memory allocation to row 4 successful

 2D array :

 iArray[0][0] is : 1
 iArray[0][1] is : 2
 iArray[0][2] is : 3
 iArray[0][3] is : 4
 iArray[0][4] is : 5
 iArray[0][5] is : 6
 iArray[0][6] is : 7
 iArray[0][7] is : 8

 iArray[1][0] is : 2
 iArray[1][1] is : 4
 iArray[1][2] is : 6
 iArray[1][3] is : 8
 iArray[1][4] is : 10
 iArray[1][5] is : 12
 iArray[1][6] is : 14
 iArray[1][7] is : 16

 iArray[2][0] is : 3
 iArray[2][1] is : 6
 iArray[2][2] is : 9
 iArray[2][3] is : 12
 iArray[2][4] is : 15
 iArray[2][5] is : 18
 iArray[2][6] is : 21
 iArray[2][7] is : 24

 iArray[3][0] is : 4
 iArray[3][1] is : 8
 iArray[3][2] is : 12
 iArray[3][3] is : 16
 iArray[3][4] is : 20
 iArray[3][5] is : 24
 iArray[3][6] is : 28
 iArray[3][7] is : 32

 iArray[4][0] is : 5
 iArray[4][1] is : 10
 iArray[4][2] is : 15
 iArray[4][3] is : 20
 iArray[4][4] is : 25
 iArray[4][5] is : 30
 iArray[4][6] is : 35
 iArray[4][7] is : 40
 Memory allocated for 2D array 4 row is freed
 Memory allocated for 2D array 3 row is freed
 Memory allocated for 2D array 2 row is freed
 Memory allocated for 2D array 1 row is freed
 Memory allocated for 2D array 0 row is freed
 
 */

















