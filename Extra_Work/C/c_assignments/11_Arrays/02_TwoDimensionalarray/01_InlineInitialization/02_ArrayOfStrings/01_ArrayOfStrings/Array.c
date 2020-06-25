#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	int MyStrLen(char[]);
	
	char str[10][15] = {"Hello", "Welcome", "To", "RTR", "Batch", "2020-21"};
	int charSize, strSize;
	int strNumElements, strNumRows, strNumColumns;
	int strActualNumChars = 0;
	int i;
	
	
	charSize = sizeof(char);
	strSize = sizeof(str);
	
	printf("\n Size of 2D char array : %d", strSize);
	
	strNumRows = strSize / sizeof(str[0]);
	printf("\n Number of rows in str : %d", strNumRows);
	
	strNumColumns = sizeof(str[0]) / charSize;
	printf("\n Number of columns in str : %d", strNumColumns);
	
	strNumElements = strNumRows * strNumColumns;
	printf("\n Number of elements in str : %d", strNumElements);
	
	for(i = 0; i < strNumRows; i++)
	{
		strActualNumChars = strActualNumChars + MyStrLen(str[i]);
	}
	printf("\n Actual number of characters in str : %d", strActualNumChars);
	
	printf("\n\n Strings in str:\n");
	
	printf("\n %s", str[0]);
	printf("\n %s", str[1]);
	printf("\n %s", str[2]);
	printf("\n %s", str[3]);
	printf("\n %s", str[4]);
	printf("\n %s", str[5]);
	
	return(0);
	
}


int MyStrLen(char str[])
{
	int j;
	int length = 0;
	
	for(j = 0; j < MAX_STRING_LENGTH; j++)
	{
		if(str[j] == '\0')
			break;
		else
			length++;
	}
	
	return(length);
}

/* output *
 Size of 2D char array : 150
 Number of rows in str : 10
 Number of columns in str : 15
 Number of elements in str : 150
 Actual number of characters in str : 29

 Strings in str:

 Hello
 Welcome
 To
 RTR
 Batch
 2020-21
 
 */
