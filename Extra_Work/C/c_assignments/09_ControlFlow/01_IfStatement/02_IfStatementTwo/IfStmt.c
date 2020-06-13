#include<stdio.h>
int main(void)
{
	int age;
	printf("\n Enter age : ");
	scanf("%d", &age);
	
	if(age >= 18)
	{
		printf("\n You are eligible for voting !!!");
	}
	return(0);
}

/* output *
 Enter age : 20

 You are eligible for voting !!!
 */

