#include<stdio.h>

int main()
{
	char grcArray[10];
	int gri;
	
	for(gri = 0; gri < 10; gri++)
		grcArray[gri] = (char)(gri + 65);

	printf("\n Elements of  char array : \n");
	
	for(gri = 0; gri < 10; gri++)
		printf("\n cArray[%d] is : %c", gri, grcArray[gri]);
	
		printf("\n\n Elements of char array with their address : \n");
	
	for(gri = 0; gri < 10; gri++)
		printf("\n cArray[%d] is %c at address : %p", gri, grcArray[gri], &grcArray[gri]);
	
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

 cArray[0] is A at address : 0060FAAC
 cArray[1] is B at address : 0060FAAD
 cArray[2] is C at address : 0060FAAE
 cArray[3] is D at address : 0060FAAF
 cArray[4] is E at address : 0060FAB0
 cArray[5] is F at address : 0060FAB1
 cArray[6] is G at address : 0060FAB2
 cArray[7] is H at address : 0060FAB3
 cArray[8] is I at address : 0060FAB4
 cArray[9] is J at address : 0060FAB5
 
 */








