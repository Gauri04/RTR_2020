#include<stdio.h>

#define NUM_ROWS 5
#define NUM_COLUMNS 3

int main()
{
	int iArray2D[NUM_ROWS][NUM_COLUMNS];
	int iArray1D[NUM_ROWS * NUM_COLUMNS];
	int i,j,num;
	
	printf("\n Enter elements in 2D array : \n");
	for(i = 0; i < NUM_ROWS; i++)
	{
		printf("\n Row\n");
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			printf("\n \t ");
			scanf("%d", &iArray2D[i][j]);
		}
	}
	
	printf("2D array :\n");
	for(i = 0; i < NUM_ROWS; i++)
	{
		printf("\n Row\n");
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			printf("\n \t %d", iArray2D[i][j]);
		}
	}
	
	// *** Conversion ****
	for(i = 0; i < NUM_ROWS; i++)
	{
		
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			iArray1D[(i * NUM_COLUMNS) + j] = iArray2D[i][j];
		}
	}
	
	printf("\n Converted 1D array : \n");
	
	for(i = 0; i < (NUM_ROWS * NUM_COLUMNS); i++)
	{
		printf("\n iArray1D[%d] : %d", i, iArray1D[i]);
	}
	return(0);
	
}

/* ouput *

 Enter elements in 2D array :

 Row

         1

         2

         3

 Row

         4

         5

         6

 Row

         7

         8

         9

 Row

         10

         11

         12

 Row

         13

         14

         15
2D array :

 Row

         1
         2
         3
 Row

         4
         5
         6
 Row

         7
         8
         9
 Row

         10
         11
         12
 Row

         13
         14
         15
 Converted 1D array :

 iArray1D[0] : 1
 iArray1D[1] : 2
 iArray1D[2] : 3
 iArray1D[3] : 4
 iArray1D[4] : 5
 iArray1D[5] : 6
 iArray1D[6] : 7
 iArray1D[7] : 8
 iArray1D[8] : 9
 iArray1D[9] : 10
 iArray1D[10] : 11
 iArray1D[11] : 12
 iArray1D[12] : 13
 iArray1D[13] : 14
 iArray1D[14] : 15
 
 */

