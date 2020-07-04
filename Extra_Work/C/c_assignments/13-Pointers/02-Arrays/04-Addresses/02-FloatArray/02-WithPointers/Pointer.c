#include<stdio.h>

int main()
{
	float grfArray[10];
	float *grfPtr = NULL;
	int gri;
	
	for(gri = 0; gri < 10; gri++)
		grfArray[gri] = (float) (gri + 1) * 1.5f;
	
	// ptr
	grfPtr = grfArray;
	printf("\n Printing elements of array using pointer : ");
	
	for(gri = 0; gri < 10; gri++)
		printf("\n ptr[%d] is : %f at address : %p", gri, *(grfPtr + gri), (grfPtr + gri));
	
	return(0);
}

/* output *

 Printing elements of array using pointer :
 ptr[0] is : 1.500000 at address : 006FF7F8
 ptr[1] is : 3.000000 at address : 006FF7FC
 ptr[2] is : 4.500000 at address : 006FF800
 ptr[3] is : 6.000000 at address : 006FF804
 ptr[4] is : 7.500000 at address : 006FF808
 ptr[5] is : 9.000000 at address : 006FF80C
 ptr[6] is : 10.500000 at address : 006FF810
 ptr[7] is : 12.000000 at address : 006FF814
 ptr[8] is : 13.500000 at address : 006FF818
 ptr[9] is : 15.000000 at address : 006FF81C
 
*/



