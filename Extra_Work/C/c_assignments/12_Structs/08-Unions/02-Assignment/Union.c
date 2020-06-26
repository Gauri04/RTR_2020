#include<stdio.h>

union MyUnion
{
	int i;
	float f;
	double d;
	char c;
};

int main()
{
	union MyUnion u1, u2;
	
	printf("\n Members of union u1 are : \n");
	//Initialization
	u1.i = 20;
	u1.f = 1.44f;
	u1.d = 98.999;
	u1.c = 'C';
	
	printf("\n \t i = %d", u1.i);
	printf("\n \t f = %f", u1.f);
	printf("\n \t d = %lf", u1.d);
	printf("\n \t c = %c", u1.c);
	
	printf("\n Addresses of members of union u1 are : \n");
	printf("\n \t Address of i = %p", &u1.i);
	printf("\n \t Address of f = %p", &u1.f);
	printf("\n \t Address of d = %p", &u1.d);
	printf("\n \t Address of c = %p", &u1.c);
	printf("\n \t MyUnion u1 : %p", &u1);
	
	printf("\n\n Members of union u2 are : \n");
	u2.i = 20;
	printf("\n \t i = %d", u2.i);
	
	u2.f = 56.5f;
	printf("\n \t f = %f", u2.f);
	
	u2.d = 3.4232;
	printf("\n \t d = %lf", u2.d);
	
	u2.c = 'h';
	printf("\n \t c = %c", u2.c);
	
	printf("\n Addresses of members of union u2 are : \n");
	printf("\n \t Address of i = %p", &u2.i);
	printf("\n \t Address of f = %p", &u2.f);
	printf("\n \t Address of d = %p", &u2.d);
	printf("\n \t Address of c = %p", &u2.c);
	printf("\n \t MyUnion u2 : %p", &u2);
	
	return(0);
	
}

/* output *

 Members of union u1 are :

         i = -1649267389
         f = -0.000000
         d = 98.999000
         c = C
 Addresses of members of union u1 are :

         Address of i = 00F0F89C
         Address of f = 00F0F89C
         Address of d = 00F0F89C
         Address of c = 00F0F89C
         MyUnion u1 : 00F0F89C

 Members of union u2 are :

         i = 20
         f = 56.500000
         d = 3.423200
         c = h
 Addresses of members of union u2 are :

         Address of i = 00F0F894
         Address of f = 00F0F894
         Address of d = 00F0F894
         Address of c = 00F0F894
         MyUnion u2 : 00F0F894
		 
*/






