#include<stdio.h>

int main()
{
	int griArray[] = {10,20,30,40,50,60,70,80,90, 100};
	int *griPtr = NULL;
	
	printf("\n Integer Array elements and addresses of its elements are : ");
	
	printf("\n iArray[0] value : %d \t address : %p", griArray[0], &griArray[0]);
	printf("\n iArray[1] value : %d \t address : %p", griArray[1], &griArray[1]);
	printf("\n iArray[2] value : %d \t address : %p", griArray[2], &griArray[2]);
	printf("\n iArray[3] value : %d \t address : %p", griArray[3], &griArray[3]);
	printf("\n iArray[4] value : %d \t address : %p", griArray[4], &griArray[4]);
	printf("\n iArray[5] value : %d \t address : %p", griArray[5], &griArray[5]);
	printf("\n iArray[6] value : %d \t address : %p", griArray[6], &griArray[6]);
	printf("\n iArray[7] value : %d \t address : %p", griArray[7], &griArray[7]);
	printf("\n iArray[8] value : %d \t address : %p", griArray[8], &griArray[8]);
	printf("\n iArray[9] value : %d \t address : %p", griArray[9], &griArray[9]);
	
	
	griPtr = griArray;
	
	// accessing value of array using *(griPtr + x) and address using (griPtr + x)
	printf("\n\n Using pointer to display values using formula,");
	printf("\n Value = *(ptr + x) \t and  address = (ptr + x)");
	
	printf("\n value *(ptr + 0) : %d \t address (ptr + 0) : %p", *(griPtr + 0), (griPtr + 0));
	printf("\n value *(ptr + 1) : %d \t address (ptr + 1) : %p", *(griPtr + 1), (griPtr + 1));
	printf("\n value *(ptr + 2) : %d \t address (ptr + 2) : %p", *(griPtr + 2), (griPtr + 2));
	printf("\n value *(ptr + 3) : %d \t address (ptr + 3) : %p", *(griPtr + 3), (griPtr + 3));
	printf("\n value *(ptr + 4) : %d \t address (ptr + 4) : %p", *(griPtr + 4), (griPtr + 4));
	printf("\n value *(ptr + 5) : %d \t address (ptr + 5) : %p", *(griPtr + 5), (griPtr + 5));
	printf("\n value *(ptr + 6) : %d \t address (ptr + 6) : %p", *(griPtr + 6), (griPtr + 6));
	printf("\n value *(ptr + 7) : %d \t address (ptr + 7) : %p", *(griPtr + 7), (griPtr + 7));
	printf("\n value *(ptr + 8) : %d \t address (ptr + 8) : %p", *(griPtr + 8), (griPtr + 8));
	printf("\n value *(ptr + 9) : %d \t address (ptr + 9) : %p", *(griPtr + 9), (griPtr + 9));
	
	return(0);
}

/* output *

 Integer Array elements and addresses of its elements are :
 iArray[0] value : 10    address : 00D3F934
 iArray[1] value : 20    address : 00D3F938
 iArray[2] value : 30    address : 00D3F93C
 iArray[3] value : 40    address : 00D3F940
 iArray[4] value : 50    address : 00D3F944
 iArray[5] value : 60    address : 00D3F948
 iArray[6] value : 70    address : 00D3F94C
 iArray[7] value : 80    address : 00D3F950
 iArray[8] value : 90    address : 00D3F954
 iArray[9] value : 100   address : 00D3F958

 Using pointer to display values using formula,
 Value = *(ptr + x)      and  address = (ptr + x)
 value *(ptr + 0) : 10   address (ptr + 0) : 00D3F934
 value *(ptr + 1) : 20   address (ptr + 1) : 00D3F938
 value *(ptr + 2) : 30   address (ptr + 2) : 00D3F93C
 value *(ptr + 3) : 40   address (ptr + 3) : 00D3F940
 value *(ptr + 4) : 50   address (ptr + 4) : 00D3F944
 value *(ptr + 5) : 60   address (ptr + 5) : 00D3F948
 value *(ptr + 6) : 70   address (ptr + 6) : 00D3F94C
 value *(ptr + 7) : 80   address (ptr + 7) : 00D3F950
 value *(ptr + 8) : 90   address (ptr + 8) : 00D3F954
 value *(ptr + 9) : 100          address (ptr + 9) : 00D3F958
 
 */








