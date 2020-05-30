#include<stdio.h>
int main()
{
	void PrintBinaryFormOfNumber(unsigned int);
	
	unsigned int a, b, result;
	
	printf("\n Enter two integers : ");
	scanf("%u %u", &a, &b);
	
	result = a ^ b;
	printf("\n Bitwise XOR of the two decimal numbers %d, %d gives result : %d", a,b,result);
	
	PrintBinaryFormOfNumber(a);
	PrintBinaryFormOfNumber(b);
	PrintBinaryFormOfNumber(result);
	
	return(0);
}

void PrintBinaryFormOfNumber(unsigned int no)
{
	unsigned int quotient, remainder, num, binary_array[8];
	int i;
	
	for(i = 0; i < 8; i++)
		binary_array[i] = 0;
	
	printf("\n Binary form of decimal integer %d is \t=\t", no);
	num = no;
	i = 7;
	while(num != 0)
	{
		quotient = num / 2;
		remainder = num % 2;
		binary_array[i] = remainder;
		num = quotient;
		i--;
	}
	
	for(i = 0; i < 8; i++)
		printf("%u", binary_array[i]);
	printf("\n\n");
}

/* output 

 Enter two integers : 5
10

 Bitwise XOR of the two decimal numbers 5, 10 gives result : 15
 Binary form of decimal integer 5 is    =       00000101


 Binary form of decimal integer 10 is   =       00001010


 Binary form of decimal integer 15 is   =       00001111

*/

