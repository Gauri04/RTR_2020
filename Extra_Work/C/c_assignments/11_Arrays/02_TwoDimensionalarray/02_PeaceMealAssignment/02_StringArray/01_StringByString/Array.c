#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	void MyStrCpy(char[], char[]);
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
	
	MyStrCpy(str[0], "My");
	MyStrCpy(str[1], "Name");
	MyStrCpy(str[2], "Is");
	MyStrCpy(str[3], "Gauri");
	MyStrCpy(str[4], "Ranade");
	
	printf("\n The strings id 2D char array are :\n");
	for(i = 0; i < strNumRows; i++)
	{
		printf("\n %s",str[i]);
	}
	return(0);
	
}


void MyStrCpy(char dest[], char source[])
{
	int MyStrLen(char[]);
	int iStringLength = 0;
	int j;
	
	
	iStringLength = MyStrLen(source);
	for(j = 0; j < iStringLength; j++)
	{
		dest[j] = source[j];
	}
	dest[j] = '\0';
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
 Size of 2D char array : 50
 Number of rows in str : 5
 Number of columns in str : 10
 Max Number of elements in str : 50
 The strings id 2D char array are :

 My
 Name
 Is
 Gauri
 Ranade
 
 */










