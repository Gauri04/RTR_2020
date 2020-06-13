#include<stdio.h>

int main()
{
	struct MyData
	{
		int i;
		float f;
		double d;
		char c;
	}data = {12, 23.43, 6565.4343, 'v'};
	
	printf("\n Members of struct MyData are :");
	printf("\n i : %d", data.i);
	printf("\n f : %f", data.f);
	printf("\n d : %lf", data.d);
	printf("\n c : %c",data.c);
	
	return(0);
	
}

/* output *

 Members of struct MyData are :
 i : 12
 f : 23.430000
 d : 6565.434300
 c : v
 */


