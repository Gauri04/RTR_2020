#include<stdio.h>
#include<stdlib.h>

#define NUM_ROWS 5
#define NUM_COLUMNS 3

int main()
{
	int griArray[NUM_ROWS][NUM_COLUMNS];
	int i,j;
	
	for(i = 0; i < NUM_ROWS; i++)
	{
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			griArray[i][j] = (i + 1) * (j + 1);
		}
		
	}
	
	printf("\n Values of 2D integer array : \n");
	
	for(i = 0; i < NUM_ROWS; i++)
	{
		printf("\n ** Row %d **", i);
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			printf("\n \t iArray[%d][%d] is : %d \t\t at address : %p", i, j, griArray[i][j], &griArray[i][j]);
		}
	}
	printf("\n");
	return(0);
	
}

/* output *

 Values of 2D integer array :

 ** Row 0 **
         iArray[0][0] is : 1             at address : 00D3F708
         iArray[0][1] is : 2             at address : 00D3F70C
         iArray[0][2] is : 3             at address : 00D3F710
 ** Row 1 **
         iArray[1][0] is : 2             at address : 00D3F714
         iArray[1][1] is : 4             at address : 00D3F718
         iArray[1][2] is : 6             at address : 00D3F71C
 ** Row 2 **
         iArray[2][0] is : 3             at address : 00D3F720
         iArray[2][1] is : 6             at address : 00D3F724
         iArray[2][2] is : 9             at address : 00D3F728
 ** Row 3 **
         iArray[3][0] is : 4             at address : 00D3F72C
         iArray[3][1] is : 8             at address : 00D3F730
         iArray[3][2] is : 12            at address : 00D3F734
 ** Row 4 **
         iArray[4][0] is : 5             at address : 00D3F738
         iArray[4][1] is : 10            at address : 00D3F73C
         iArray[4][2] is : 15            at address : 00D3F740

*/


