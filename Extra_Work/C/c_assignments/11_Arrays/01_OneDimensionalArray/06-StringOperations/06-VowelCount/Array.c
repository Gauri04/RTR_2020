#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	int MyStrLen(char[]);
	char str[MAX_STRING_LENGTH];
	int countA = 0, countE = 0, countI = 0, countO = 0, countU = 0;
	int i, iStringLength;
	
	printf("\n Enter a string : ");
	gets_s(str, MAX_STRING_LENGTH);
	printf("\n str : %s", str);
	
	iStringLength = MyStrLen(str);
	
	for(i = 0; i < iStringLength; i++)
	{
		switch(str[i])
		{
			case 'A':
			case 'a':
				countA++;
				break;
				
			case 'E':
			case 'e':
				countE++;
				break;
				
			case 'I':
			case 'i':
				countI++;
				break;
				
			case 'O':
			case 'o':
				countO++;
				break;
				
			case 'U':
			case 'u':
				countU++;
				break;
				
			default :
				break;
		}
		
	}	
	
	printf("\n In String %s, 'A' has occured %d times", str, countA);
	printf("\n In String %s, 'E' has occured %d times", str, countE);
	printf("\n In String %s, 'I' has occured %d times", str, countI);
	printf("\n In String %s, 'O' has occured %d times", str, countO);
	printf("\n In String %s, 'U' has occured %d times", str, countU);
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

 str : gauri
 In String gauri, 'A' has occured 1 times
 In String gauri, 'E' has occured 0 times
 In String gauri, 'I' has occured 1 times
 In String gauri, 'O' has occured 0 times
 In String gauri, 'U' has occured 1 times
 */
