#include<stdio.h>

struct grEmployee
{
	char grName;
	int grAge;
	float grSalary;
	char grMaritalStatus;
};

int main()
{
	printf("\n Size of data type :  \t\t\t Size of respective pointer variable :");
	printf("\n \n int :  %d  \t\t\t\t pointer to int (int*) : %d", sizeof(int), sizeof(int*));
	printf("\n float :  %d  \t\t\t\t pointer to float (float*) : %d", sizeof(float), sizeof(float*));
	printf("\n double :  %d  \t\t\t\t pointer to double (double*) : %d", sizeof(double), sizeof(double*));
	printf("\n char :  %d  \t\t\t\t pointer to char (char*) : %d", sizeof(char), sizeof(char*));
	printf("\n struct Employee :  %d  \t\t pointer to struct Employee (struct Employee*) : %d",
		sizeof(struct grEmployee), sizeof(struct grEmployee*));
	
	return(0);
}

/* output *
 Size of data type :                     Size of respective pointer variable :

 int :  4                                pointer to int (int*) : 4
 float :  4                              pointer to float (float*) : 4
 double :  8                             pointer to double (double*) : 4
 char :  1                               pointer to char (char*) : 4
 struct Employee :  16                   pointer to struct Employee (struct Employee*) : 4
 
 */
 


