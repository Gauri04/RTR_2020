
#include<stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int Add(int, int);
	int a,b, result;
	
	printf("\n Enter two numbers : ");
	scanf("%d%d", &a, &b);
	
	result = Add(a,b);
	printf("\n result = %d", result);
	return(0);
}

int Add(int a, int b)
{
	int sum = a + b;
	return(sum);
	
}

/* ouput *
 Enter two numbers : 7
7

 result = 14
 */