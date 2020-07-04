#include<stdio.h>
#include<ctype.h>

#define NAME_LENGTH 100
#define MARITAL_STATUS 10

struct GREmployee
{
	char name[NAME_LENGTH];
	int age;
	char sex;
	float salary;
	char maritalStrtus;
};

int main()
{
	void MyGetString(char[], int);
	
	struct GREmployee *grpEmployee = NULL;
	int grNumEmployees, i;
	
	printf("\n How many employee records you want to enter : ");
	scanf("%d", &grNumEmployees);
	
	grpEmployee = (struct GREmployee *)malloc(grNumEmployees * sizeof(struct GREmployee));
	if(grpEmployee == NULL)
	{
		printf("\n Failed to allocate memory to struct");
		exit(0);
	}
	else
		printf("\n Successfully allocated memory of %d employees to struct", grNumEmployees);
	
	
	printf("\n Enter record : \n");
	for(i = 0; i < grNumEmployees; i++)
	{
		printf("\n Enter Employee name : ");
		MyGetString(grpEmployee[i].name, NAME_LENGTH);
		
		printf("\n Enter employee age : ");
		scanf("%d", &grpEmployee[i]. age);
		
		printf("\n Enter employee sex : F/f for female, M/m for male : ");
		grpEmployee[i].sex = getch();
		printf("%c", grpEmployee[i].sex);
		
		printf("\n Enter employee salary : ");
		scanf("%f", &grpEmployee[i].salary);
		
		printf("\n Is the employee married ? : Y/y for yes, N/n for no : ");
		grpEmployee[i].maritalStrtus = getch();
		printf("%c", grpEmployee[i].maritalStrtus);
		grpEmployee[i].maritalStrtus = toupper(grpEmployee[i].maritalStrtus);
		
	}
	
	// Display
	for(i = 0; i < grNumEmployees; i++)
	{
		printf("\n ***************** Employee %d ************** \n", i);
		printf("\n Name : \t %s", grpEmployee[i].name);
		printf("\n Age : \t %d", grpEmployee[i].age);
		
		
		if(grpEmployee[i].sex == 'f' || grpEmployee[i].sex == 'F')
			printf("\n Sex : Female");
		
		else if(grpEmployee[i].sex == 'm' || grpEmployee[i].sex == 'M')
			printf("\n Sex : Male");
		
		else
			printf("\n Sex : Invalid data entered");
		
		printf("\n Salary : \t %f", grpEmployee[i].salary);
		
		if(grpEmployee[i].maritalStrtus == 'y' || grpEmployee[i].maritalStrtus == 'Y')
			printf("\n Marital Status : Married");
		
		else if(grpEmployee[i].maritalStrtus == 'n' || grpEmployee[i].maritalStrtus == 'N')
			printf("\n Marital Status : Married");
		
		else
			printf("\n Marital Status : Invalid data entered");
			
	}
	
	
	if(grpEmployee)
	{
		free(grpEmployee);
		grpEmployee = NULL;
		printf("\n Successfully freed memory fro employee record");
	}
	
}

void MyGetString(char *str, int strSize)
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
	}while((ch != '\r') && i < strSize);
	
	if(i == strSize)
		str[i - 1] = '\0';
	else
		str[i] = '\0';
}

/* output *
 How many employee records you want to enter : 2

 Successfully allocated memory of 2 employees to struct
 Enter record :

 Enter Employee name : seema
 Enter employee age : 20

 Enter employee sex : F/f for female, M/m for male : f
 Enter employee salary : 2000

 Is the employee married ? : Y/y for yes, N/n for no : n
 Enter Employee name : raj
 Enter employee age : 24

 Enter employee sex : F/f for female, M/m for male : M
 Enter employee salary : 2000

 Is the employee married ? : Y/y for yes, N/n for no : y
 ***************** Employee 0 **************

 Name :          seema
 Age :   20
 Sex : Female
 Salary :        2000.000000
 Marital Status : Married
 ***************** Employee 1 **************

 Name :          raj
 Age :   24
 Sex : Male
 Salary :        2000.000000
 Marital Status : Married
 Successfully freed memory fro employee record
 
 */

























