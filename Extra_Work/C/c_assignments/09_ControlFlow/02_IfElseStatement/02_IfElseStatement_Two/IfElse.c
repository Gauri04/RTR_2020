#include<stdio.h>
int main(void)
{
	int age;
	
	printf("\n Enter age : ");
	scanf("%d", &age);
	
	if(age >= 18)
	{
		printf("\n\n Entering if block");
		printf("\n You are eligible for voting");
	}
	else
	{
		printf("\n\n Entering else block");
		printf("\n You are not eligible for voting");
	}
	printf("\n Bye !");
	return(0);
	
}

/* output *
 Enter age : 12


 Entering else block
 You are not eligible for voting
 Bye !
 */
 
 

