#include<stdio.h>

struct GREmployee
{
	char grName[20];
	int grAge;
	float grSalary;
	char grSex;
	char grMaritalStatus;
};

int main()
{
	printf("\n Size of DATA TYPES and POINTERS to those repsective data types are : ");
	
	printf("\n Size of (int) is : %d \t\t\t Size of (int *) is : %d \t\t Size of (int **) is : %d", 
		sizeof(int), sizeof(int *), sizeof(int **));
		
	printf("\n Size of (float) is : %d \t\t Size of (float *) is : %d \t\t Size of (float **) is : %d", 
		sizeof(float), sizeof(float *), sizeof(float **));
		
	printf("\n Size of (double) is : %d \t\t Size of (double *) is : %d \t\t Size of (double **) is : %d", 
		sizeof(double), sizeof(double *), sizeof(double **));
		
	printf("\n Size of (char) is : %d \t\t\t Size of (char *) is : %d \t\t Size of (char **) is : %d", 
		sizeof(char), sizeof(char *), sizeof(char **));
		
	printf("\n Size of (struct Employee) is : %d \t Size of (struct Employee *) is : %d " 
		"\t Size of (struct Employee **) is : %d", sizeof(struct GREmployee),
		sizeof(struct GREmployee *), sizeof(struct GREmployee **));
	
	return(0);
	
}

/* output *
 Size of DATA TYPES and POINTERS to those repsective data types are :
 Size of (int) is : 4                    Size of (int *) is : 4                  Size of (int **) is : 4
 Size of (float) is : 4                  Size of (float *) is : 4                Size of (float **) is : 4
 Size of (double) is : 8                 Size of (double *) is : 4               Size of (double **) is : 4
 Size of (char) is : 1                   Size of (char *) is : 4                 Size of (char **) is : 4
 Size of (struct Employee) is : 32       Size of (struct Employee *) is : 4      Size of (struct Employee **) is : 4
 
 */











