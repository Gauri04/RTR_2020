#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	char strOriginal[MAX_STRING_LENGTH], strCopy[MAX_STRING_LENGTH];
	int len;
	
	
	printf("\n Enter a string : ");
	gets_s(strOriginal, MAX_STRING_LENGTH);
	
	printf("\n str : %s", strOriginal);
	strcpy(strCopy,strOriginal);
	printf("\n copies string : %s", strCopy);
	return(0);
	
}

/* output 

 Enter a string : thank

 str : thank
 copies string : thank
 */