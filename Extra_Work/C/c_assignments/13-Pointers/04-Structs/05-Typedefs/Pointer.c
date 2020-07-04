#include<stdio.h>

struct GRData
{
	int i;
	float f;
	double d;
};

int main()
{
	int griSize, grfSize, grdSize;
	int grDataSize;
	int grptrDataSize;
	
	typedef struct GRData* GRDataPtr;
	GRDataPtr grpData;
	
	grpData = (GRDataPtr)malloc(sizeof(struct GRData));
	if(grpData == NULL)
	{
		printf("\n Failed to allocate memory to struct");
		exit(0);
	}
	else
		printf("\n Successfully allocated memory to struct");
	
	// assignment
	grpData->i = 60;
	grpData->f = 90.7f;
	grpData->d = 50.5555;
	
	//display
	printf("\n i : %d", grpData->i);
	printf("\n f : %f", grpData->f);
	printf("\n d : %lf", grpData->d);
	
	//calculate sizes of data types
	griSize = sizeof(grpData->i);
	grfSize = sizeof(grpData->f);
	grdSize = sizeof(grpData->d);
	
	printf("\n\n Size of data members of struct GRData :");
	printf("\n Size of i : %d", griSize);
	printf("\n Size of f : %d", grfSize);
	printf("\n Size of d : %d", grdSize);
	
	grDataSize = sizeof(struct GRData);
	grptrDataSize = sizeof(GRDataPtr);
	
	printf("\n Size of struct GRData  : %d", grDataSize);
	printf("\n Size of pointer to struct GRData  : %d", grptrDataSize);
	
	if(grpData)
	{
		free(grpData);
		grpData = NULL;
		printf("\n Successfully freed memory allocated to struct");
	}
	return(0);
	
}

/* output *

 Successfully allocated memory to struct
 i : 60
 f : 90.699997
 d : 50.555500

 Size of data members of struct GRData :
 Size of i : 4
 Size of f : 4
 Size of d : 8
 Size of struct GRData  : 16
 Size of pointer to struct GRData  : 4
 Successfully freed memory allocated to struct
 
 */



































