#include<stdio.h>
int main(void)
{
	int num;
	printf("\n Enter number : ");
	scanf("%d", &num);
	
	if(num < 0)
	{
		printf("\n num %d is less than zero", num);
	}
	
	if((num > 0) && (num <= 100))
	{
		printf("\n num %d is between 0 and hundred", num);
	}
	
	if((num > 100) && (num <= 200))
	{
		printf("\n num %d is between 100 and 200", num);
	}
	
	if((num > 200) && (num <= 300))
	{
		printf("\n num %d is between 200 and 300", num);
	}
	
	if((num > 300) && (num <= 400))
	{
		printf("\n num %d is between 300 and 400", num);
	}
	
	if((num > 400) && (num <= 500))
	{
		printf("\n num %d is between 400 and 500", num);
	}
	
	if(num > 500)
	{
		printf("\n num %d is greater than 500", num);
	}
	
	return(0);
}

/* output*

 Enter number : 301

 num 301 is between 300 and 400
 */








