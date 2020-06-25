#include<stdio.h>
#include<string.h> //strrev()
#define MAX_STRING_LENGTH 512

int main()
{
	char str[MAX_STRING_LENGTH];
	
	printf("\n Enter a string : ");
	gets_s(str, MAX_STRING_LENGTH);
	
	printf("\n Original str : %s", str);
	
	printf("\n Reverse str : %s", strrev(str));
	
	return(0);
	
}

/* output *
 Enter a string : array

 Original str : array
 Reverse str : yarra
 */


