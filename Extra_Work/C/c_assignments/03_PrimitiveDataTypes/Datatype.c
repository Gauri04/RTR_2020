#include<stdio.h>

int main(void)
{
	printf("\n\n");
	printf("\n Size of 'int' 	: %ld bytes\n", sizeof(int));
	printf("\n Size of 'unsigned int' : %ld bytes\n", sizeof(unsigned int));
	printf("\n Size of 'long' 	: %ld bytes\n", sizeof(long));
	printf("\n Size of 'long long' 	: %ld bytes\n", sizeof(long long));
	
	printf("\n Size of 'float' 	: %ld bytes\n", sizeof(float));
	printf("\n Size of 'double' 	: %ld bytes\n", sizeof(double));
	printf("\n Size of 'long double' 	: %ld bytes\n", sizeof(long double));
	printf("\n\n");
	return(0);
	
}

/** Output **



 Size of 'int' 	: 4 bytes

 Size of 'unsigned int' : 4 bytes

 Size of 'long' 	: 8 bytes

 Size of 'long long' 	: 8 bytes

 Size of 'float' 	: 4 bytes

 Size of 'double' 	: 8 bytes

 Size of 'long double' 	: 16 bytes


*/

