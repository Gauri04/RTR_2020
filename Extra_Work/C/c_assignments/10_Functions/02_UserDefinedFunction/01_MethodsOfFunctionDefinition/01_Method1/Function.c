#include<stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	void Add(void);
	
	Add();
	return(0);
}

void Add(void)
{
	int a,b,result;
	
	printf("\n Enter two numbers : ");
	scanf("%d%d", &a, &b);
	result = a + b;
	printf("\n addition : %d", result);
}

/* output *
 Enter two numbers : 2
3

 addition : 5
*/
