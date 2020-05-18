#include<stdio.h>

int main(int argc, char *argv[])
{
	int year = 0;
	printf("\nPlease enter integer value :");
	scanf("%d", &year);
	if((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))
	{
		printf("%d is leap year\n", year);
	}
	else
	{
		printf("%d is not a leap year\n", year);
	}
	return(0);
}

/*
**** Output *****
Please enter integer value :3000
3000 is not a leap year
*/
