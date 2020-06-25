#include<stdio.h>
#define MAX_STRING_LENGTH 512

int main()
{
	int MyStrLen(char[]);
	
	char str[6][15] = {"Hello", "Welcome", "To", "RTR", "Batch", "2020-21"};
	int  strSize;
	int strNumRows;
	int i, j, iStrLengths[10];
	
	
	strSize = sizeof(str);
	
	printf("\n Size of 2D char array : %d", strSize);
	
	strNumRows = strSize / sizeof(str[0]);
	printf("\n Number of rows in str : %d", strNumRows);
	
	for(i = 0; i < strNumRows; i++)
	{
		iStrLengths[i] = MyStrLen(str[i]);
	}
	
	printf("\n Entire Array str : \n");
	for(i = 0; i < strNumRows; i++)
	{
		printf("\n %t %s",str[i]);
	}
	
	printf("\n\n Strings in str : \n");
	for(i = 0; i < strNumRows; i++)
	{
		printf("\n String Number : %d : %s",(i + 1), str[i]);
		
		for(j = 0; j < iStrLengths[i]; j++)
		{
			printf("\n Character %d = %c", (j+1), str[i][j]);
		}
		printf("\n");
	}
	return(0);	
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

 Size of 2D char array : 90
 Number of rows in str : 6
 Entire Array str :

  Hello
  Welcome
  To
  RTR
  Batch
  2020-21

 Strings in str :

 String Number : 1 : Hello
 Character 1 = H
 Character 2 = e
 Character 3 = l
 Character 4 = l
 Character 5 = o

 String Number : 2 : Welcome
 Character 1 = W
 Character 2 = e
 Character 3 = l
 Character 4 = c
 Character 5 = o
 Character 6 = m
 Character 7 = e

 String Number : 3 : To
 Character 1 = T
 Character 2 = o

 String Number : 4 : RTR
 Character 1 = R
 Character 2 = T
 Character 3 = R

 String Number : 5 : Batch
 Character 1 = B
 Character 2 = a
 Character 3 = t
 Character 4 = c
 Character 5 = h

 String Number : 6 : 2020-21
 Character 1 = 2
 Character 2 = 0
 Character 3 = 2
 Character 4 = 0
 Character 5 = -
 Character 6 = 2
 Character 7 = 1
 
 */











	