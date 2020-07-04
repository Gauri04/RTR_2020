
#include<stdio.h>

int main()
{
	char grcArray[10];
	char *grcPtr = NULL;
	int gri;
	
	for(gri = 0; gri < 10; gri++)
		grcArray[gri] = (char)(gri + 65);

	// ptr
	grcPtr = grcArray;
	
	printf("\n Elements of  char array : \n");
	
	for(gri = 0; gri < 10; gri++)
		printf("\n cArray[%d] is : %c", gri, *(grcPtr + gri));
	
		printf("\n\n Elements of char array with their address : \n");
	
	for(gri = 0; gri < 10; gri++)
		printf("\n cArray[%d] is %c at address : %p", gri, *(grcPtr + gri), (grcPtr + gri));
	
	return(0);
	
}

/* output *

 Elements of  char array :

 cArray[0] is : A
 cArray[1] is : B
 cArray[2] is : C
 cArray[3] is : D
 cArray[4] is : E
 cArray[5] is : F
 cArray[6] is : G
 cArray[7] is : H
 cArray[8] is : I
 cArray[9] is : J

 Elements of char array with their address :

 cArray[0] is A at address : 0053FCCC
 cArray[1] is B at address : 0053FCCD
 cArray[2] is C at address : 0053FCCE
 cArray[3] is D at address : 0053FCCF
 cArray[4] is E at address : 0053FCD0
 cArray[5] is F at address : 0053FCD1
 cArray[6] is G at address : 0053FCD2
 cArray[7] is H at address : 0053FCD3
 cArray[8] is I at address : 0053FCD4
 cArray[9] is J at address : 0053FCD5
 
 */






