#include<stdio.h>

struct Number
{
	int num;
	int numTable[10];
};

struct NumTables
{
	struct Number a;
	struct Number b;
	struct Number c;
};

int main()
{
	struct NumTables tables;
	int i;
	
	// Table of 2 
	tables.a.num = 2;
	
	for(i = 0; i < 10; i++)
	{
		tables.a.numTable[i] = tables.a.num * (i + 1); 
	}
	
	// Table of 3
	tables.b.num = 3;
	
	for(i = 0; i < 10; i++)
	{
		tables.b.numTable[i] = tables.b.num * (i + 1); 
	}
	
	// Table of 5
	tables.c.num = 5;
	
	for(i = 0; i < 10; i++)
	{
		tables.c.numTable[i] = tables.c.num * (i + 1); 
	}
	
	// display
	printf("\n Table for %d : \n", tables.a.num);
	for(i = 0; i < 10; i++)
	{
		printf("\n \t %d x %d : %d", tables.a.num, (i + 1), tables.a.numTable[i]);
	}
	
	
	printf("\n\n\n Table for %d : \n", tables.b.num);
	for(i = 0; i < 10; i++)
	{
		printf("\n \t %d x %d : %d", tables.b.num, (i + 1), tables.b.numTable[i]);
	}
	
	
	printf("\n\n\n Table for %d : \n", tables.c.num);
	for(i = 0; i < 10; i++)
	{
		printf("\n \t %d x %d : %d", tables.c.num, (i + 1), tables.c.numTable[i]);
	}
	
	return(0);
}

/* output *

 Table for 2 :

         2 x 1 : 2
         2 x 2 : 4
         2 x 3 : 6
         2 x 4 : 8
         2 x 5 : 10
         2 x 6 : 12
         2 x 7 : 14
         2 x 8 : 16
         2 x 9 : 18
         2 x 10 : 20


 Table for 3 :

         3 x 1 : 3
         3 x 2 : 6
         3 x 3 : 9
         3 x 4 : 12
         3 x 5 : 15
         3 x 6 : 18
         3 x 7 : 21
         3 x 8 : 24
         3 x 9 : 27
         3 x 10 : 30


 Table for 5 :

         5 x 1 : 5
         5 x 2 : 10
         5 x 3 : 15
         5 x 4 : 20
         5 x 5 : 25
         5 x 6 : 30
         5 x 7 : 35
         5 x 8 : 40
         5 x 9 : 45
         5 x 10 : 50
		 
*/


