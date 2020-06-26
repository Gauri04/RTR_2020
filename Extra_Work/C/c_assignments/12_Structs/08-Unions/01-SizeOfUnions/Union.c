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
	
	printf("\n Size of struct MyStruct is  : %lu", sizeof(myStruct));
	printf("\n Size of union MyUnion is  : %lu", sizeof(myUnion));
	return(0);
}

/* output *

 Size of struct MyStruct is  : 24
 Size of union MyUnion is  : 8
 
 */
 
 

