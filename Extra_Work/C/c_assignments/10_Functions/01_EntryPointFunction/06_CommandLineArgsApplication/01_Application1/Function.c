#include<stdio.h>
#include<ctype.h>	//for atio()
#include<stdlib.h>	//for exit()

int main(int argc, char *argv[], char *envp[])
{
	int num, i;
	int sum = 0;
	
	if(argc == 1)
	{
		printf("\n No numbers given for addition");
		exit(0);
	}
	
	printf("Sum of all integre command line args are : ");
	
	for(i = 0; i < argc; i++)
	{
		num = atoi(argv[i]);
		sum = sum + num;
	}
	printf("%d", sum);
	
	return(0);
	
}

/* output *
Function.exe 10 20 30
Sum of all integre command line args are : 60
*/