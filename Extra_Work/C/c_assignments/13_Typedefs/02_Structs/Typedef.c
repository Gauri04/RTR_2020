#include<stdio.h>
#define MAX_NAME_LENGTH 100

struct Employee
{
	char name[MAX_NAME_LENGTH];
	unsigned int age;
	char gender;
	double salary;
};

struct GRData
{
	int i;
	float f;
	double d;
	char c;
};

int main()
{
	typedef struct Employee MY_EMPLOYEE;
	typedef struct GRData MY_DATA;
	
	struct Employee emp = {"Funny", 25, 'M', 1000.22};	// initialization
	MY_EMPLOYEE gr_emp_typedef = {"Bunny", 30, 'F', 2312.211};
	
	struct GRData gd = {30, 21.5, 43.434232, '*'};
	
	MY_DATA gr_md_typedef;
	
	//piecemeal initialization
	gr_md_typedef.i = 32;
	gr_md_typedef.f = 434.2;
	gr_md_typedef.d = 54.211211;
	gr_md_typedef.c = 'v';
	
	
	printf("\n struct employee : ");
	printf("\n emp name : %s", emp.name);
	printf("\n emp age : %d", emp.age);
	printf("\n emp gender %c : ", emp.gender);
	printf("\n emp salary : %lf", emp.salary);
	
	printf("\n\n type MY_EMPLOYEE : ");
	printf("\n MY_EMPLOYEE name : %s", gr_emp_typedef.name);
	printf("\n MY_EMPLOYEE age : %d", gr_emp_typedef.age);
	printf("\n MY_EMPLOYEE gender %c : ", gr_emp_typedef.gender);
	printf("\n MY_EMPLOYEE salary : %lf", gr_emp_typedef.salary);
	
	printf("\n\n\n struct GRDATA :");
	printf("\n GRDATA int : %d", gd.i);
	printf("\n GRDATA float : %f ", gd.f);
	printf("\n GRDATA double : %lf", gd.d);
	printf("\n GRDATA char : %c", gd.c);
	
	printf("\n\n type MY_DATA");
	printf("\n MY_DATA int : %d", gr_md_typedef.i);
	printf("\n MY_DATA float : %f ", gr_md_typedef.f);
	printf("\n MY_DATA double : %lf", gr_md_typedef.d);
	printf("\n MY_DATA char : %c", gr_md_typedef.c);
	
	return(0);
	
}

/* output *
struct employee :
 emp name : Funny
 emp age : 25
 emp gender M :
 emp salary : 1000.220000

 type MY_EMPLOYEE :
 MY_EMPLOYEE name : Bunny
 MY_EMPLOYEE age : 30
 MY_EMPLOYEE gender F :
 MY_EMPLOYEE salary : 2312.211000


 struct GRDATA :
 GRDATA int : 30
 GRDATA float : 21.500000
 GRDATA double : 43.434232
 GRDATA char : *

 type MY_DATA
 MY_DATA int : 32
 MY_DATA float : 434.200012
 MY_DATA double : 54.211211
 MY_DATA char : v
 
 */
 





