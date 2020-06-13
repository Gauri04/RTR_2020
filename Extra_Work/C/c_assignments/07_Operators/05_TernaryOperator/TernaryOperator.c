#include<stdio.h>

int main()
{
	int a,b;
	int p,q;
	char chResult1, chResult2;
	int iResult1, iResult2;
	
	a = 7;
	b = 5;
	chResult1 = (a > b) ? 'A' : 'B';	// if a > b then chResult1 = 'A' else chResult1 = 'B'
	iResult1 = (a > b) ? a : b;
	printf("\n Ternary Operator Answer 1 : %c, %d", chResult1, iResult1);
	
	p = 30;
	q = 30;
	chResult2 = (p != q) ? 'P' : 'Q';	// if p != q then chResult2 = 'P' else chResult2 = 'Q'
	iResult2 = (p != q) ? p : q;
	printf("\n Ternary Operator Answer 2 : %c, %d", chResult2, iResult2);
	
	return(0);
	
}

/* output *

 Ternary Operator Answer 1 : A, 7
 Ternary Operator Answer 2 : Q, 30
 
 */


