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
	struct MyData d1 = {21, 323.2f, 54.5555, 'g'};
	struct MyData d2 = {'P', 43.2f, 21.3232, 68};
	struct MyData d3 = {34, 'G'};
	struct MyData d4 = {79};
	
	printf("\n members of MyData d1 :");
	printf("\n i : %d", d1.i);
	printf("\n f : %f", d1.f);
	printf("\n d : %lf", d1.d);
	printf("\n c : %c",d1.c);
	
	printf("\n members of MyData d2 :");
	printf("\n i : %d (ASCII value of 'P')", d2.i);
	printf("\n f : %f", d2.f);
	printf("\n d : %lf", d2.d);
	printf("\n c : %c",d2.c);
	
	printf("\n members of MyData d3 :");
	printf("\n i : %d", d3.i);
	printf("\n f : %f (ASCII float value of 'G')", d3.f);
	printf("\n d : %lf", d3.d);
	printf("\n c : %c",d3.c);
	
	printf("\n members of MyData d4 :");
	printf("\n i : %d", d4.i);
	printf("\n f : %f", d4.f);
	printf("\n d : %lf", d4.d);
	printf("\n c : %c",d4.c);
	
	return(0);
	
}

/* output *


 members of MyData d1 :
 i : 21
 f : 323.200012
 d : 54.555500
 c : g
 members of MyData d2 :
 i : 80 (ASCII value of 'P')
 f : 43.200001
 d : 21.323200
 c : D
 members of MyData d3 :
 i : 34
 f : 71.000000 (ASCII float value of 'G')
 d : 0.000000
 c :
 members of MyData d4 :
 i : 79
 f : 0.000000
 d : 0.000000
 c :


*/




