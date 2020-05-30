#include<stdio.h>

int main(void)
{
	// variable declaration
	int i = 5;
	float f = 3.9f;
	double d = 8.041997;
	char c = 'A';
	
	printf("\n\n");
	
	printf("i = %d\n", i);
	printf("f = %f\n", f);
	printf("d = %lf\n", d);
	printf("d = %c\n", c);
	
	printf("\n\n");
	
	i = 43;
	f = 6.54f;
	d = 26.1294;
	c = 'P';
	
	printf("i = %d\n", i);
	printf("f = %f\n", f);
	printf("d = %lf\n", d);
	printf("d = %c\n", c);
	
	printf("\n\n");
	return(0);

}

/** output **
i = 5
f = 3.900000
d = 8.041997
d = A


i = 43
f = 6.540000
d = 26.129400
d = P

*/




