#include<stdio.h>

#define NAME_LENGTH 100
#define MARITAL_STATUS 10

struct Employee
{
	char name[NAME_LENGTH];
	int age;
	float salary;
	char sex;
	char maritalStatus[MARITAL_STATUS];
};

int main()
{
	struct Employee empRecord[5];
	
	char emp_rajesh[] = "Rajesh";
	char emp_sameer[] = "Sameer";
	char emp_reena[] = "Reena";
	char emp_seema[] = "Seema";
	char emp_meena[] = "Meena";
	int i;
	
	// Initialization (Hardcoded)
	strcpy(empRecord[0].name, emp_rajesh);
	empRecord[0].age = 22;
	empRecord[0].salary = 2000;
	empRecord[0].sex = 'M';
	strcpy(empRecord[0].maritalStatus, "Married");
	
	//2
	strcpy(empRecord[1].name, emp_sameer);
	empRecord[1].age = 32;
	empRecord[1].salary = 88000;
	empRecord[1].sex = 'M';
	strcpy(empRecord[1].maritalStatus, "Unmarried");
	
	//3
	strcpy(empRecord[2].name, emp_reena);
	empRecord[2].age = 42;
	empRecord[2].salary = 200000;
	empRecord[2].sex = 'F';
	strcpy(empRecord[2].maritalStatus, "Unmarried");
	
	//4
	strcpy(empRecord[3].name, emp_seema);
	empRecord[3].age = 29;
	empRecord[3].salary = 50000;
	empRecord[3].sex = 'F';
	strcpy(empRecord[3].maritalStatus, "Married");
	
	//5
	strcpy(empRecord[4].name, emp_meena);
	empRecord[4].age = 20;
	empRecord[4].salary = 90000;
	empRecord[4].sex = 'F';
	strcpy(empRecord[4].maritalStatus, "Unmarried");
	
	// Display
	for(i = 0; i < 5; i++)
	{
		printf("\n Employee :\n");
		printf("\n \t Name : %s", empRecord[i].name);
		printf("\n \t Age : %d", empRecord[i].age);
		printf("\n \t Salary : %f", empRecord[i].salary);
		printf("\n \t Sex : %c", empRecord[i].sex);
		printf("\n \t Marital Status : %s", empRecord[i].maritalStatus);
	}
	
	return(0);
}

/* output *
 Employee :

         Name : Rajesh
         Age : 22
         Salary : 2000.000000
         Sex : M
         Marital Status : Married
 Employee :

         Name : Sameer
         Age : 32
         Salary : 88000.000000
         Sex : M
         Marital Status : Unmarried
 Employee :

         Name : Reena
         Age : 42
         Salary : 200000.000000
         Sex : F
         Marital Status : Unmarried
 Employee :

         Name : Seema
         Age : 29
         Salary : 50000.000000
         Sex : F
         Marital Status : Married
 Employee :

         Name : Meena
         Age : 20
         Salary : 90000.000000
         Sex : F
         Marital Status : Unmarried

*/


