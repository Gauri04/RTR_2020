#include<stdio.h>
#include<stdarg.h>

#define NUM_TO_BE_FOUND 3
#define NUM_ELEMENTS 10

int main()
{
	void FindNumber(int, int, ...);
	
	FindNumber(NUM_TO_BE_FOUND, NUM_ELEMENTS, 3,4,5,6,3,8,7,3,0,3);
	
	return(0);
}

void FindNumber(int numToFind, int num, ...)
{
	int grCount = 0;
	int n;
	va_list gr_va_list;
	
	va_start(gr_va_list, num);
	
	while(num)
	{
		n = va_arg(gr_va_list, int);
		if(n == numToFind)
			grCount++;
		
		num--;
	}
	
	va_end(gr_va_list);
	
	if(grCount == 0)
		printf("Number %d not found", numToFind);
	else
		printf("Number %d found %d times! ", numToFind, grCount);
}

/* output *
Number 3 found 4 times!
*/







