#include<stdio.h>

struct MyData
{
	int i;
	float f;
	double d;
	char c;
};

int main()
{
	struct MyData md;
	md.i = 10;
	md.f = 34.45f;
	md.d = 79.9898;
	md.c = 'c';
	
	// Display data
	printf("\n i : %d", md.i);
	printf("\n f : %f", md.f);
	printf("\n d : %lf", md.d);
	printf("\n c : %c", md.c);
	
	// Display address
	printf("\n\n Address of i starts from : %p", &md.i);
	printf("\n\n Address of f starts from : %p", &md.f);
	printf("\n\n Address of d starts from : %p", &md.d);
	printf("\n\n Address of c starts from : %p", &md.c);
	
	printf("\n\n Address of struct MyData md starts from : %p", &md);
	
	return(0);
}

/* output *

 i : 10
 f : 34.450001
 d : 79.989800
 c : c

 Address of i starts from : 0133FC0C

 Address of f starts from : 0133FC10

 Address of d starts from : 0133FC14

 Address of c starts from : 0133FC1C

 Address of struct MyData md starts from : 0133FC0C
 
 */
