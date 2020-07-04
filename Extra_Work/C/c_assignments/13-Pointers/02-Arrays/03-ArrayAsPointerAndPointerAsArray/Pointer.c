#include<stdio.h>

int main()
{
	int griArray[] = {10,20,30,40,50,60,70,80,90, 100};
	int *griPtr = NULL;
	
	printf("\n Displaying xth element of array using *(iArray + x) and its address (iArray + x)");
	
	printf("\n value *(iArray + 0) : %d \t address (iArray + 0) : %p", *(griArray + 0), (griArray + 0));
	printf("\n value *(iArray + 1) : %d \t address (iArray + 1) : %p", *(griArray + 1), (griArray + 1));
	printf("\n value *(iArray + 2) : %d \t address (iArray + 2) : %p", *(griArray + 2), (griArray + 2));
	printf("\n value *(iArray + 3) : %d \t address (iArray + 3) : %p", *(griArray + 3), (griArray + 3));
	printf("\n value *(iArray + 4) : %d \t address (iArray + 4) : %p", *(griArray + 4), (griArray + 4));
	printf("\n value *(iArray + 5) : %d \t address (iArray + 5) : %p", *(griArray + 5), (griArray + 5));
	printf("\n value *(iArray + 6) : %d \t address (iArray + 6) : %p", *(griArray + 6), (griArray + 6));
	printf("\n value *(iArray + 7) : %d \t address (iArray + 7) : %p", *(griArray + 7), (griArray + 7));
	printf("\n value *(iArray + 8) : %d \t address (iArray + 8) : %p", *(griArray + 8), (griArray + 8));
	printf("\n value *(iArray + 9) : %d \t address (iArray + 9) : %p", *(griArray + 9), (griArray + 9));
	
	// using pointer to access value using formula griptr[x] and it address using formula &griptr[x] 
	griPtr = griArray;
	printf("\n\n *** Pointer ***");
	printf("\n\n Using pointer to display values using formula,");
	printf("\n Value = iPtr[x] \t and  address = &iPtr[x]");
	
	printf("\n iPtr[0] value : %d \t address &iPtr[0] : %p", griPtr[0], &griPtr[0]);
	printf("\n iPtr[1] value : %d \t address &iPtr[1] : %p", griPtr[1], &griPtr[1]);
	printf("\n iPtr[2] value : %d \t address &iPtr[2] : %p", griPtr[2], &griPtr[2]);
	printf("\n iPtr[3] value : %d \t address &iPtr[3] : %p", griPtr[3], &griPtr[3]);
	printf("\n iPtr[4] value : %d \t address &iPtr[4] : %p", griPtr[4], &griPtr[4]);
	printf("\n iPtr[5] value : %d \t address &iPtr[5] : %p", griPtr[5], &griPtr[5]);
	printf("\n iPtr[6] value : %d \t address &iPtr[6] : %p", griPtr[6], &griPtr[6]);
	printf("\n iPtr[7] value : %d \t address &iPtr[7] : %p", griPtr[7], &griPtr[7]);
	printf("\n iPtr[8] value : %d \t address &iPtr[8] : %p", griPtr[8], &griPtr[8]);
	printf("\n iPtr[9] value : %d \t address &iPtr[9] : %p", griPtr[9], &griPtr[9]);
	
	return(0);	
	
}

/* output *

 Displaying xth element of array using *(iArray + x) and its address (iArray + x)
 value *(iArray + 0) : 10        address (iArray + 0) : 0062FAD0
 value *(iArray + 1) : 20        address (iArray + 1) : 0062FAD4
 value *(iArray + 2) : 30        address (iArray + 2) : 0062FAD8
 value *(iArray + 3) : 40        address (iArray + 3) : 0062FADC
 value *(iArray + 4) : 50        address (iArray + 4) : 0062FAE0
 value *(iArray + 5) : 60        address (iArray + 5) : 0062FAE4
 value *(iArray + 6) : 70        address (iArray + 6) : 0062FAE8
 value *(iArray + 7) : 80        address (iArray + 7) : 0062FAEC
 value *(iArray + 8) : 90        address (iArray + 8) : 0062FAF0
 value *(iArray + 9) : 100       address (iArray + 9) : 0062FAF4

 *** Pointer ***

 Using pointer to display values using formula,
 Value = iPtr[x]         and  address = &iPtr[x]
 iPtr[0] value : 10      address &iPtr[0] : 0062FAD0
 iPtr[1] value : 20      address &iPtr[1] : 0062FAD4
 iPtr[2] value : 30      address &iPtr[2] : 0062FAD8
 iPtr[3] value : 40      address &iPtr[3] : 0062FADC
 iPtr[4] value : 50      address &iPtr[4] : 0062FAE0
 iPtr[5] value : 60      address &iPtr[5] : 0062FAE4
 iPtr[6] value : 70      address &iPtr[6] : 0062FAE8
 iPtr[7] value : 80      address &iPtr[7] : 0062FAEC
 iPtr[8] value : 90      address &iPtr[8] : 0062FAF0
 iPtr[9] value : 100     address &iPtr[9] : 0062FAF4
 
*/









