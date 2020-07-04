#include<stdio.h>
struct GRData
{
	int i;
	int *griptr;
	
	float f;
	float *grfptr;
	
	double d;
	double *grdptr;
};

int main()
{
	struct GRData *grptrData;
	
	grptrData = (struct GRData *)malloc(sizeof(struct GRData));
	
	if(grptrData == NULL)
	{
		printf("\n Failed to allocate memory to struct");
		exit(0);
	}
	else
		printf("\n Successfully allocated memory to struct");
	
	// assignment
	grptrData->i = 50;
	grptrData->griptr = &grptrData->i;
	
	grptrData->f = 440.44f;
	grptrData->grfptr = &grptrData->f;
	
	grptrData->d = 89.99999;
	grptrData->grdptr = &grptrData->d;
	
	printf("\n i : %d \t address of i : %p", grptrData->i, grptrData->griptr);
	printf("\n f : %f \t address of f : %p",grptrData->f, grptrData->grfptr);
	printf("\n d : %lf \t address of d : %p", grptrData->d, grptrData->grdptr);
	
	return(0);
	
}

/* output *

 Successfully allocated memory to struct
 i : 50          address of i : 00B72B70
 f : 440.440002          address of f : 00B72B78
 d : 89.999990   address of d : 00B72B80
 
 */




