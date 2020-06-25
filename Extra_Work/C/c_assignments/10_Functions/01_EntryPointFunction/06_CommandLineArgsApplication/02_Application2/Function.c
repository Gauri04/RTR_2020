#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
	int i;
	if(argc != 4)
	{
		printf("\nInvalid");
		printf("\n Cmd line usage : Function.exe <FirstName> <Middlename> <LastName>");
		exit(0);
	}
	
	printf("\n command line args are : ");
	for(i = 0; i < argc; i++)
	{
		printf("\n %s", argv[i]);
	}
	return(0);
}

/* output *
Function.exe Gauri Uday Ranade

 command line args are :
 Function.exe
 Gauri
 Uday
 Ranade
 */