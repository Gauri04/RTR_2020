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
	
	struct GRData *grData;
	
	grData = (struct GRData *)malloc(sizeof(struct GRData));
	
	if(grData == NULL)
	{
		printf("\n Failed to allocate memory to struct");
		exit(0);
	}
	else
		printf("\n Successfully allocated memory to struct");
	
	// Assignment
	grData->i = 30;
	grData->f = 5.55f;
	grData->d = 3.45555;
	
	// display
	printf("Struct data : \n");
	printf("\n i : %d", grData->i);
	printf("\n f : %f", grData->f);
	printf("\n d : %lf", grData->d);
	
	// calculate size
	griSize = sizeof(grData->i);
	grfSize = sizeof(grData->f);
	grdSize = sizeof(grData->d);
	
	printf("\n Size of data members of struct :");
	printf("\n Size of i : %d", griSize);
	printf("\n Size of f : %d", grfSize);
	printf("\n Size of d : %d", grdSize);
	
	grDataSize = sizeof(struct GRData);
	grptrDataSize = sizeof(struct GRData *);
	
	printf("\n Size of struct GRData  : %d", grDataSize);
	printf("\n Size of pointer to struct GRData  : %d", grptrDataSize);
	
	if(grData)
	{
		free(grData);
		grData = NULL;
	}
	return(0);
	
}

/* output *

 Successfully allocated memory to structStruct data :

 i : 30
 f : 5.550000
 d : 3.455550
 Size of data members of struct :
 Size of i : 4
 Size of f : 4
 Size of d : 8
 Size of struct GRData  : 16
 Size of pointer to struct GRData  : 4
 
 */























