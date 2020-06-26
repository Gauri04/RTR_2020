#include<stdio.h>
struct MyStruct
{
	int i;
	float f;
	double d;
	char c;
};

union MyUnion
{
	int i;
	float f;
	double d;
	char c;
};

int main()
{
	struct MyStruct myStruct;
	union MyUnion myUnion;
	
	// Initialization of struct members
	myStruct.i = 20;
	myStruct.f = 89.8f;
	myStruct .d = 43.4343f;
	myStruct.c = 'c';
	
	// struct data display
	printf("\n Members of MyStruct are : \n");
	printf("\n \t i = %d", myStruct.i);
	printf("\n \t f = %f", myStruct.f);
	printf("\n \t d = %lf", myStruct.d);
	printf("\n \t c = %c", myStruct.c);
	
	printf("\n Addresses of MyStruct are : \n");
	printf("\n \t Address of i = %p", &myStruct.i);
	printf("\n \t Address of f = %p", &myStruct.f);
	printf("\n \t Address of d = %p", &myStruct.d);
	printf("\n \t Address of c = %p", &myStruct.c);
	printf("\n \t MyStruct : myStruct : %p", &myStruct);
	
	// Initialization of union members
	printf("\n\n Members of myUnion are : \n");
	myUnion.i = 2;
	printf("\n \t i = %d", myUnion.i);
	
	myUnion.f = 87.6f;
	printf("\n \t f = %f", myUnion.f);
	
	myUnion.d = 332.444;
	printf("\n \t d = %lf", myUnion.d);
	
	myUnion.c = 'd';
	printf("\n \t c = %c", myUnion.c);
	
	printf("\n Addresses of members of myUnion are : \n");
	printf("\n \t Address of i = %p", &myUnion.i);
	printf("\n \t Address of f = %p", &myUnion.f);
	printf("\n \t Address of d = %p", &myUnion.d);
	printf("\n \t Address of c = %p", &myUnion.c);
	printf("\n \t MyUnion myUnion : %p", &myUnion);
	return(0);
}

/* output *

 Members of MyStruct are :

         i = 20
         f = 89.800003
         d = 43.434299
         c = c
 Addresses of MyStruct are :

         Address of i = 005AFC6C
         Address of f = 005AFC70
         Address of d = 005AFC74
         Address of c = 005AFC7C
         MyStruct : myStruct : 005AFC6C

 Members of myUnion are :

         i = 2
         f = 87.599998
         d = 332.444000
         c = d
 Addresses of members of myUnion are :

         Address of i = 005AFC64
         Address of f = 005AFC64
         Address of d = 005AFC64
         Address of c = 005AFC64
         MyUnion myUnion : 005AFC64
		 
*/




