#include<stdio.h>

int main()
{
	double grdArray[10];
	int gri;
	
	for(gri = 0; gri < 10; gri++)
		grdArray[gri] = (double) (gri + 1) * 1.3333f;
	
	printf("\n Elements of array : \n");
	
	for(gri = 0; gri < 10; gri++)
		printf("\n dArray[%d] is : %lf", gri, grdArray[gri]);
	
	printf("\n\n Elements with their addresses : \n");
	
	for(gri = 0; gri < 10; gri++)
		printf("\n dArray[%d] is : %lf at address : %p", gri, grdArray[gri], &grdArray[gri]);
		
	return(0);
}

/* output *
 Elements of array :

 dArray[0] is : 1.333300
 dArray[1] is : 2.666600
 dArray[2] is : 3.999900
 dArray[3] is : 5.333200
 dArray[4] is : 6.666500
 dArray[5] is : 7.999800
 dArray[6] is : 9.333100
 dArray[7] is : 10.666400
 dArray[8] is : 11.999700
 dArray[9] is : 13.333000

 Elements with their addresses :

 dArray[0] is : 1.333300 at address : 006FFBA4
 dArray[1] is : 2.666600 at address : 006FFBAC
 dArray[2] is : 3.999900 at address : 006FFBB4
 dArray[3] is : 5.333200 at address : 006FFBBC
 dArray[4] is : 6.666500 at address : 006FFBC4
 dArray[5] is : 7.999800 at address : 006FFBCC
 dArray[6] is : 9.333100 at address : 006FFBD4
 dArray[7] is : 10.666400 at address : 006FFBDC
 dArray[8] is : 11.999700 at address : 006FFBE4
 dArray[9] is : 13.333000 at address : 006FFBEC
 
 */



