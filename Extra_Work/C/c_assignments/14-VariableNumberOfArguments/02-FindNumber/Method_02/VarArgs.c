#include<stdio.h>
#include<stdarg.h>

#define NUM_TO_FOUND 3
#define NUM_ELEMENTS 10

int main()
{
	void FindNumber(int, int, ...);
	
	FindNumber(NUM_TO_FOUND, NUM_ELEMENTS, 2, 3, 4, 3, 5, 6, 3, 9, 2, 3);
	
	return(0);
}

void FindNumber(int numToFind, int num, ...)
{
	int va_FindNumber(int, int, va_list);
		
	int grCount = 0;
	int n;
	va_list gr_va_list;
		
	va_start(gr_va_list, num);
		
	grCount = va_FindNumber(numToFind, num, gr_va_list);
		
	if(grCount == 0)
		printf("\n Number %d could not be found.", numToFind);
	else
		printf("\n Number %d found %d times.",numToFind, grCount);
		
}

int va_FindNumber(int numToFind, int num, va_list num_list)
{
	int grNumCount = 0;
	int n;
	
	while(num)
	{
		n = va_arg(num_list, int);
		if(n == numToFind)
			grNumCount++;
		
		num--;
	}
	return(grNumCount);
}


/* output *

 Number 3 found 4 times.
 
 */






























