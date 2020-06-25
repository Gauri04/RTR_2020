
#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	char str[MAX_STRING_LENGTH];
	int len;
	
	
	printf("\n Enter a string : ");
	gets_s(str, MAX_STRING_LENGTH);
	
	printf("\n str : %s", str);
	len = strlen(str);
	printf("\n String length : %d", len);
	
	return(0);
	
}
/* ouput

 Enter a string : welcome

 str : welcome
 String length : 7
 */