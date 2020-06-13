#include<stdio.h>

int main(void)
{
	int num;
	
	printf("Enter a number : ");
	scanf("%d", &num);
	
	if(num < 0)
		printf("\n num : %d is less than 0", num);
	
	else if((num > 0) && (num <= 100))
		printf("\n num : %d is between 0 and 100", num);
	
	else if((num > 100) && (num <= 200))
		printf("\n num : %d is between 100 and 200", num);
	
	else if((num > 200) && (num <= 300))
		printf("\n num : %d is between 200 and 300", num);
	
	else if((num > 300) && (num <= 400))
		printf("\n num : %d is between 300 and 400", num);
	
	else if((num > 400) && (num <= 500))
		printf("\n num : %d is between 400 and 500", num);
	
	else if(num > 500)
		printf("\n num : %d is greater than 500", num);
	
	return(0);
}

/* output *
Enter a number : 455

 num : 455 is between 400 and 500
 */




