#include<stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	void Add(int, int);
	int a,b;
	
	printf("\n Enter two numbers : ");
	scanf("%d%d", &a, &b);
	
	Add(a,b);
	
	return(0);
}

void Add(int a, int b)
{
	int result = a + b;
	printf("\n result = %d", result);
}
/* ouput *
 Enter two numbers : 4 4

 result = 8
 */