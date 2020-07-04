#include<stdio.h>
#include<stdlib.h>

#define MAX_STRING_LENGTH 512

int main()
{
	char* ReplaceVowelsWithHashSymbol(char *);
	
	char grcArray[MAX_STRING_LENGTH];
	char *grReplacedStr = NULL;
	
	printf("\n Enter a string : ");
	gets_s(grcArray, MAX_STRING_LENGTH);
	
	grReplacedStr = ReplaceVowelsWithHashSymbol(grcArray);
	if(grReplacedStr == NULL)
	{
		printf("\n ReplaceVowelsWithHashSymbol function failed");
		exit(0);
	}

	printf("\n Replaced string is : %s", grReplacedStr);
	
	if(grReplacedStr)
	{
		free(grReplacedStr);
		grReplacedStr = NULL;
	}
	
	return(0);
}

char* ReplaceVowelsWithHashSymbol(char *str)
{
	void MyStrCpy(char *, char *);
	int MyStrLen(char *);
	
	char *newString = NULL;
	int i;
	
	newString = (char *) malloc(MyStrLen(str) * sizeof(char));
	
	if(newString == NULL)
	{
		printf("\n Failed to allocate memory to newString");
		exit(0);
	}
	
	MyStrCpy(newString, str);
	
	for(i = 0; i < MyStrLen(str); i++)
	{
		switch(newString[i])
		{
					case 'a':
			case 'A':
			case 'e':
			case 'E':
			case 'i':
			case 'I':
			case 'o':
			case 'O':
			case 'u':
			case 'U':
				newString[i] = '#';
				break;
			
			default :
				break;
		}
	}
	
	return(newString);
	
}

void MyStrCpy(char *dest, char *src)
{
	int MyStrLen(char *);
	int grStringLength = 0;
	int j;
	
	grStringLength = MyStrLen(src);
	for(j = 0; j < grStringLength; j++)
	{
		*(dest + j) = *(src + j);
	}
	
	*(dest + j) = '\0';
	
}

int MyStrLen(char *str)
{
	int j, grStringLength = 0;
	
	for(j = 0; j < MAX_STRING_LENGTH; j++)
	{
		if(*(str + j) == 0)
			break;
		else
			grStringLength++;
	}
	return(grStringLength);
}

/* output *

 Enter a string : HelloWorld

 Replaced string is : H#ll#W#rld
 
 */









