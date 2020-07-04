#include<stdio.h>
#include<stdlib.h>

#define MAX_STRING_LENGTH 512

int main()
{
	int MyStrLen(char *);
	
	char *grcArray = NULL;
	int griStringLength = 0;
	
	grcArray = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
	
	if(grcArray == NULL)
	{
		printf("Failed to allocate memory");
		exit(0);
	}
	
	printf("\n Enter a string : ");
	gets_s(grcArray, MAX_STRING_LENGTH);
	
	printf("\n Entered string is : %s", grcArray);
	
	griStringLength = MyStrLen(grcArray);
	printf("\n Length if string is : %d", griStringLength);
	
	if(grcArray)
	{
		free(grcArray);
		grcArray = NULL;
	}
	
	return(0);
	
}

int MyStrLen(char *str)
{
	int j, grStringLength = 0;
	
	for(j = 0; j < MAX_STRING_LENGTH; j++)
	{
		if(*(str + j) == 0)
			break;
		else
			grStringLength++;
	}
	return(grStringLength);
}

/* output *

 Enter a string : gauri

 Entered string is : gauri
 Length if string is : 5
 
 */














