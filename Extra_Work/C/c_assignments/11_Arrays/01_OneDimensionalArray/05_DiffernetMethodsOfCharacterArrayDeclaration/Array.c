#include<stdio.h>

int main()
{
	char a[] = {'A', 'S', 'T', 'R', 'O', 'M', 'E', 'D', 'I', 'C', 'O', 'M', 'P', '\0'};
	char b[9] = {'W', 'e', 'l', 'c', 'o', 'm', 'e', 's', '\0'};
	char c[] = {'Y', 'O', 'U', '\0'};
	char d[] = "To";
	char e[] = "REAL TIME RENDERING BATCH 2020- 21";
	char ch[] = {'H', 'e', 'l', 'l', 'o'};
	
	printf("\n Size of a[] : %d", sizeof(a));
	printf("\n Size of b[] : %d", sizeof(b));
	printf("\n Size of c[] : %d", sizeof(c));
	printf("\n Size of d[] : %d", sizeof(d));
	printf("\n Size of e[] : %d", sizeof(e));
	printf("\n Size of ch[] : %d", sizeof(ch));
	
	printf("\n a[] : %s", a);
	printf("\n b[] : %s", b);
	printf("\n c[] : %s", c);
	printf("\n d[] : %s", d);
	printf("\n e[] : %s", e);
	printf("\n ch[] WITHOUT NULL TERMINATOR \\0: %s", ch);
	
	return(0);	
	
}

/* output *

 Size of a[] : 14
 Size of b[] : 9
 Size of c[] : 4
 Size of d[] : 3
 Size of e[] : 35
 Size of ch[] : 5
 a[] : ASTROMEDICOMP
 b[] : Welcomes
 c[] : YOU
 d[] : To
 e[] : REAL TIME RENDERING BATCH 2020- 21
 ch[] WITHOUT NULL TERMINATOR \0: Helloë
 */