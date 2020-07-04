#include<stdio.h>

int main()
{
	float grfArray[10];
	int gri;
	
	for(gri = 0; gri < 10; gri++)
		grfArray[gri] = (float) (gri + 1) * 1.5f;
	
	for(gri = 0; gri < 10; gri++)
		printf("\n fArray[%d] : %f", gri, grfArray[gri]);
	
	return(0);
}

/* ouput *

 fArray[0] : 1.500000
 fArray[1] : 3.000000
 fArray[2] : 4.500000
 fArray[3] : 6.000000
 fArray[4] : 7.500000
 fArray[5] : 9.000000
 fArray[6] : 10.500000
 fArray[7] : 12.000000
 fArray[8] : 13.500000
 fArray[9] : 15.000000
 
 */


