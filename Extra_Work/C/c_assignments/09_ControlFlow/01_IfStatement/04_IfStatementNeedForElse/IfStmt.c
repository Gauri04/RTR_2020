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
	printf("\n You are not eligible for voting");
	return(0);
	
}

/* output *
 Enter age : 34

 You are eligible for voting !!!
 You are not eligible for voting
 */
