#include<stdio.h>

int main()
{
	int iArray[] = {3,5,1,7,9};
	int iSize;
	int iArraySize;
	int iArrayNumElements;
	int i;
	
	float fArray[] = {1.2f, 5.5f, 0.23f, 23.44f, 0.99f};
	int fSize;
	int fArraySize, fArrayNumElements;
	
	char chArray[] = {'a', 's', 't', 'r', 'o', 'm', 'e', 'd', 'i', 'c', 'o', 'm', 'p'};
	int chSize, chArraySize, chArrayNumElements;
	
	//int 
	iSize = sizeof(int);
	iArraySize = sizeof(iArray);
	iArrayNumElements = iArraySize / iSize;
	
	for(i = 0; i < iArrayNumElements; i++)
	{
		printf("\n iArray[%d] : %d", i, iArray[i]);
	}
	
	printf("\n int data type size : %d", iSize);
	printf("\n No. of elements in fArray : %d", fArrayNumElements);
	printf("\n Size of chArray : (%d Elements * %d bytes) : %d bytes", iArrayNumElements, iSize, iArraySize);
	
	//float
	fSize = sizeof(float);
	fArraySize = sizeof(fArray);
	fArrayNumElements = fArraySize / fSize;
	
	for(i = 0; i < fArrayNumElements; i++)
	{
		printf("\n fArray[%d] : %f", i, fArray[i]);
	}
	
	printf("\n float data type size : %d", fSize);
	printf("\n No. of elements in fArray : %d", fArrayNumElements);
	printf("\n Size of chArray : (%d Elements * %d bytes) : %d bytes", fArrayNumElements, fSize, fArraySize);
	
	
	//char
	chSize = sizeof(char);
	chArraySize = sizeof(chArray);
	chArrayNumElements = chArraySize / chSize;
	
	for(i = 0; i < chArrayNumElements; i++)
	{
		printf("\n chArray[%d] : %c", i, chArray[i]);
	}
	
	printf("\n Char data type size : %d", chSize);
	printf("\n No. of elements in chArray : %d", chArrayNumElements);
	printf("\n Size of chArray : (%d Elements * %d bytes) : %d bytes", chArrayNumElements, chSize, chArraySize);
	
	return(0);
	
}	

/* output *
 fArray[0] : 1.200000
 fArray[1] : 5.500000
 fArray[2] : 0.230000
 fArray[3] : 23.440001
 fArray[4] : 0.990000
 float data type size : 4
 No. of elements in fArray : 5
 Size of chArray : (5 Elements * 4 bytes) : 20 bytes
 chArray[0] : a
 chArray[1] : s
 chArray[2] : t
 chArray[3] : r
 chArray[4] : o
 chArray[5] : m
 chArray[6] : e
 chArray[7] : d
 chArray[8] : i
 chArray[9] : c
 chArray[10] : o
 chArray[11] : m
 chArray[12] : p
 Char data type size : 1
 No. of elements in chArray : 13
 Size of chArray : (13 Elements * 1 bytes) : 13 bytes
 */
 
 
 
