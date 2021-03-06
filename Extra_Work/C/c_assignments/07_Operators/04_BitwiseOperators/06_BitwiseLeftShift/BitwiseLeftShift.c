#include<stdio.h>
int main()
{
	void PrintBinaryFormOfNumber(unsigned int);
	
	unsigned int a,num_bits, result;
	
	printf("\n Enter a integer : ");
	scanf("%u", &a);
	printf("\n How many bits you want to shift a : %d to left :", a);
	scanf("%u", &num_bits);
	
	result = a << num_bits;
	printf("\n Bitwise Left shift (<<) of a : %d gives result : %d", a,result);
	
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


/* output *

 Enter a integer : 2

 How many bits you want to shift a : 2 to left :3

 Bitwise Left shift (<<) of a : 2 gives result : 16
 Binary form of decimal integer 2 is    =       00000010


 Binary form of decimal integer 16 is   =       00010000

*/
