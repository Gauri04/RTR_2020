#include<stdio.h>

int main()
{
	FILE *pFile = NULL;
	
	if(fopen_s(&pFile, "GRLog.txt", "w") != 0)
	{
		printf("Error: Cannot open desired file \n");
	}
	fprintf(pFile, "India is my country. \n");
	fclose(pFile);
	
	return(0);
}


