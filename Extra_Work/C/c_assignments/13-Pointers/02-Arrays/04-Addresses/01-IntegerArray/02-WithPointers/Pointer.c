
#include<stdio.h>

int main()
{
	int griArray[10];
	int *griPtr = NULL;
	int gri;
	
	// table of 3
	for(gri = 0; gri < 10; gri++)
		griArray[gri] = (gri + 1) * 3;
	
	// Name of an array itsel is its base address
	griPtr = griArray;
	
	printf("\n Elements of array :");
	
	for(gri = 0; gri < 10; gri++)
		printf("\n iArray[%d] is %d", gri, *(griPtr + gri));
	
	printf("\n Elements of array and its address :");
	
	for(gri = 0; gri < 10; gri++)
		printf("\n iArray[%d] is %d \t address : %p", gri, *(griPtr + gri), (griPtr + gri));
	
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
 iArray[0] is 3          address : 00FFFBB0
 iArray[1] is 6          address : 00FFFBB4
 iArray[2] is 9          address : 00FFFBB8
 iArray[3] is 12         address : 00FFFBBC
 iArray[4] is 15         address : 00FFFBC0
 iArray[5] is 18         address : 00FFFBC4
 iArray[6] is 21         address : 00FFFBC8
 iArray[7] is 24         address : 00FFFBCC
 iArray[8] is 27         address : 00FFFBD0
 iArray[9] is 30         address : 00FFFBD4
 
 */
 



