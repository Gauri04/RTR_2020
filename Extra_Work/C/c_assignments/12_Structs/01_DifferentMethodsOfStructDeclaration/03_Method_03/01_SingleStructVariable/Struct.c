#include<stdio.h>

int main()
{
	struct MyData
	{
		int i;
		float f;
		double d;
	}grData;			//local declaration
	
	int i_size;
	int f_size;
	int d_size;
	int struct_MyData_Size;
	
	grData.i = 40;
	grData.f = 12.43;
	grData.d = 54.7356;
	
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
	
	struct_MyData_Size = sizeof(struct MyData);
	printf("\n\n Struct MyData size : %d", struct_MyData_Size);
	
	return(0);
}

/* output *

 members of struct grData :
 i : 40
 j : 12.430000
 d : 54.735600

 size of data members:
         i : 4
         j : 4
         d : 8

 Struct MyData size : 16
 */



