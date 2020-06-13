#include<stdio.h>
int main()
{
	float fNum1, fNum2, i;
	
	printf("\n Enter the float number that you want to start from : ");
	scanf("%f", &fNum1);
	
	printf("\n Enter upto How many digits the number should increment : ");
	scanf("%f", &fNum2);
	
	i = fNum1;
	do
	{
		printf("\n %f", i);
		
		i++;
	}while(i <+ (fNum1 + fNum2));
	
	return(0);
}

/* output *
Enter the float number that you want to start from : 12.5

 Enter upto How many digits the number should increment : 10

 12.500000
 13.500000
 14.500000
 15.500000
 16.500000
 17.500000
 18.500000
 19.500000
 20.500000
 21.500000
 */
 