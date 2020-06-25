#include<stdio.h>

int main()
{
	int iArray1[5];
	int iArray2[5][3];
	int iArray3[100][100][3];
	
	int numRows2D, numColumns2D;
	int numRows3D, numColumns3D;
	int depth3D;
	
	printf("\n Size of 1D integer array iArray1 : %lu", sizeof(iArray1));
	printf("\n Number of integers in iArray1 : %lu", (sizeof(iArray1) / sizeof(int)));
	
	printf("\n Size of 2D integer array iArray2 : %lu", sizeof(iArray2));
	printf("\n Number of rows in iArray1 : %lu", (sizeof(iArray2) / sizeof(iArray2[0])));
	
	numRows2D = sizeof(iArray2) / sizeof(iArray2[0]);
	
	printf("\n Number of elements (columns) in each row in 2D integer array iArray2 : %lu", 
	(sizeof(iArray2[0]) / sizeof(iArray2[0][0])));
	
	numColumns2D = sizeof(iArray2[0]) / sizeof(iArray2[0][0]);
	
	printf("\n Number of total elements in 2D integer array iArray2 : %d", (numRows2D * numColumns2D));
	
	// 3D array
	printf("\n Size of 3D integer array iArray3 : %lu", sizeof(iArray3));
	printf("\n Number of rows in iArray3 : %lu", (sizeof(iArray3) / sizeof(iArray3[0])));
	
	numRows3D = sizeof(iArray3) / sizeof(iArray3[0]);
	
	printf("\n No. of elements in one row in 3D array iArray3 : %lu", (sizeof(iArray3[0]) / sizeof(iArray3[0][0])) );
	
	numColumns3D = sizeof(iArray3[0]) / sizeof(iArray3[0][0]);
	
	printf("\n No. of elements in one column in 3D integer array iArray3 : %lu", 
		(sizeof(iArray3[0][0]) / sizeof(iArray3[0][0][0])) ); 
	
	depth3D = sizeof(iArray3[0][0]) / sizeof(iArray3[0][0][0]);
	
	printf("\n Number of elements in total in iarray3 : %d", (numRows3D * numColumns3D * depth3D));
	
	return(0);
	
	
}

/* output *

 Size of 1D integer array iArray1 : 20
 Number of integers in iArray1 : 5
 Size of 2D integer array iArray2 : 60
 Number of rows in iArray1 : 5
 Number of elements (columns) in each row in 2D integer array iArray2 : 3
 Number of total elements in 2D integer array iArray2 : 15
 Size of 3D integer array iArray3 : 120000
 Number of rows in iArray3 : 100
 No. of elements in one row in 3D array iArray3 : 100
 No. of elements in one column in 3D integer array iArray3 : 3
 Number of elements in total in iarray3 : 30000
 
 */

