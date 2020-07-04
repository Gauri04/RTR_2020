#include<stdio.h>
#include<stdlib.h>

#define MAX_STRING_LENGTH 512

int main()
{
	void MyStrCpy(char *, char *);
	int MyStrLen(char *);
	
	char *grcArray = NULL;
	char *grcArrayCopy = NULL;


	
	grcArray = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
	
	if(grcArray == NULL)
	{
		printf("Failed to allocate memory");
		exit(0);
	}
	
	printf("\n Enter a string : ");
	gets_s(grcArray, MAX_STRING_LENGTH);
	
	printf("\n Entered string is : %s", grcArray);
	
	grcArrayCopy = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
	if(grcArrayCopy == NULL)
	{
		printf("Failed to allocate memory");
		exit(0);
	}
	
	MyStrCpy(grcArrayCopy, grcArray);
	
	printf("\n Copied string is : %s", grcArrayCopy);
	
	if(grcArrayCopy)
	{
		free(grcArrayCopy);
		grcArrayCopy = NULL;
	}
	
	if(grcArray)
	{
		free(grcArray);
		grcArray = NULL;
	}
		
	return(0);	
}

void MyStrCpy(char *dest, char *src)
{
	int MyStrLen(char *);
	int grStringLength = 0;
	int j;
	
	grStringLength = MyStrLen(src);
	for(j = 0; j < grStringLength; j++)
	{
		*(dest + j) = *(src + j);
	}
	
	*(dest + j) = '\0';
	
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
 Copied string is : gauri
 
 */
























	
