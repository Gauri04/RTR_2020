#include<stdio.h>

int main()
{
	int iArray[] = {3,5,1,7,9};
	int iSize;
	int iArraySize;
	int iArrayNumElements;
	
	float fArray[] = {1.2f, 5.5f, 0.23f, 23.44f, 0.99f};
	int fSize;
	int fArraySize, fArrayNumElements;
	
	char chArray[] = {'c', 'g', '*', '[', 'q', '/', 'y'};
	int chSize, chArraySize, chArrayNumElements;
	
	printf("\n iArray[0] : %d", iArray[0]);
	printf("\n iArray[1] : %d", iArray[1]);
	printf("\n iArray[2] : %d", iArray[2]);
	printf("\n iArray[3] : %d", iArray[3]);
	printf("\n iArray[4] : %d", iArray[4]);
	
	iSize = sizeof(int);
	iArraySize = sizeof(iArray);
	iArrayNumElements = iArraySize / iSize;
	
	printf("\n int data type size : %d", iSize);
	printf("\n No. of elements in fArray : %d", fArrayNumElements);
	printf("\n Size of chArray : (%d Elements * %d bytes) : %d bytes", iArrayNumElements, iSize, iArraySize);
	
	//float
	printf("\n fArray[0] : %f", fArray[0]);
	printf("\n fArray[1] : %f", fArray[1]);
	printf("\n fArray[2] : %f", fArray[2]);
	printf("\n fArray[3] : %f", fArray[3]);
	printf("\n fArray[4] : %f", fArray[4]);
	
	fSize = sizeof(float);
	fArraySize = sizeof(fArray);
	fArrayNumElements = fArraySize / fSize;
	printf("\n float data type size : %d", fSize);
	printf("\n No. of elements in fArray : %d", fArrayNumElements);
	printf("\n Size of chArray : (%d Elements * %d bytes) : %d bytes", fArrayNumElements, fSize, fArraySize);
	
	//char
	printf("\n chArray[0] : %c", chArray[0]);
	printf("\n chArray[1] : %c", chArray[1]);
	printf("\n chArray[2] : %c", chArray[2]);
	printf("\n chArray[3] : %c", chArray[3]);
	printf("\n chArray[4] : %c", chArray[4]);
	
	chSize = sizeof(char);
	chArraySize = sizeof(chArray);
	chArrayNumElements = chArraySize / chSize;
	
	printf("\n Char data type size : %d", chSize);
	printf("\n No. of elements in chArray : %d", chArrayNumElements);
	printf("\n Size of chArray : (%d Elements * %d bytes) : %d bytes", chArrayNumElements, chSize, chArraySize);
	
}

/* ouput *

  iArray[0] : 3
 iArray[1] : 5
 iArray[2] : 1
 iArray[3] : 7
 iArray[4] : 9
 int data type size : 4
 No. of elements in fArray : 0
 Size of chArray : (5 Elements * 4 bytes) : 20 bytes
 fArray[0] : 1.200000
 fArray[1] : 5.500000
 fArray[2] : 0.230000
 fArray[3] : 23.440001
 fArray[4] : 0.990000
 float data type size : 4
 No. of elements in fArray : 5
 Size of chArray : (5 Elements * 4 bytes) : 20 bytes
 chArray[0] : c
 chArray[1] : g
 chArray[2] : *
 chArray[3] : [
 chArray[4] : q
 Char data type size : 1
 No. of elements in chArray : 7
 Size of chArray : (7 Elements * 1 bytes) : 7 bytes
 */