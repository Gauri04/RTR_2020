#include<stdio.h>
int main()
{
	void PrintBinaryFormOfNumber(unsigned int);
	
	unsigned int a, result;
	
	printf("\n Enter a integer : ");
	scanf("%u", &a);
	
	result = ~a;
	printf("\n Bitwise Complementing of a : %d gives result : %d", a,result);
	
	PrintBinaryFormOfNumber(a);
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


/* Output **

 Enter a integer : 4

 Bitwise Complementing of a : 4 gives result : -5
 Binary form of decimal integer 4 is    =       00000100


 Binary form of decimal integer -5 is   =       11111011

*/