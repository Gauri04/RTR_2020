#include<stdio.h>

#define NAME_LENGTH 100
#define MARITAL_STATUS 10
#define NUM_EMPLOYEES 5

struct Employee
{
	char name[NAME_LENGTH];
	int age;
	float salary;
	char sex;
	char maritalStatus;
};

int main()
{
	void MyGetString(char[], int);
	
	struct Employee empRecord[NUM_EMPLOYEES];
	int i;
	
	for(i = 0; i < NUM_EMPLOYEES; i++)
	{
		printf("\n Enter Employee name : ");
		MyGetString(empRecord[i].name, NAME_LENGTH);
		
		printf("\n Enter employee age : ");
		scanf("%d", &empRecord[i].age);
		
		printf("\n Enter employee salary : ");
		scanf("%f", &empRecord[i].salary);
		
		printf("\n Enter employee sex : 'M' or 'm' / 'F' or 'f' \n");
		empRecord[i].sex = getch();
		printf("%c", empRecord[i].sex);
		empRecord[i].sex = toupper(empRecord[i].sex);
		
		printf("\n Enter employee marital status : Married : 'y' OR 'Y' / Unmarried : 'n' OR 'N' \n");
		empRecord[i].maritalStatus = getch();
		printf("%c", empRecord[i].maritalStatus);
		empRecord[i].maritalStatus = toupper(empRecord[i].maritalStatus);
	}
	
	//Display
	for(i = 0; i < NUM_EMPLOYEES; i++)
	{
		printf("\n \n Employee :");
		printf("\n \t Name : %s", empRecord[i].name);
		printf("\n \t Employee Age : %d", empRecord[i].age);
		printf("\n \t Employee Salary : %f", empRecord[i].salary);
		printf("\n \t Employee Sex : ");
		
		if(empRecord[i].sex == 'F' || empRecord[i].sex == 'f')
			printf("Female");
		else if(empRecord[i].sex == 'M' || empRecord[i].sex == 'm')
			printf("Male");
		else
			printf("Invalid information");
		
		printf("\n Employee Marital Status : ");
		if(empRecord[i].maritalStatus == 'Y' || empRecord[i].maritalStatus == 'y')
			printf("Married");
		else if(empRecord[i].maritalStatus == 'N' || empRecord[i].maritalStatus == 'n')
			printf("Unmarried");
		else
			printf("Invalid information");
	}
	
	return(0);
	
}

void MyGetString(char str[], int strLength)
{
	int i;
	char ch = '\0';
	
	i = 0;
	do
	{
		ch = getch();
		str[i] = ch;
		printf("%c", str[i]);
		i++;
	}while((ch != '\r') && (i < strLength));
	
	if(i == strLength)
		str[i - 1] = '\0';
	else
		str[i] = '\0';
	
}

/* ouput *

 Enter Employee name : ramesh
 Enter employee age : 20

 Enter employee salary : 10000

 Enter employee sex : 'M' or 'm' / 'F' or 'f'
M
 Enter employee marital status : Married : 'y' OR 'Y' / Unmarried : 'n' OR 'N'
y
 Enter Employee name : suresh
 Enter employee age : 40

 Enter employee salary : 5000

 Enter employee sex : 'M' or 'm' / 'F' or 'f'
m
 Enter employee marital status : Married : 'y' OR 'Y' / Unmarried : 'n' OR 'N'
y
 Enter Employee name : nilesh
 Enter employee age : 20

 Enter employee salary : 10000

 Enter employee sex : 'M' or 'm' / 'F' or 'f'
m
 Enter employee marital status : Married : 'y' OR 'Y' / Unmarried : 'n' OR 'N'
N
 Enter Employee name : neeta
 Enter employee age : 22

 Enter employee salary : 20222

 Enter employee sex : 'M' or 'm' / 'F' or 'f'
F
 Enter employee marital status : Married : 'y' OR 'Y' / Unmarried : 'n' OR 'N'
n
 Enter Employee name : seetαM
 Enter employee age : 45

 Enter employee salary : 45000

 Enter employee sex : 'M' or 'm' / 'F' or 'f'
f
 Enter employee marital status : Married : 'y' OR 'Y' / Unmarried : 'n' OR 'N'
y

 Employee :
         Name : ramesh
         Employee Age : 20
         Employee Salary : 10000.000000
         Employee Sex : Male
 Employee Marital Status : Married

 Employee :
         Name : suresh
         Employee Age : 40
         Employee Salary : 5000.000000
         Employee Sex : Male
 Employee Marital Status : Married

 Employee :
         Name : nilesh
         Employee Age : 20
         Employee Salary : 10000.000000
         Employee Sex : Male
 Employee Marital Status : Unmarried

 Employee :
         Name : neeta
         Employee Age : 22
         Employee Salary : 20222.000000
         Employee Sex : Female
 Employee Marital Status : Unmarried

 Employee :
         Name : seetαM
         Employee Age : 45
         Employee Salary : 45000.000000
         Employee Sex : Female
 Employee Marital Status : Married
 
 */



