
#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	int MyStrLen(char[]);
	char str[MAX_STRING_LENGTH];
	int len;
	
	
	printf("\n Enter a string : ");
	gets_s(str, MAX_STRING_LENGTH);
	
	printf("\n str : %s", str);
	len = MyStrLen(str);
	printf("\n String length : %d", len);
	
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
 Enter a string : hello there

 str : hello there
 String length : 11
 */