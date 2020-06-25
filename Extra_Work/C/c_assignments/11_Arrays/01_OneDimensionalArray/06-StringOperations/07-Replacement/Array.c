// To replace all the vowels in the string with '*'

#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	int MyStrLen(char[]);
	void MyStrCpy(char[], char[]);
	char str[MAX_STRING_LENGTH], strReplaced[MAX_STRING_LENGTH];
	int i, iStringLength;
	
	printf("\n Enter a string : ");
	gets_s(str, MAX_STRING_LENGTH);
	printf("\n str : %s", str);
	
	MyStrCpy(strReplaced, str);
	iStringLength = MyStrLen(str);
	
	for(i = 0; i < iStringLength; i++)
	{
		switch(str[i])
		{
			case 'A':
			case 'a':
				
			case 'E':
			case 'e':
				
			case 'I':
			case 'i':
				
			case 'O':
			case 'o':
				
			case 'U':
			case 'u':
				strReplaced[i] = '*';
				break;
				
			default :
				break;
		}
		
	}	
	
	printf("\n New String : %s", strReplaced);
}

void MyStrCpy(char dest[], char source[])
{
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
 Enter a string : this is string replace program

 str : this is string replace program
 New String : th*s *s str*ng r*pl*c* pr*gr*m
 */