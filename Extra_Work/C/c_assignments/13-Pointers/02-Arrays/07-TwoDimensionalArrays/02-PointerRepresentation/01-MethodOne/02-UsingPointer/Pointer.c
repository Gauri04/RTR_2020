#include<stdio.h>
#include<stdlib.h>

#define NUM_ROWS 5
#define NUM_COLUMNS 3

int main()
{
	int griArray[NUM_ROWS][NUM_COLUMNS];
	int *griPtrArrayRow = NULL;
	int i,j;
	
	for(i = 0; i < NUM_ROWS; i++)
	{
		griPtrArrayRow = griArray[i];
		
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			*(griPtrArrayRow + j) = (i + 1) * (j + 1);
		}
	}
	
	printf("\n 2D array elements with its associated addresses : ");
	for(i = 0; i < NUM_ROWS; i++)
	{
		printf("\n *** Row %d ***", i);
		griPtrArrayRow = griArray[i];
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			printf("\n *(ptrArrayRow + %d) is : %d \t \t at address &(ptrArrayRow + j): %p", 
				j, *(griPtrArrayRow + j), (griPtrArrayRow + j));
		}
	}
	
	return(0);
}

/* output *

 2D array elements with its associated addresses :
 *** Row 0 ***
 *(ptrArrayRow + 0) is : 1               at address &(ptrArrayRow + j): 00EFF710
 *(ptrArrayRow + 1) is : 2               at address &(ptrArrayRow + j): 00EFF714
 *(ptrArrayRow + 2) is : 3               at address &(ptrArrayRow + j): 00EFF718
 *** Row 1 ***
 *(ptrArrayRow + 0) is : 2               at address &(ptrArrayRow + j): 00EFF71C
 *(ptrArrayRow + 1) is : 4               at address &(ptrArrayRow + j): 00EFF720
 *(ptrArrayRow + 2) is : 6               at address &(ptrArrayRow + j): 00EFF724
 *** Row 2 ***
 *(ptrArrayRow + 0) is : 3               at address &(ptrArrayRow + j): 00EFF728
 *(ptrArrayRow + 1) is : 6               at address &(ptrArrayRow + j): 00EFF72C
 *(ptrArrayRow + 2) is : 9               at address &(ptrArrayRow + j): 00EFF730
 *** Row 3 ***
 *(ptrArrayRow + 0) is : 4               at address &(ptrArrayRow + j): 00EFF734
 *(ptrArrayRow + 1) is : 8               at address &(ptrArrayRow + j): 00EFF738
 *(ptrArrayRow + 2) is : 12              at address &(ptrArrayRow + j): 00EFF73C
 *** Row 4 ***
 *(ptrArrayRow + 0) is : 5               at address &(ptrArrayRow + j): 00EFF740
 *(ptrArrayRow + 1) is : 10              at address &(ptrArrayRow + j): 00EFF744
 *(ptrArrayRow + 2) is : 15              at address &(ptrArrayRow + j): 00EFF748
 
 */



