#include<stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	unsigned int num;
	
	void recursive(unsigned int);
	
	printf("Enter a number : ");
	scanf("\n %d", &num);
	
	recursive(num);
	
	return(0);
}

void recursive(unsigned int n)
{
	printf("\n %d", n);
	
	if(n > 0)
	{
		recursive(n-1);
	}
}

/* ouput *
Enter a number : 5

 5
 4
 3
 2
 1
 0
 */

