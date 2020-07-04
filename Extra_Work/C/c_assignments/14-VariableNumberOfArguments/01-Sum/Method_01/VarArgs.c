#include<stdio.h>
#include<stdarg.h>

int main()
{
	int CalculateSum(int, ...);
	int grAnswer;
	
	grAnswer = CalculateSum(5, 10, 20, 30, 40 ,50);
	printf("\n Answer : %d", grAnswer);
	
	grAnswer = CalculateSum(0);
	printf("\n Answer : %d", grAnswer);
	
	return(0);
}

int CalculateSum(int num, ...)
{
	int grTotal = 0;
	int n;
	va_list gr_va_list;
	
	va_start(gr_va_list, num);
	
	while(num)
	{
		n = va_arg(gr_va_list, int);
		grTotal = grTotal + n;
		num--;
	}
	va_end(gr_va_list);
	return(grTotal);		
}

/* output *
 Answer : 150
 Answer : 0
 */

