#include<stdio.h>
#include<stdarg.h>

int main()
{
	int CalculateSum(int, ...);
	int grAnswer;
	
	grAnswer = CalculateSum(5, 10, 20, 30, 40 ,50);
	printf("\n Answer : %d", grAnswer);
	
	grAnswer = CalculateSum(10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
	printf("\n Answer : %d", grAnswer);
	
	grAnswer = CalculateSum(0);
	printf("\n Answer : %d", grAnswer);
	
	return(0);
}

int CalculateSum(int num, ...)
{
	int va_CalculateSum(int, va_list);
	
	int grSum = 0;
	va_list gr_va_list;
	
	va_start(gr_va_list, num);
	
	grSum = va_CalculateSum(num, gr_va_list);
	
	va_end(gr_va_list);
	return(grSum);
}

int va_CalculateSum(int num, va_list list)
{
	int n;
	int grTotal = 0;
	
	while(num)
	{
		n = va_arg(list, int);
		grTotal = grTotal + n;
		num--;
	}
	return(grTotal);	
}

/* output *

 Answer : 150
 Answer : 10
 Answer : 0
 
 */





