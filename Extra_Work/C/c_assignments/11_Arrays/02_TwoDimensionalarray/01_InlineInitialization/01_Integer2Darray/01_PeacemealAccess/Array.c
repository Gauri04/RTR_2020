#include<stdio.h>

int main()
{
	int iArray[5][3] = {{1,2,3}, {4,5,6}, {7,8,9}, {10,11,12}, {13,14,15}};
	int iSize, iArraySize, iArrayNumElements, iArrayNumRows, iArrayNumColumns;
	
	iSize = sizeof(int);
	iArraySize = sizeof(iArray);
	
	printf("\n Size of 2D array : %d",iArraySize);
	
	iArrayNumRows = iArraySize / sizeof(iArray[0]);
	printf("\n No. of rows in 2D array : %d", iArrayNumRows);
	
	iArrayNumColumns = sizeof(iArray[0]) / iSize;
	printf("\n No. of columns in 2D array : %d", iArrayNumColumns);
	
	iArrayNumElements = iArrayNumRows * iArrayNumColumns;
	printf("\n No. of elements in 2D array : %d\n\n", iArrayNumElements);
	
	
	printf("\n iArray[0][0] : %d", iArray[0][0]);
	printf("\n iArray[0][1] : %d", iArray[0][1]);
	printf("\n iArray[0][2] : %d", iArray[0][2]);
	
	printf("\n iArray[1][0] : %d", iArray[1][0]);
	printf("\n iArray[1][1] : %d", iArray[1][1]);
	printf("\n iArray[1][2] : %d", iArray[1][2]);
	
	printf("\n iArray[2][0] : %d", iArray[2][0]);
	printf("\n iArray[2][0] : %d", iArray[2][1]);
	printf("\n iArray[2][0] : %d", iArray[2][2]);
	
	printf("\n iArray[3][0] : %d", iArray[3][0]);
	printf("\n iArray[3][1] : %d", iArray[3][1]);
	printf("\n iArray[3][2] : %d", iArray[3][2]);
	
	printf("\n iArray[4][0] : %d", iArray[4][0]);
	printf("\n iArray[4][1] : %d", iArray[4][1]);
	printf("\n iArray[4][2] : %d", iArray[4][2]);
	
	return(0);
	
}

/* output *

 Size of 2D array : 60
 No. of rows in 2D array : 5
 No. of columns in 2D array : 3
 No. of elements in 2D array : 15


 iArray[0][0] : 1
 iArray[0][1] : 2
 iArray[0][2] : 3
 iArray[1][0] : 4
 iArray[1][1] : 5
 iArray[1][2] : 6
 iArray[2][0] : 7
 iArray[2][0] : 8
 iArray[2][0] : 9
 iArray[3][0] : 10
 iArray[3][1] : 11
 iArray[3][2] : 12
 iArray[4][0] : 13
 iArray[4][1] : 14
 iArray[4][2] : 15
 
 */



