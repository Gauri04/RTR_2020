#include<stdio.h>
#include<stdlib.h>

#define MAX_STRING_LENGTH 512

int main()
{
	void MyStrCat(char *, char *);
	int MyStrLen(char *);
	
	char *grcArray = NULL;
	char *grcArray2 = NULL;


	
	grcArray = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
	
	if(grcArray == NULL)
	{
		printf("Failed to allocate memory");
		exit(0);
	}
	
	printf("\n Enter a string : ");
	gets_s(grcArray, MAX_STRING_LENGTH);
	
	printf("\n Entered string is : %s", grcArray);
	
	grcArray2 = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
	if(grcArray2 == NULL)
	{
		printf("Failed to allocate memory");
		exit(0);
	}
	
	printf("\n Enter a second string : ");
	gets_s(grcArray2, MAX_STRING_LENGTH);
	
	MyStrCat(grcArray, grcArray2);
	
	printf("\n Concatenated string is : %s", grcArray);
	
	if(grcArray2)
	{
		free(grcArray2);
		grcArray2 = NULL;
	}
	
	if(grcArray)
	{
		free(grcArray);
		grcArray = NULL;
	}
		
	return(0);	
}

void MyStrCat(char *dest, char *src)
{
	int MyStrLen(char *);
	int grStringLengthSrc = 0;
	int grStringLengthDest = 0;
	int i, j;
	
	grStringLengthSrc = MyStrLen(src);
	grStringLengthDest = MyStrLen(dest);
	
	
	for(i = grStringLengthDest, j = 0;   j < grStringLengthSrc;   i++, j++)
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

/* output *
 Enter a string : Hello

 Entered string is : Hello
 Enter a second string : World

 Concatenated string is : HelloWorld
 */