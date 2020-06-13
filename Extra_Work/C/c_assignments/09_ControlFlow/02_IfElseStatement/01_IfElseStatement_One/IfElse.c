#include<stdio.h>
int main(void)
{
	int a,b,p;
	
	a = 9;
	b = 30;
	p = 30;
	
	if(a < b)
	{
		printf("\n First if block, A : %d is less than B : %d", a,b);
	}
	else
	{
		printf("\n First else block, A : %d is not less than B : %d", a,b);
	}
	printf("\n First if else pair is done");
	
	if(b != p)
	{
		printf("\n Second if block, B : %d is not equal to P : %d" , b,p);
	}
	else
	{
		printf("\n Second else block, B : %d is equal to P : %d" , b,p);
	}
	printf("\n Second if else pair done");
	return(0);
}

/* output *

 First if block, A : 9 is less than B : 30
 First if else pair is done
 Second else block, B : 30 is equal to P : 30
 Second if else pair done
 */

