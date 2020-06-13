#include<stdio.h>
int main()
{
	float f1, f2;
	f1 = 1.5;
	
	printf("\n Printing float value from %f to %f", f1, (f1 * 10.0f));
	f2 = f1;
	
	do{
		printf("\n %f",f2);
		f2 = f2 + f1;
	}while(f2 <= f1 * 10.0f);
	
return(0);
	
}

/* output *
 Printing float value from 1.500000 to 15.000000
 1.500000
 3.000000
 4.500000
 6.000000
 7.500000
 9.000000
 10.500000
 12.000000
 13.500000
 15.000000
 */
 
 