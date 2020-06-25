#include<stdio.h>

int main(int argc, char *argv[])
{
	int i;
	printf("\n No. of command line arguments : %d", argc);
	
	printf("\n Command line arguments : ");
	for(i = 0; i < argc; i++)
	{
		printf("\n Command line argument no : %d, and argument : %s", (i + 1), argv[i]);
	}
	return(0);
	
}

/* output *

 No. of command line arguments : 1
 Command line arguments :
 Command line argument no : 1, and argument : Function.exe
 */