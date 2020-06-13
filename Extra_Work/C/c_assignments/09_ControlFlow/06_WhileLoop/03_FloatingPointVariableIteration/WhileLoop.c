#include<stdio.h>

int main()
{
	float f, fNum;
	
	fNum = 1.2f;
	printf("\n Printing numbers from %f to %f", fNum, (fNum * 10.0f));
	
	f = fNum;
	while(f <= (fNum * 10.0f))
	{
		printf("\n %f", f);
		f = f + fNum;
	}
	
	return(0);
}

/* output *

 Printing numbers from 1.200000 to 12.000000
 1.200000
 2.400000
 3.600000
 4.800000
 6.000000
 7.200000
 8.400000
 9.599999
 10.799999
 11.999999
 
 */


