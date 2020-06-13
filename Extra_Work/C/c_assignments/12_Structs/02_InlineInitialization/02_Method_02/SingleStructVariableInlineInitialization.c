#include<stdio.h>

struct MyData
{
	int i;
	float f;
	double d;
	char c;
};

struct MyData md = {12, 323.5, 4343.32323, 'c'};

int main()
{
	printf("\n members of struct MyData are : ");
	printf("\n i : %d", md.i);
	printf("\n f : %f", md.f);
	printf("\n d : %lf", md.d);
	printf("\n c : %c",md.c);
	
	return(0);
}

/* output *
 members of struct MyData are :
 i : 12
 f : 323.500000
 d : 4343.323230
 c : c
 */