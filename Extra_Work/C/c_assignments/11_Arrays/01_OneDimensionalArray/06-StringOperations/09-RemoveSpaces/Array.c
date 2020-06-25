#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	int MyStrLen(char[]);
	char str[MAX_STRING_LENGTH], strSpaceRemoved[MAX_STRING_LENGTH];
	int i, j, iStringLength;
	
	printf("\n Enter a string : ");
	gets_s(str, MAX_STRING_LENGTH);
	printf("\n string is : %s", str);
	
	iStringLength = MyStrLen(str);
	
	j = 0;
	for(i = 0; i < iStringLength; i++)
	{
		if(str[i] == ' ')
			continue;
		else
		{
			strSpaceRemoved[j] = str[i];
			j++;
		}
	}
	strSpaceRemoved[j] = '\0';
	
	printf("\n String with spaces removed : %s", strSpaceRemoved);
	
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

 Enter a string : c program for space remove

 string is : c program for space remove
 String with spaces removed : cprogramforspaceremove
 
 */

	