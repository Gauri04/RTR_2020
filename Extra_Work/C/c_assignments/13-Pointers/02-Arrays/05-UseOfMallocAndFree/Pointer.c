#include<stdio.h>
#include<stdlib.h> 	// For malloc() and free()

int main()
{
	int *griPtrArray = NULL;
	unsigned int griArrayLength = 0;
	int gri;
	
	printf("\n Enter the length of array in integers : \n");
	scanf("%d", &griArrayLength);
	
	// malloc
	
	griPtrArray = (int *)malloc(sizeof(int) * griArrayLength);
	
	if(griPtrArray == NULL)
	{
		printf("\n Erro :Failed to allocate memory");	
		exit(0);
	}
	else
	{
		printf("\n Memory allocation to integer array succeded.");
		printf("\n Memory allocated fro %p to %p", griPtrArray, (griPtrArray + (griArrayLength - 1)));
	}
		
	printf("\n\n Enter %d elements to be inserted in array : \n", griArrayLength);
	for(gri = 0; gri < griArrayLength; gri++)
		scanf("%d", (griPtrArray + gri));
	
	printf("\n\n Entered array : \n");
	for(gri = 0; gri < griArrayLength; gri++)
		printf("\n ptrArray[%d] is : %d \t\t at address &ptrArray[%d] : %p",
			gri, griPtrArray[gri], gri, &griPtrArray[gri]);
	
	
	printf("\n\n");
	for(gri = 0; gri < griArrayLength; gri++)
		printf("\n *(ptrArray + %d) is : %d \t\t at address (ptrArray + %d) : %p",
			gri, *(griPtrArray + gri), gri, (griPtrArray + gri));
	
	// free-ing the memory
	if(griPtrArray)
	{
		free(griPtrArray);
		griPtrArray = NULL;
		printf("\n Successfully freed memory allocated to ptrArray");
	}
	
	return(0);
}

/* output *
 Enter the length of array in integers :
5

 Memory allocation to integer array succeded.
 Memory allocated fro 00B03408 to 00B03418

 Enter 5 elements to be inserted in array :
10
20
30
40
50


 Entered array :

 ptrArray[0] is : 10             at address &ptrArray[0] : 00B03408
 ptrArray[1] is : 20             at address &ptrArray[1] : 00B0340C
 ptrArray[2] is : 30             at address &ptrArray[2] : 00B03410
 ptrArray[3] is : 40             at address &ptrArray[3] : 00B03414
 ptrArray[4] is : 50             at address &ptrArray[4] : 00B03418


 *(ptrArray + 0) is : 10                 at address (ptrArray + 0) : 00B03408
 *(ptrArray + 1) is : 20                 at address (ptrArray + 1) : 00B0340C
 *(ptrArray + 2) is : 30                 at address (ptrArray + 2) : 00B03410
 *(ptrArray + 3) is : 40                 at address (ptrArray + 3) : 00B03414
 *(ptrArray + 4) is : 50                 at address (ptrArray + 4) : 00B03418
 Successfully freed memory allocated to ptrArray
 
 */












