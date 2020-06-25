#include<stdio.h>

#define WIDTH 5
#define HEIGHT 3
#define DEPTH 2

int main()
{
	int iArray3D[WIDTH][HEIGHT][DEPTH]= { 
									{ {1 ,  2},  {3 ,  4},  {5 ,  6} },
									{ {7 ,  8},  {9 , 10},  {11, 12} },
									{ {13, 14}, {15, 16},  {17, 18} },
									{ {19, 20}, {21, 22},  {23, 24} },
									{ {25, 26}, {27, 28},  {29, 30} }
								};
	int iArray1D[WIDTH * HEIGHT * DEPTH];
								
	
	int i, j, k;
	
	// Piecemeal display
	printf("\n Entered 3D array :");
	
	for(i = 0; i < WIDTH; i++)
	{
		for(j = 0; j < HEIGHT; j++)
		{
			printf("\n \t");
			for(k = 0; k < DEPTH; k++)
			{
				printf("\n iArray[%d][%d][%d] : %d", i,j,k, iArray3D[i][j][k]);
			}
		}
		printf("\n\n");
	}
	
	// Converison
	for(i = 0; i < WIDTH; i++)
	{
		for(j = 0; j < HEIGHT; j++)
		{
			for(k = 0; k < DEPTH; k++)
			{
				iArray1D[(i * HEIGHT * DEPTH) + (j * DEPTH ) + k] = iArray3D[i][j][k];
			}
		}
	}
	
	printf("\n Converted 1D array : \n");
	for(i = 0; i < (WIDTH * HEIGHT * DEPTH); i++)
	{
		printf("\n iArray1D[%d] : %d", i, iArray1D[i]);
	}
	
	return(0);
}

/* output *

 Entered 3D array :

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
 iArray1D[15] : 16
 iArray1D[16] : 17
 iArray1D[17] : 18
 iArray1D[18] : 19
 iArray1D[19] : 20
 iArray1D[20] : 21
 iArray1D[21] : 22
 iArray1D[22] : 23
 iArray1D[23] : 24
 iArray1D[24] : 25
 iArray1D[25] : 26
 iArray1D[26] : 27
 iArray1D[27] : 28
 iArray1D[28] : 29
 iArray1D[29] : 30
 
 */