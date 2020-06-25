#include<stdio.h>

#define INT_ARRAY_NUM_ELEMENTS 5
#define FLOAT_ARRAY_NUM_ELEMENTS 3
#define CHAR_ARRAY_NUM_ELEMENTS 7

int main()
{
	int iArray[INT_ARRAY_NUM_ELEMENTS];
	float fArray[FLOAT_ARRAY_NUM_ELEMENTS];
	char chArray[CHAR_ARRAY_NUM_ELEMENTS];
	int i;

	
	printf("\n Enter elements for integer array : ");
	for(i = 0; i < INT_ARRAY_NUM_ELEMENTS; i++)
	{
		scanf("%d", &iArray[i]);
	}
	
	printf("\n Enter elements for float array : ");
	for(i = 0; i < FLOAT_ARRAY_NUM_ELEMENTS; i++)
	{
		scanf("%f", &fArray[i]);
	}
	
	printf("\n Enter elements for char array : ");
	for(i = 0; i < CHAR_ARRAY_NUM_ELEMENTS; i++)
	{
		chArray[i] = getch();
		printf("\n%c", chArray[i]);
	}
	
	//display
	printf("\n\n");
	for(i = 0; i < INT_ARRAY_NUM_ELEMENTS; i++)
	{
		printf("\n iArray [%d] : %d", i, iArray[i]);
	}
	
	printf("\n\n");
	for(i = 0; i < FLOAT_ARRAY_NUM_ELEMENTS; i++)
	{
		printf("\n fArray [%d] : %f", i, fArray[i]);
	}
	
	printf("\n\n");
	for(i = 0; i < CHAR_ARRAY_NUM_ELEMENTS; i++)
	{
		printf("\n chArray [%d] : %c", i, chArray[i]);
	}
	return(0);
	
}

/* output *
 Enter elements for integer array : 1
2
3
4
5

 Enter elements for float array : 1
2
3

 Enter elements for char array :
a

b

c

d


 iArray [0] : 1
 iArray [1] : 2
 iArray [2] : 3
 iArray [3] : 4
 iArray [4] : 5


 fArray [0] : 1.000000
 fArray [1] : 2.000000
 fArray [2] : 3.000000


 chArray [0] : a
 chArray [1] :
 chArray [2] : b
 chArray [3] :
 chArray [4] : c
 chArray [5] :
 chArray [6] : d
 
 */


