#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	int MyStrLen(char[]);
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
			chArrayCapitalizeFirstLetterOfEveryWord[i] = toupper(chArray[i]);
		
		else if(chArray[i] == ' ')
		{
			chArrayCapitalizeFirstLetterOfEveryWord[i] = chArray[i];
			chArrayCapitalizeFirstLetterOfEveryWord[j + 1] = toupper(chArray[i + 1]);
			j++;
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

/* ouput *
 Enter a string : c program for capital letter

 Entered string is : c program for capital letter
 String with capital letters : C Program For Capital Letter
 */




