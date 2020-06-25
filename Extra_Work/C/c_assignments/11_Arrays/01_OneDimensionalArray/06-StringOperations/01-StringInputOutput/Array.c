#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	char str[MAX_STRING_LENGTH];
	
	printf("\n Enter a string : ");
	gets_s(str, MAX_STRING_LENGTH);
	
	printf("\n str : %s", str);
	return(0);
	
}

/* output

 Enter a string : hello

 str : hello
 */