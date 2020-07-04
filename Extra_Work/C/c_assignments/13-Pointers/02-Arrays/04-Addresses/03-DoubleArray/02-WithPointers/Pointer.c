#include<stdio.h>

int main()
{
	double grdArray[10];
	double* grdPtr = NULL;
	int gri;
	
	for(gri = 0; gri < 10; gri++)
		grdArray[gri] = (double) (gri + 1) * 1.3333f;
	
	
	// ptr
	grdPtr = grdArray;
	
	printf("\n Elements of array : \n");
	
	for(gri = 0; gri < 10; gri++)
		printf("\n dArray[%d] is : %lf", gri, *(grdPtr + gri));
	
	printf("\n\n Elements with their address : \n");
	
	for(gri = 0; gri < 10; gri++)
		printf("\n dArray[%d] is : %lf at address : %p", gri, *(grdPtr + gri), (grdPtr + gri));
		
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

 Elements with their address :

 dArray[0] is : 1.333300 at address : 00F3F860
 dArray[1] is : 2.666600 at address : 00F3F868
 dArray[2] is : 3.999900 at address : 00F3F870
 dArray[3] is : 5.333200 at address : 00F3F878
 dArray[4] is : 6.666500 at address : 00F3F880
 dArray[5] is : 7.999800 at address : 00F3F888
 dArray[6] is : 9.333100 at address : 00F3F890
 dArray[7] is : 10.666400 at address : 00F3F898
 dArray[8] is : 11.999700 at address : 00F3F8A0
 dArray[9] is : 13.333000 at address : 00F3F8A8
 
 */




