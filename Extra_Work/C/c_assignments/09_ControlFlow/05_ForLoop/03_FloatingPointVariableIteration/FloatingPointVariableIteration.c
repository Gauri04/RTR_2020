#include<stdio.h>

int main()
{
	float f;
	float f_num = 2.9f;
	
	printf("\n Printing numbers %f to %f", f_num, (f_num * 10.0f));
	
	for(f = f_num; f <= (f_num * 10.0f); f = f + f_num)
	{
		printf("\n %f", f);
	}
	
	return(0);
	
}

/* output *

 Printing numbers 2.900000 to 29.000000
 2.900000
 5.800000
 8.700001
 11.600000
 14.500000
 17.400000
 20.299999
 23.199999
 26.099998
 28.999998
 */
 
