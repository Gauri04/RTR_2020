#include<stdio.h>
#define INT_ARRAY_SIZE 10
#define FLOAT_ARRAY_SIZE 5
#define CHAR_ARRAY_SIZE 26

#define NUM_STRINGS 10
#define MAX_CHAR_PER_STRING 20
#define APLHABET_BEGINNING 65

struct MyData1
{
	int iArray[INT_ARRAY_SIZE];
	float fArray[FLOAT_ARRAY_SIZE];
};

struct MyData2
{
	char cArray[CHAR_ARRAY_SIZE];
	char strArray[NUM_STRINGS][MAX_CHAR_PER_STRING];
};

int main()
{
	struct MyData1 md1;
	struct MyData2 md2;
	int i;
	
	// Piece-meal initialization
	md1.fArray[0] = 1.1f;
	md1.fArray[1] = 2.1f;
	md1.fArray[2] = 3.1f;
	md1.fArray[3] = 4.1f;
	md1.fArray[4] = 5.1f;
	
	//Loop initialization
	printf("Enter %d integers : \n", INT_ARRAY_SIZE);
	for(i = 0; i < INT_ARRAY_SIZE; i++)
	{
		scanf("%d", &md1.iArray[i]);
	}
	
	//Hard coded value using loop
	for(i = 0; i < CHAR_ARRAY_SIZE; i++)
	{
		md2.cArray[i] = (char)(APLHABET_BEGINNING + i);
	}
	
	// Hardcoded Piecemeal assignment 
	strcpy(md2.strArray[0], "Welcome");
	strcpy(md2.strArray[1], "Tjis");
	strcpy(md2.strArray[2], "is");
	strcpy(md2.strArray[3], "Astromedicomp's");
	strcpy(md2.strArray[4], "Real");
	strcpy(md2.strArray[5], "Time");
	strcpy(md2.strArray[6], "Rendering");
	strcpy(md2.strArray[7], "Batch");
	strcpy(md2.strArray[8], "Of");
	strcpy(md2.strArray[9], "2020-21");
	
	//Display
	printf("\n Data of struct MyData1 :\n");
	
	for(i = 0; i < INT_ARRAY_SIZE; i++)
	{
		printf("\n MyData 1 iArray[%d] : %d", i, md1.iArray[i]);
	}
	
	for(i = 0; i < FLOAT_ARRAY_SIZE; i++)
	{
		printf("\n MyData 1 fArray[%d] : %f", i, md1.fArray[i]);
	}
	
	printf("\n Data of struct MyData2 :\n");
	
	for(i = 0; i < CHAR_ARRAY_SIZE; i++)
	{
		printf("\n MyData 2 cArray[%d] : %c", i, md2.cArray[i]);
	}
	
	for(i = 0; i < NUM_STRINGS; i++)
	{
		printf("\n MyData 2 strArray[%d] : %s", i, md2.strArray[i]);
	}
	
	return(0);
	
}

/* output *
Enter 10 integers :
1
2
3
4
5
6
7
8
9
10

 Data of struct MyData1 :

 MyData 1 iArray[0] : 1
 MyData 1 iArray[1] : 2
 MyData 1 iArray[2] : 3
 MyData 1 iArray[3] : 4
 MyData 1 iArray[4] : 5
 MyData 1 iArray[5] : 6
 MyData 1 iArray[6] : 7
 MyData 1 iArray[7] : 8
 MyData 1 iArray[8] : 9
 MyData 1 iArray[9] : 10
 MyData 1 fArray[0] : 1.100000
 MyData 1 fArray[1] : 2.100000
 MyData 1 fArray[2] : 3.100000
 MyData 1 fArray[3] : 4.100000
 MyData 1 fArray[4] : 5.100000
 Data of struct MyData2 :

 MyData 2 cArray[0] : A
 MyData 2 cArray[1] : B
 MyData 2 cArray[2] : C
 MyData 2 cArray[3] : D
 MyData 2 cArray[4] : E
 MyData 2 cArray[5] : F
 MyData 2 cArray[6] : G
 MyData 2 cArray[7] : H
 MyData 2 cArray[8] : I
 MyData 2 cArray[9] : J
 MyData 2 cArray[10] : K
 MyData 2 cArray[11] : L
 MyData 2 cArray[12] : M
 MyData 2 cArray[13] : N
 MyData 2 cArray[14] : O
 MyData 2 cArray[15] : P
 MyData 2 cArray[16] : Q
 MyData 2 cArray[17] : R
 MyData 2 cArray[18] : S
 MyData 2 cArray[19] : T
 MyData 2 cArray[20] : U
 MyData 2 cArray[21] : V
 MyData 2 cArray[22] : W
 MyData 2 cArray[23] : X
 MyData 2 cArray[24] : Y
 MyData 2 cArray[25] : Z
 MyData 2 strArray[0] : Welcome
 MyData 2 strArray[1] : Tjis
 MyData 2 strArray[2] : is
 MyData 2 strArray[3] : Astromedicomp's
 MyData 2 strArray[4] : Real
 MyData 2 strArray[5] : Time
 MyData 2 strArray[6] : Rendering
 MyData 2 strArray[7] : Batch
 MyData 2 strArray[8] : Of
 MyData 2 strArray[9] : 2020-21
 
 */

