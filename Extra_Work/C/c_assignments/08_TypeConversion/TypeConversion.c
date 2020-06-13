#include<stdio.h>

int main()
{
	int i,j;
	char ch1, ch2;
	int a, iResult;
	float f, fResult;
	int iExplicit;
	float fExplicit;
	
	i = 70;
	ch1 = i;
	printf("\n ch1 after (ch1 = i) is : %c", ch1);
	
	ch2 = 'Q';
	j = ch2;
	printf("\n ch2 = %c, j after (j = ch2) is : %d", ch2, j);
	
	a = 5;
	f = 7.8f;
	fResult = a + f;
	printf("\n addition of a : %d, f : %f, a + f gives fResult : %f", a,f, fResult);
	
	iResult = a + f;
	printf("\n addition of a : %d, f : %f, a + f gives iResult : %d", a,f, iResult);
	
	fExplicit = 30.1219323;
	iExplicit = (int)fExplicit;
	
	printf("\n Floating point answer which can be typecasted explicitely fExplicit : %f", fExplicit);
	printf("\n Integer equivalent of fExplicit : %d", iExplicit);
	
	return(0);
}

/** output *

 ch1 after (ch1 = i) is : F
 ch2 = Q, j after (j = ch2) is : 81
 addition of a : 5, f : 7.800000, a + f gives fResult : 12.800000
 addition of a : 5, f : 7.800000, a + f gives iResult : 12
 Floating point answer which can be typecasted explicitely fExplicit : 30.121933
 Integer equivalent of fExplicit : 30
 */
 