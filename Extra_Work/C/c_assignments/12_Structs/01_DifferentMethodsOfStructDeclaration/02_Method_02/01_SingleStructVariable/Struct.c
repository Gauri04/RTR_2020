#include<stdio.h>

struct MyData
{
	int i;
	float f;
	double d;
};

struct MyData grData; 	// global declaration

int main()
{
	int i_size;
	int f_size;
	int d_size;
	int MyData_Size;
	
	grData.i = 80;
	grData.f = 65.4;
	grData.d = 5476.76;
	
	printf("\n members of struct grData : ");
	printf("\n i : %d", grData.i);
	printf("\n j : %f", grData.f);
	printf("\n d : %lf", grData.d);
	
	i_size = sizeof(grData.i);
	f_size = sizeof(grData.f);
	d_size = sizeof(grData.d);
	
	printf("\n\n size of data members: ");
	printf("\n \t i : %d", i_size);
	printf("\n \t j : %d", f_size);
	printf("\n \t d : %d", d_size);
	
	MyData_Size = sizeof(struct MyData);
	printf("\n\n Struct MyData size : %d", MyData_Size);
	
	return(0);
	
}
/* output *

 members of struct grData :
 i : 80
 j : 65.400002
 d : 5476.760000

 size of data members:
         i : 4
         j : 4
         d : 8

 Struct MyData size : 16

*/


