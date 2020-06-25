#include<stdio.h>
#define MAX_STRING_LENGTH 512

#define SPACE ' '
#define COMMA ','
#define FULLSTOP '.'
#define EXCLAIMATION '!'
#define QUESTION_MARK '?'

int main()
{
	int MyStrLen(char[]);
	char MyToUpper(char);
	char chArray[MAX_STRING_LENGTH], chArrayCapitalizeFirstLetterOfEveryWord[MAX_STRING_LENGTH];
	int iStringLength, i, j;
		
	printf("\n Enter a string : ");
	gets_s(chArray, MAX_STRING_LENGTH);
	printf("\n Entered string is : %s", chArray);
	
	iStringLength = MyStrLen(chArray);	
	j = 0;
	for(i = 0; i < iStringLength; i++)
	{
		if(i == 0)
			chArrayCapitalizeFirstLetterOfEveryWord[i] = MyToUpper(chArray[i]);
		
		else if(chArray[i] == ' ')
		{
			chArrayCapitalizeFirstLetterOfEveryWord[i] = chArray[i];
			chArrayCapitalizeFirstLetterOfEveryWord[j + 1] = MyToUpper(chArray[i + 1]);
			j++;
			i++;
		}
		else if((chArray[i] == FULLSTOP || chArray[i] == COMMA || 
			chArray[i] == EXCLAIMATION || chArray[i] == QUESTION_MARK) && chArray[i] == SPACE)
		{
			chArrayCapitalizeFirstLetterOfEveryWord[j] = chArray[i];
			chArrayCapitalizeFirstLetterOfEveryWord[j + 1] = SPACE;
			chArrayCapitalizeFirstLetterOfEveryWord[j + 2] = MyToUpper(chArray[i + 1]);
			
			j = j + 2;
			i++;
		}
		
		else
			chArrayCapitalizeFirstLetterOfEveryWord[j] = chArray[j];
			
		j++;
	}
	
	chArrayCapitalizeFirstLetterOfEveryWord[j] = '\0';
	
	printf("\n String with capital letters : %s", chArrayCapitalizeFirstLetterOfEveryWord);
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

char MyToUpper(char ch)
{
	int num;
	int c;
	
	// ASCII value of 'a' (97) - ASCII value of 'A' (65) = 32 is difference between capital and lower case letters
	// ASCII value of a to z : 97 - 122
	// ASCII value of A to Z : 65 - 90
	
	num = 'a' - 'A';
	if((int)ch >= 97 && (int)ch <= 122)
	{
		c = (int)ch - num;
		return((char)c);
	}
	else
		return(ch);
	
}

/* output *

 Enter a string : c program for ? uppercase letter. below

 Entered string is : c program for ? uppercase letter. below
 String with capital letters : C Program For ? Uppercase Letter. Below
 
 */





















