#include<stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int Add(void);
	int result;
	
	result = Add();
	printf("\n result = %d", result);
	return(0);
}

int Add(void)
{
	int a,b,sum;
	
	printf("\n Enter two numbers : ");
	scanf("%d%d", &a, &b);
	sum = a + b;
	return(sum);
}

/* output *
 Enter two numbers : 3 3

 result = 6
 */

