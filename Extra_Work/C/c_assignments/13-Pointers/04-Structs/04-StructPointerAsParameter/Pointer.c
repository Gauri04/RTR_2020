#include<stdio.h>

struct GRData
{
	int i;
	float f;
	double d;
};

int main()
{
	void ChangeValues(struct GRData *);
	struct GRData *grpData = NULL;
	
	grpData = (struct GRData *)malloc(sizeof(struct GRData));
	
	if(grpData == NULL)
	{
		printf("\n Failed to allocate memory to struct");
		exit(0);
	}
	else
		printf("\n Successfully allocated memory to struct");
	
	// assignment
	grpData->i = 40;
	grpData->f = 4.05f;
	grpData->d = 66.6666;
	
	printf("\n\n Before calling ChangeValues() : ");
	printf("\n i : %d", grpData->i);
	printf("\n f : %f", grpData->f);
	printf("\n d : %lf", grpData->d);
	
	ChangeValues(grpData);
	
	//display
	printf("\n]n After calling ChangeValues() : ");
	printf("\n i : %d", grpData->i);
	printf("\n f : %f", grpData->f);
	printf("\n d : %lf", grpData->d);
	
	if(grpData)
	{
		free(grpData);
		grpData = NULL;
		printf("\n Successfuly free memory aloocated to struct");
	}
	
	return(0);
}

void ChangeValues(struct GRData *data)
{
	(*data).i = 30;
	(*data).f = 33.33f;
	(*data).d = 76.1234;	
}

/* output *
 Successfully allocated memory to struct

 Before calling ChangeValues() :
 i : 40
 f : 4.050000
 d : 66.666600
]n After calling ChangeValues() :
 i : 30
 f : 33.330002
 d : 76.123400
 Successfuly free memory aloocated to struct
 
 */












































