/*
C program to print hello wolrd using char array
*/
#include<stdio.h>

int main(int argc, char *argv[])
{
	char myString[] = "Hello World\0";
	printf("%s\n", myString);
	return(0);
	
}

/*
**** Output *****

Hello World
*/
