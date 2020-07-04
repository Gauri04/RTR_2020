#include<stdio.h>
#include<stdlib.h>

#define INT_SIZE sizeof(int)
#define FLOAT_SIZE sizeof(float)
#define DOUBLE_SIZE sizeof(double)
#define CHAR_SIZE sizeof(char)

int main()
{
	int *griPtrArray = NULL;
	unsigned int griArrayLength = 0;
	
	float *grfPtrArray = NULL;
	unsigned int grfArrayLength = 0;
	
	double *grdPtrArray = NULL;
	unsigned int grdArrayLength = 0;
	
	char *grcPtrArray = NULL;
	unsigned int grcArrayLength = 0;
	
	int gri;
	
	
	/****** Integer array ***********/
	printf("\n Enter number of elements to be inserted in integer array :");
	scanf("%u", &griArrayLength);
	
	griPtrArray = (int *)malloc(INT_SIZE * griArrayLength);
	if(griPtrArray == NULL)
	{
		printf("\n Error : Failed to allocate memory to integer array");
		exit(0);
	}
	else
	{
		printf("\n Memory allocation to integer array succeded");
	}
	
	printf("\n Enter elements to be filled in array : \n");
	for(gri = 0; gri < griArrayLength; gri++)
	{
			scanf("%d", (griPtrArray + gri));
	}
	
	
	/***** Float  ******/
	printf("\n Enter number of elements to be inserted in float array :");
	scanf("%u", &grfArrayLength);
	
	grfPtrArray = (float *)malloc(FLOAT_SIZE * grfArrayLength);
	if(grfPtrArray == NULL)
	{
		printf("\n Error : Failed to allocate memory to float array");
		exit(0);
	}
	else
	{
		printf("\n Memory allocation to float array succeded");
	}
	
	printf("\n Enter elements to be filled in array : \n");
	for(gri = 0; gri < grfArrayLength; gri++)
	{
			scanf("%f", (grfPtrArray + gri));
	}
	
	
	/******* Double **************/
	printf("\n Enter number of elements to be inserted in a double array :");
	scanf("%u", &grdArrayLength);
	
	grdPtrArray = (double *)malloc(DOUBLE_SIZE * grdArrayLength);
	if(grdPtrArray == NULL)
	{
		printf("\n Error : Failed to allocate memory to double array");
		exit(0);
	}
	else
	{
		printf("\n Memory allocation to double array succeded");
	}
	
	printf("\n Enter elements to be filled in an array : \n");
	for(gri = 0; gri < grdArrayLength; gri++)
	{
			scanf("%lf", (grdPtrArray + gri));
	}
	
	/******* Char array ************/
	printf("\n Enter number of elements to be inserted in a char array :");
	scanf("%u", &grcArrayLength);
	
	grcPtrArray = (char *)malloc(CHAR_SIZE * grcArrayLength);
	if(grcPtrArray == NULL)
	{
		printf("\n Error : Failed to allocate memory to char array");
		exit(0);
	}
	else
	{
		printf("\n Memory allocation to char array succeded");
	}
	
	printf("\n Enter elements to be filled in a char array : \n");
	for(gri = 0; gri < grcArrayLength; gri++)
	{
			 *(grcPtrArray + gri) = getch();
			printf("%c", *(grcPtrArray + gri));
	}
	
	/*************************************** Display **********************************************/
	
	// Int
	printf("\n Array of %d integer elements : \n", griArrayLength);
	for(gri = 0; gri < griArrayLength; gri++)
	{
		printf("\n iArray[%d] is : %d \t\t at address : %p", gri, *(griPtrArray + gri), (griPtrArray + gri));
	}
	
	// Float
	printf("\n Array of %d float elements : \n", grfArrayLength);
	for(gri = 0; gri < grfArrayLength; gri++)
	{
		printf("\n fArray[%d] is : %f \t\t at address : %p", gri, *(grfPtrArray + gri), (grfPtrArray + gri));
	}
	
	// Double
	printf("\n Array of %d double elements : \n", grdArrayLength);
	for(gri = 0; gri < grdArrayLength; gri++)
	{
		printf("\n dArray[%d] is : %lf \t\t at address : %p", gri, *(grdPtrArray + gri), (grdPtrArray + gri));
	}
	
	// Char
	printf("\n Array of %d character elements : \n", grcArrayLength);
	for(gri = 0; gri < grcArrayLength; gri++)
	{
		printf("\n cArray[%d] is : %c \t\t at address : %p", gri, *(grcPtrArray + gri), (grcPtrArray + gri));
	}
	
	return(0);
}

/* output *
 Enter number of elements to be inserted in integer array :5

 Memory allocation to integer array succeded
 Enter elements to be filled in array :
10
20
30
40
50

 Enter number of elements to be inserted in float array :3

 Memory allocation to float array succeded
 Enter elements to be filled in array :
11.11
22.22
33.33

 Enter number of elements to be inserted in a double array :2

 Memory allocation to double array succeded
 Enter elements to be filled in an array :
333.333
666.666

 Enter number of elements to be inserted in a char array :5

 Memory allocation to char array succeded
 Enter elements to be filled in a char array :
gauri
 Array of 5 integer elements :

 iArray[0] is : 10               at address : 008D3220
 iArray[1] is : 20               at address : 008D3224
 iArray[2] is : 30               at address : 008D3228
 iArray[3] is : 40               at address : 008D322C
 iArray[4] is : 50               at address : 008D3230
 Array of 3 float elements :

 fArray[0] is : 11.110000                at address : 008D3240
 fArray[1] is : 22.219999                at address : 008D3244
 fArray[2] is : 33.330002                at address : 008D3248
 Array of 2 double elements :

 dArray[0] is : 333.333000               at address : 008D3258
 dArray[1] is : 666.666000               at address : 008D3260
 Array of 5 character elements :

 cArray[0] is : g                at address : 008D3270
 cArray[1] is : a                at address : 008D3271
 cArray[2] is : u                at address : 008D3272
 cArray[3] is : r                at address : 008D3273
 cArray[4] is : i                at address : 008D3274
 
 */



