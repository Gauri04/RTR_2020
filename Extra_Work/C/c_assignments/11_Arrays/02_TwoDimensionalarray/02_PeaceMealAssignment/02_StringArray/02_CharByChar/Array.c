#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	char str[5][10];
	
	int charSize, strSize;
	int strNumElements, strNumRows, strNumColumns;
	int i;
	
	charSize = sizeof(char);
	strSize = sizeof(str);
	
	printf("\n Size of 2D char array : %d", strSize);
	
	strNumRows = strSize / sizeof(str[0]);
	printf("\n Number of rows in str : %d", strNumRows);
	
	strNumColumns = sizeof(str[0]) / charSize;
	printf("\n Number of columns in str : %d", strNumColumns);
	
	strNumElements = strNumRows * strNumColumns;
	printf("\n Max Number of elements in str : %d", strNumElements);
	
	str[0][0] = 'M';
	str[0][1] = 'y';
	str[0][2] = '\0';
	
	str[1][0] = 'N';
	str[1][1] = 'A';
	str[1][2] = 'M';
	str[1][3] = 'E';
	str[1][4] = '\0';
	
	str[2][0] = 'I';
	str[2][1] = 's';
	str[2][2] = '\0';
	
	str[3][0] = 'G';
	str[3][1] = 'a';
	str[3][2] = 'u';
	str[3][3] = 'r';
	str[3][4] = 'i';
	str[3][5] = '\0';
	
	str[4][0] = 'R';
	str[4][1] = 'a';
	str[4][2] = 'n';
	str[4][3] = 'a';
	str[4][4] = 'd';
	str[4][5] = 'e';
	str[4][6] = '\0';
	
	printf("\n The strings in 2D char array are :\n");
	for(i = 0; i < strNumRows; i++)
	{
		printf("\n %s",str[i]);
	}
	return(0);	
	
}

/* output *

 Size of 2D char array : 50
 Number of rows in str : 5
 Number of columns in str : 10
 Max Number of elements in str : 50
 The strings in 2D char array are :

 My
 NAME
 Is
 Gauri
 Ranade
 */
