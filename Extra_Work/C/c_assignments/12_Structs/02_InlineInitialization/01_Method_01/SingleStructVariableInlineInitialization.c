#include<stdio.h>
struct str
{
	int i;
	float f;
	double d;
	char c;
}data = {30, 4.5f, 11.3232, 'A'};

int main()
{
	printf("\n members of struct str are : ");
	printf("\n i : %d", data.i);
	printf("\n f : %f", data.f);
	printf("\n d : %lf", data.d);
	printf("\n c : %c",data.c);
	
	return(0);
}


/* output *

 members of struct str are :
 i : 30
 f : 4.500000
 d : 11.323200
 c : A
 
 */
