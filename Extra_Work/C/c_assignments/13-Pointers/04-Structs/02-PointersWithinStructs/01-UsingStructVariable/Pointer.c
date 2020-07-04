#include<stdio.h>

struct GRData
{
	int i;
	int *griptr;
	
	float f;
	float *grfptr;
	
	double d;
	double *grdptr;
};

int main()
{
	struct GRData grData;
	
	grData.i = 10;
	grData.griptr = &grData.i;
	
	grData.f = 33.33f;
	grData.grfptr = &grData.f;
	
	grData.d = 3.1426878;
	grData.grdptr = &grData.d;
	
	printf("\n i : %d \t address of i : %p", *(grData.griptr), grData.griptr);
	printf("\n f : %f \t address of f : %p", *(grData.grfptr), grData.grfptr);
	printf("\n d : %lf \t address of d : %p", *(grData.grdptr), grData.grdptr);
	
	return(0);
}

/* output *

 i : 10          address of i : 012FFA1C
 f : 33.330002   address of f : 012FFA24
 d : 3.142688    address of d : 012FFA2C
 
 */




























