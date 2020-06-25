#include<stdio.h>

int main()
{
	int iSize, iArraySize, iArrayNumElements, iArrayNumRows, iArrayNumColumns;
	int i, j;
	int iArray[3][5];
	
	iSize = sizeof(int);
	iArraySize = sizeof(iArray);
	
	printf("\n Size of 2D array : %d",iArraySize);
	
	iArrayNumRows = iArraySize / sizeof(iArray[0]);
	printf("\n No. of rows in 2D array : %d", iArrayNumRows);
	
	iArrayNumColumns = sizeof(iArray[0]) / iSize;
	printf("\n No. of columns in 2D array : %d", iArrayNumColumns);
	
	iArrayNumElements = iArrayNumRows * iArrayNumColumns;
	printf("\n No. of elements in 2D array : %d\n\n", iArrayNumElements);
	
	//Piecemeal initialization
	iArray[0][0] = 1;
	iArray[0][1] = 2;
	iArray[0][2] = 3;
	iArray[0][3] = 4;
	iArray[0][4] = 5;
	
	iArray[1][0] = 6;
	iArray[1][1] = 7;
	iArray[1][2] = 8;
	iArray[1][3] = 9;
	iArray[1][4] = 10;
	
	iArray[2][0] = 11;
	iArray[2][1] = 12;
	iArray[2][2] = 13;
	iArray[2][3] = 14;
	iArray[2][4] = 15;
	
	for(i = 0; i < iArrayNumRows; i++)
	{
		for(j = 0; j < iArrayNumColumns; j++)
		{
			printf("\n iArray[%d][%d] : %d", i,j, iArray[i][j]);
		}
		printf("\n\n");
	}
	return(0);
}


/* output *

 Size of 2D array : 60
 No. of rows in 2D array : 3
 No. of columns in 2D array : 5
 No. of elements in 2D array : 15


 iArray[0][0] : 1
 iArray[0][1] : 2
 iArray[0][2] : 3
 iArray[0][3] : 4
 iArray[0][4] : 5


 iArray[1][0] : 6
 iArray[1][1] : 7
 iArray[1][2] : 8
 iArray[1][3] : 9
 iArray[1][4] : 10


 iArray[2][0] : 11
 iArray[2][1] : 12
 iArray[2][2] : 13
 iArray[2][3] : 14
 iArray[2][4] : 15

*/




