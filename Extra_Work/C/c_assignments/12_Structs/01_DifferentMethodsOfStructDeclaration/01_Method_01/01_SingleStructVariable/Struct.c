#include<stdio.h>

struct MyData
{
	int i;
	float j;
	double d;
	char c;
}data; 			//global declaration

int main()
{
	int i_size;
	int f_size;
	int d_size;
	int c_size;
	int struct_MyData_size;
	
	data.i = 30;
	data.j = 32.4;
	data.d = 54.7676;
	data.c = 'g';
	
	printf("\n i : %d", data.i);
	printf("\n j : %f", data.j);
	printf("\n d : %lf", data.d);
	printf("\n c : %c", data.c);
	
	
	i_size = sizeof(data.i);
	f_size = sizeof(data.j);
	d_size = sizeof(data.d);
	c_size = sizeof(data.c);
	
	printf("\n\n size of : ");
	printf("\n \t i : %d", i_size);
	printf("\n \t j : %d", f_size);
	printf("\n \t d : %d", d_size);
	printf("\n \t c : %d", c_size);
	
	struct_MyData_size = sizeof(struct MyData);
	printf("\n\n size of struct MyData : %d", struct_MyData_size);
	
	return(0);
	
}

/* output *

 i : 30
 j : 32.400002
 d : 54.767600
 c : g

 size of :
         i : 4
         j : 4
         d : 8
         c : 1

 size of struct MyData : 24
 
 */



