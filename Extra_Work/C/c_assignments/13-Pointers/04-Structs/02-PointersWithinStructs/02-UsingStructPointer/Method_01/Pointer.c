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
	(*grptrData).i = 10;
	(*grptrData).griptr = &(*grptrData).i;
	
	(*grptrData).f = 56.6f;
	(*grptrData).grfptr = &(*grptrData).f;
	
	(*grptrData).d = 76.6666;
	(*grptrData).grdptr = &(*grptrData).d;
	
	printf("\n i : %d \t address of i : %p", *((*grptrData).griptr), (*grptrData).griptr);
	printf("\n f : %f \t address of f : %p",*((*grptrData).grfptr), (*grptrData).grfptr);
	printf("\n d : %lf \t address of d : %p", *((*grptrData).grdptr), (*grptrData).grdptr);
	
	return(0);
	
}

/* output *

 Successfully allocated memory to struct
 i : 10          address of i : 009AB818
 f : 56.599998   address of f : 009AB820
 d : 76.666600   address of d : 009AB828
 
 */



