#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	void MyStrCat(char[], char[]);
	char str[MAX_STRING_LENGTH], str2[MAX_STRING_LENGTH];
	
	
	printf("\n Enter a string : ");
	gets_s(str, MAX_STRING_LENGTH);
	printf("\n Enter another string : ");
	gets_s(str2, MAX_STRING_LENGTH);
	
	printf("\n str : %s", str);
	printf("\n str2 : %s", str2);
	
	MyStrCat(str, str2);
	
	printf("\n string1 after concatenation : %s", str);
	printf("\n string2 after concatenation : %s", str2);
	
	return(0);
}

void MyStrCat(char dest[], char source[])
{
	int MyStrLen(char[]);
	int iStrLengthSource = 0, iStringLengthDest = 0;
	int i,j;
	
	iStrLengthSource = MyStrLen(source);
	iStringLengthDest =  MyStrLen(dest);
	
	for(i = iStringLengthDest, j = 0; j < iStrLengthSource; i++, j++)
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
 Enter a string : gauri

 Enter another string : ranade

 str : gauri
 str2 : ranade
 string1 after concatenation : gauriranade
 string2 after concatenation : ranade
 
 */




