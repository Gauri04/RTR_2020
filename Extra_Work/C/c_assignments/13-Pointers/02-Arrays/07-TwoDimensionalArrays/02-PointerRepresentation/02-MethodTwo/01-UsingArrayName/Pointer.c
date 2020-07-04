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
			*(* (griArray + i) + j) = (i + 1) * (j + 1);
		}
	}
	
	printf("\n Elements of 2D integer array : \n");
	
	for(i = 0; i < NUM_ROWS; i++)
	{
		printf("\n ** Row %d **", i);
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			printf("\n *(*(griArray + %d) + %d) : %d \t\t aty address : %p",
				i, j, *(*(griArray + i) + j), (griArray[i] + j), (*(griArray + i) + j));
		}
	}
	printf("\n");
	return(0);
	
}

/* output *

 Elements of 2D integer array :

 ** Row 0 **
 *(*(griArray + 0) + 0) : 1              aty address : 00AFFB5C
 *(*(griArray + 0) + 1) : 2              aty address : 00AFFB60
 *(*(griArray + 0) + 2) : 3              aty address : 00AFFB64
 ** Row 1 **
 *(*(griArray + 1) + 0) : 2              aty address : 00AFFB68
 *(*(griArray + 1) + 1) : 4              aty address : 00AFFB6C
 *(*(griArray + 1) + 2) : 6              aty address : 00AFFB70
 ** Row 2 **
 *(*(griArray + 2) + 0) : 3              aty address : 00AFFB74
 *(*(griArray + 2) + 1) : 6              aty address : 00AFFB78
 *(*(griArray + 2) + 2) : 9              aty address : 00AFFB7C
 ** Row 3 **
 *(*(griArray + 3) + 0) : 4              aty address : 00AFFB80
 *(*(griArray + 3) + 1) : 8              aty address : 00AFFB84
 *(*(griArray + 3) + 2) : 12             aty address : 00AFFB88
 ** Row 4 **
 *(*(griArray + 4) + 0) : 5              aty address : 00AFFB8C
 *(*(griArray + 4) + 1) : 10             aty address : 00AFFB90
 *(*(griArray + 4) + 2) : 15             aty address : 00AFFB94
 
 */
 
 
 
 