#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	void MyStrCpy(char[], char[]);
	char str[MAX_STRING_LENGTH], strCopy[MAX_STRING_LENGTH];
	
	
	printf("\n Enter a string : ");
	gets_s(str, MAX_STRING_LENGTH);
	
	printf("\n str : %s", str);
	MyStrCpy(strCopy, str);
	
	printf("\n Copied string : %s", strCopy);
	
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

 Enter a string : hello there

 str : hello there
 Copied string : hello there
 
 */
 
 