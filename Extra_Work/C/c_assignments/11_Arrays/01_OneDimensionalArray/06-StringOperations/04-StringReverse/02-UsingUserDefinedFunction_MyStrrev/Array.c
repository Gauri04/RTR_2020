#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	void MyStrRev(char[], char[]);
	char str[MAX_STRING_LENGTH], strReverse[MAX_STRING_LENGTH];
	
	
	printf("\n Enter a string : ");
	gets_s(str, MAX_STRING_LENGTH);
	
	printf("\n str : %s", str);
	MyStrRev(strReverse, str);
	
	printf("\n Reversed string : %s", strReverse);
	
	return(0);
}

void MyStrRev(char dest[], char source[])
{
	int MyStrLen(char[]);
	int len, i,j, iStringLength = 0;
	
	iStringLength = MyStrLen(source);
	len = iStringLength - 1;
	
	for(i = 0, j = len; i < iStringLength, j >= 0; i++, j--)
	{
		dest[i] = source[j];
	}
	dest[i] = '\0';
	
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

 Enter a string : hello welcome

 str : hello welcome
 Reversed string : emoclew olleh
 */




