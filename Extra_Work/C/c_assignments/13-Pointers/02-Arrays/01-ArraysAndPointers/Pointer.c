#include<stdio.h>

int main()
{
	int griArray[] = {10,20,30,40,50,60,70,80,90, 100};
	float grfArray[] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
	double grdArray[] = {1222.22, 234.455, 789.0001};
	char grcArray[] = {'a', 's','t','r','o','m','e','d','i','c','o','m','p', '\0'};
	
	printf("\n Array elements and addresses of its elements are : ");
	
	printf("\n **** iArray ****");
	printf("\n iArray[0] value : %d \t address : %p", *(griArray + 0), (griArray + 0));
	printf("\n iArray[1] value : %d \t address : %p", *(griArray + 1), (griArray + 1));
	printf("\n iArray[2] value : %d \t address : %p", *(griArray + 2), (griArray + 2));
	printf("\n iArray[3] value : %d \t address : %p", *(griArray + 3), (griArray + 3));
	printf("\n iArray[4] value : %d \t address : %p", *(griArray + 4), (griArray + 4));
	printf("\n iArray[5] value : %d \t address : %p", *(griArray + 5), (griArray + 5));
	printf("\n iArray[6] value : %d \t address : %p", *(griArray + 6), (griArray + 6));
	printf("\n iArray[7] value : %d \t address : %p", *(griArray + 7), (griArray + 7));
	printf("\n iArray[8] value : %d \t address : %p", *(griArray + 8), (griArray + 8));
	printf("\n iArray[9] value : %d \t address : %p", *(griArray + 9), (griArray + 9));
	
	printf("\n\n **** fArray ****");
	printf("\n fArray[0] value : %f \t address : %p", *(grfArray + 0), (grfArray + 0));
	printf("\n fArray[1] value : %f \t address : %p", *(grfArray + 1), (grfArray + 1));
	printf("\n fArray[2] value : %f \t address : %p", *(grfArray + 2), (grfArray + 2));
	printf("\n fArray[3] value : %f \t address : %p", *(grfArray + 3), (grfArray + 3));
	printf("\n fArray[4] value : %f \t address : %p", *(grfArray + 4), (grfArray + 4));
	
	printf("\n\n **** dArray ****");
	printf("\n dArray[0] value : %f \t address : %p", *(grdArray + 0), (grdArray + 0));
	printf("\n dArray[1] value : %f \t address : %p", *(grdArray + 1), (grdArray + 1));
	printf("\n dArray[2] value : %f \t address : %p", *(grdArray + 2), (grdArray + 2));
	
	printf("\n **** cArray ****");
	printf("\n cArray[0] value : %d \t address : %p", *(grcArray + 0), (grcArray + 0));
	printf("\n cArray[1] value : %d \t address : %p", *(grcArray + 1), (grcArray + 1));
	printf("\n cArray[2] value : %d \t address : %p", *(grcArray + 2), (grcArray + 2));
	printf("\n cArray[3] value : %d \t address : %p", *(grcArray + 3), (grcArray + 3));
	printf("\n cArray[4] value : %d \t address : %p", *(grcArray + 4), (grcArray + 4));
	printf("\n cArray[5] value : %d \t address : %p", *(grcArray + 5), (grcArray + 5));
	printf("\n cArray[6] value : %d \t address : %p", *(grcArray + 6), (grcArray + 6));
	printf("\n cArray[7] value : %d \t address : %p", *(grcArray + 7), (grcArray + 7));
	printf("\n cArray[8] value : %d \t address : %p", *(grcArray + 8), (grcArray + 8));
	printf("\n cArray[9] value : %d \t address : %p", *(grcArray + 9), (grcArray + 9));
	printf("\n cArray[10] value : %d \t address : %p", *(grcArray + 10), (grcArray + 10));
	printf("\n cArray[11] value : %d \t address : %p", *(grcArray + 11), (grcArray + 11));
	printf("\n cArray[12] value : %d \t address : %p", *(grcArray + 12), (grcArray + 12));

	return(0);
}

/* output *
 **** iArray ****
 iArray[0] value : 10    address : 001CF9F0
 iArray[1] value : 20    address : 001CF9F4
 iArray[2] value : 30    address : 001CF9F8
 iArray[3] value : 40    address : 001CF9FC
 iArray[4] value : 50    address : 001CFA00
 iArray[5] value : 60    address : 001CFA04
 iArray[6] value : 70    address : 001CFA08
 iArray[7] value : 80    address : 001CFA0C
 iArray[8] value : 90    address : 001CFA10
 iArray[9] value : 100   address : 001CFA14

 **** fArray ****
 fArray[0] value : 0.100000      address : 001CFA18
 fArray[1] value : 0.200000      address : 001CFA1C
 fArray[2] value : 0.300000      address : 001CFA20
 fArray[3] value : 0.400000      address : 001CFA24
 fArray[4] value : 0.500000      address : 001CFA28

 **** dArray ****
 dArray[0] value : 1222.220000   address : 001CF9D8
 dArray[1] value : 234.455000    address : 001CF9E0
 dArray[2] value : 789.000100    address : 001CF9E8
 **** cArray ****
 cArray[0] value : 97    address : 001CFA2C
 cArray[1] value : 115   address : 001CFA2D
 cArray[2] value : 116   address : 001CFA2E
 cArray[3] value : 114   address : 001CFA2F
 cArray[4] value : 111   address : 001CFA30
 cArray[5] value : 109   address : 001CFA31
 cArray[6] value : 101   address : 001CFA32
 cArray[7] value : 100   address : 001CFA33
 cArray[8] value : 105   address : 001CFA34
 cArray[9] value : 99    address : 001CFA35
 cArray[10] value : 111          address : 001CFA36
 cArray[11] value : 109          address : 001CFA37
 cArray[12] value : 112          address : 001CFA38
 
 */
 






