#include<stdio.h>

int main()
{
	int iArray3D[5][3][2]= { 
									{ {1 ,  2},  {3 ,  4},  {5 ,  6} },
									{ {7 ,  8},  {9 , 10},  {11, 12} },
									{ {13, 14}, {15, 16},  {17, 18} },
									{ {19, 20}, {21, 22},  {23, 24} },
									{ {25, 26}, {27, 28},  {29, 30} }
								};
								
	int iSize, iArraySize, iArrayNumElements, iArrayWidth, iArrayHeight, iArrayDepth;
	int i, j, k;
	
	iSize = sizeof(int);
	iArraySize = sizeof(iArray3D);
	
	printf("\n Size of iArray3D : %d", iArraySize);
	
	iArrayWidth = iArraySize / sizeof(iArray3D[0]);
	iArrayHeight = sizeof(iArray3D[0]) / sizeof(iArray3D[0][0]);
	iArrayDepth = sizeof(iArray3D[0][0]) / iSize;
	
	iArrayNumElements = iArrayWidth * iArrayHeight * iArrayDepth;
	
	printf("\n Width of array : %d", iArrayWidth);
	printf("\n Height of array : %d", iArrayHeight);
	printf("\n Depth of array : %d", iArrayDepth);
	printf("\n Total number of elements in 3D array iArray3D : %d", iArrayNumElements);
	
	// Piecemeal display
	printf("\n\n Displaying 3D array :\n");
	
	for(i = 0; i < iArrayWidth; i++)
	{
		printf("\n\n");
		for(j = 0; j < iArrayHeight; j++)
		{
			printf("\n \t");
			for(k = 0; k < iArrayDepth; k++)
			{
				printf("\n iArray[%d][%d][%d] : %d", i,j,k, iArray3D[i][j][k]);
			}
		}
	}
	
	return(0);	
	
}

/* ouput *

 Size of iArray3D : 120
 Width of array : 5
 Height of array : 3
 Depth of array : 2
 Total number of elements in 3D array iArray3D : 30

 Displaying 3D array :




 iArray[0][0][0] : 1
 iArray[0][0][1] : 2

 iArray[0][1][0] : 3
 iArray[0][1][1] : 4

 iArray[0][2][0] : 5
 iArray[0][2][1] : 6



 iArray[1][0][0] : 7
 iArray[1][0][1] : 8

 iArray[1][1][0] : 9
 iArray[1][1][1] : 10

 iArray[1][2][0] : 11
 iArray[1][2][1] : 12



 iArray[2][0][0] : 13
 iArray[2][0][1] : 14

 iArray[2][1][0] : 15
 iArray[2][1][1] : 16

 iArray[2][2][0] : 17
 iArray[2][2][1] : 18



 iArray[3][0][0] : 19
 iArray[3][0][1] : 20

 iArray[3][1][0] : 21
 iArray[3][1][1] : 22

 iArray[3][2][0] : 23
 iArray[3][2][1] : 24



 iArray[4][0][0] : 25
 iArray[4][0][1] : 26

 iArray[4][1][0] : 27
 iArray[4][1][1] : 28

 iArray[4][2][0] : 29
 iArray[4][2][1] : 30
 */