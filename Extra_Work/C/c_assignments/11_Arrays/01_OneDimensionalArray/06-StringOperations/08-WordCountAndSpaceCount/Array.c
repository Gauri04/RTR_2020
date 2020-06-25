//Word count and space count
#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	int MyStrLen(char[]);
	char str[MAX_STRING_LENGTH];
	int iStringLength, i, word_count = 0, space_count = 0;
	
	printf("\n Enter a string : ");
	gets_s(str, MAX_STRING_LENGTH);
	iStringLength = MyStrLen(str);
	
	for(i = 0; i < iStringLength; i++)
	{
		switch(str[i])
		{
			case 32 : 
				space_count++;
		}
	}
	
	word_count = space_count + 1;
	printf("\n str : %s", str);
	printf("\n Word count : %d", word_count);	
	printf("\n Space count : %d", space_count);

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
 Enter a string : welcome to c programming

 str : welcome to c programming
 Word count : 4
 Space count : 3
 
 */


