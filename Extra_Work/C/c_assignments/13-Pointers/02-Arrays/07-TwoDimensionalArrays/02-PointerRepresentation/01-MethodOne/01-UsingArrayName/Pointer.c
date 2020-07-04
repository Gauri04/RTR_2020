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
			*(griArray[i] + j) = (i + 1) * (j + 1);
		}
		
	}
	
	printf("\n Elements of 2D integer array : \n");
	
	for(i = 0; i < NUM_ROWS; i++)
	{
		printf("\n ** Row %d **", i);
		for(j = 0; j < NUM_COLUMNS; j++)
		{
			printf("\n \t iArray[%d][%d] is : %d \t\t at address : %p", i, j, *(griArray[i] + j), (griArray[i] + j));
		}
	}
	printf("\n");
	return(0);
	
}

/* output *

 Elements of 2D integer array :

 ** Row 0 **
         iArray[0][0] is : 1             at address : 008FFE2C
         iArray[0][1] is : 2             at address : 008FFE30
         iArray[0][2] is : 3             at address : 008FFE34
 ** Row 1 **
         iArray[1][0] is : 2             at address : 008FFE38
         iArray[1][1] is : 4             at address : 008FFE3C
         iArray[1][2] is : 6             at address : 008FFE40
 ** Row 2 **
         iArray[2][0] is : 3             at address : 008FFE44
         iArray[2][1] is : 6             at address : 008FFE48
         iArray[2][2] is : 9             at address : 008FFE4C
 ** Row 3 **
         iArray[3][0] is : 4             at address : 008FFE50
         iArray[3][1] is : 8             at address : 008FFE54
         iArray[3][2] is : 12            at address : 008FFE58
 ** Row 4 **
         iArray[4][0] is : 5             at address : 008FFE5C
         iArray[4][1] is : 10            at address : 008FFE60
         iArray[4][2] is : 15            at address : 008FFE64

*/








