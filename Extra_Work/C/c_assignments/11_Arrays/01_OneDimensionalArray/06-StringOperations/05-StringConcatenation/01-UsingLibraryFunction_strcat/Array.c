#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	char str[MAX_STRING_LENGTH], str2[MAX_STRING_LENGTH];
	
	
	printf("\n Enter a string : ");
	gets_s(str, MAX_STRING_LENGTH);
	printf("\n Enter another string : ");
	gets_s(str2, MAX_STRING_LENGTH);
	
	strcat(str, str2);
	
	printf("\n Concatenated string : %s", str);
	
	return(0);
}

/* output *

 Enter a string : gauri

 Enter another string : ranade

 Concatenated string : gauriranade
 */