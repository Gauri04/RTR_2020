
#include<stdio.h>
#include<stdlib.h>

#define MAX_STRING_LENGTH 512

int main()
{
	void MyStrRev(char *, char *);
	int MyStrLen(char *);
	
	char *grcArray = NULL;
	char *grcArrayRev = NULL;


	
	grcArray = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
	
	if(grcArray == NULL)
	{
		printf("Failed to allocate memory");
		exit(0);
	}
	
	printf("\n Enter a string : ");
	gets_s(grcArray, MAX_STRING_LENGTH);
	
	printf("\n Entered string is : %s", grcArray);
	
	grcArrayRev = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
	if(grcArrayRev == NULL)
	{
		printf("Failed to allocate memory");
		exit(0);
	}
	
	MyStrRev(grcArrayRev, grcArray);
	
	printf("\n Reversed string is : %s", grcArrayRev);
	
	if(grcArrayRev)
	{
		free(grcArrayRev);
		grcArrayRev = NULL;
	}
	
	if(grcArray)
	{
		free(grcArray);
		grcArray = NULL;
	}
		
	return(0);	
}

void MyStrRev(char *dest, char *src)
{
	int MyStrLen(char *);
	int grStringLength = 0;
	int i, j, len;
	
	grStringLength = MyStrLen(src);
	len = grStringLength - 1;
	
	for(i = 0, j = len; i < grStringLength, j >= 0; i++, j--)
	{
		*(dest + i) = *(src + j);
	}
	
	*(dest + i) = '\0';
	
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

/* OUTPUT *

 Enter a string : GAURI

 Entered string is : GAURI
 Reversed string is : IRUAG
 
 */











