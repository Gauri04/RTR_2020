#include<stdio.h>

int main()
{
	int griArray[10];
	int gri;
	
	// table of 3
	for(gri = 0; gri < 10; gri++)
		griArray[gri] = (gri + 1) * 3;
	
	printf("\n Elements of array :");
	
	for(gri = 0; gri < 10; gri++)
		printf("\n iArray[%d] is %d", gri, griArray[gri]);
	
	printf("\n Elements of array and its address :");
	
	for(gri = 0; gri < 10; gri++)
		printf("\n iArray[%d] is %d \t address : %p", gri, griArray[gri], &griArray[gri]);
	
	return(0);
}

/* output *

 Elements of array :
 iArray[0] is 3
 iArray[1] is 6
 iArray[2] is 9
 iArray[3] is 12
 iArray[4] is 15
 iArray[5] is 18
 iArray[6] is 21
 iArray[7] is 24
 iArray[8] is 27
 iArray[9] is 30
 Elements of array and its address :
 iArray[0] is 3          address : 009AFC78
 iArray[1] is 6          address : 009AFC7C
 iArray[2] is 9          address : 009AFC80
 iArray[3] is 12         address : 009AFC84
 iArray[4] is 15         address : 009AFC88
 iArray[5] is 18         address : 009AFC8C
 iArray[6] is 21         address : 009AFC90
 iArray[7] is 24         address : 009AFC94
 iArray[8] is 27         address : 009AFC98
 iArray[9] is 30         address : 009AFC9C
 
 */
 
