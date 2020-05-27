#include<stdio.h>

int main(void)
{
	printf("\n\n");
	printf("*************************************");
	printf("\n\n");
	printf("Hello world \n\n");
	
	int a = 13;
	printf("Integer decimal value of 'a' = %d\n", a);
	printf("Octal value of 'a' = %o\n", a);
	
	printf("Integer Hexadecimal value of 'a' (Hexadecimal letters in lower case) = %x \n", a);
	printf("Integer Hexadecimal value of 'a' (Hexadecimal letters in capital case) = %X \n", a);
	
	char ch = 'A';
	printf("Character ch = %c\n", ch);
	char str[] = "Atromedicomp's Real time rendering batch 3.0 (2020-2021)";
	printf("String str = %s\n\n", str);
	
	long num = 30121995L;
	printf("Long integer = %ld\n\n", num);
	
	unsigned int b = 7;
	printf("Unsigned integer 'b' =%u\n\n", b);
	
	float f_num = 3012.1995f;
	printf("Floating point number with just %%f 'f_num' = %f\n", f_num);
	printf("Floating point number with %%4.2f 'f_num' = %4.2f\n", f_num);
	printf("Floating point number with just %%6.5f 'f_num' = %6.5f\n\n", f_num);
	
	double d_pi = 3.14159265235897323846;
	printf("Double precision floating point number without exponential = %g\n", d_pi);
	printf("Double precision floating point number with exponential (Lower case) = %e\n", d_pi);
	printf("Double precision floating point number with exponential (Upper case) = %E\n", d_pi);
	printf("Double hexadecimal value of d_pi (Hexadecimal letters in lower case) = %a\n", d_pi);
	printf("Double hexadecimal value of d_pi (Hexadecimal letters in upper case) = %A\n\n", d_pi);		
	
	printf("******************************************************\n");
	
	return(0);
	
	
}


/** output **

*************************************

Hello world 

Integer decimal value of 'a' = 13
Octal value of 'a' = 15
Integer Hexadecimal value of 'a' (Hexadecimal letters in lower case) = d 
Integer Hexadecimal value of 'a' (Hexadecimal letters in capital case) = D 
Character ch = A
String str = Atromedicomp's Real time rendering batch 3.0 (2020-2021)

Long integer = 30121995

Unsigned integer 'b' =7

Floating point number with just %f 'f_num' = 3012.199463
Floating point number with %4.2f 'f_num' = 3012.20
Floating point number with just %6.5f 'f_num' = 3012.19946

Double precision floating point number without exponential = 3.14159
Double precision floating point number with exponential (Lower case) = 3.141593e+00
Double precision floating point number with exponential (Upper case) = 3.141593E+00
Double hexadecimal value of d_pi (Hexadecimal letters in lower case) = 0x1.921fb5419e2bp+1
Double hexadecimal value of d_pi (Hexadecimal letters in upper case) = 0X1.921FB5419E2BP+1

******************************************************
*/























