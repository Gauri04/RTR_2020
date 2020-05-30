#include<stdio.h>

int main()
{
	int no1, no2, result;
	
	printf("\n Enter one integer : ");
	scanf("%d", &no1);
	
	printf("\n Enter another integer : ");
	scanf("%d", &no2);
	
	printf("\n If Result is 0, it is FALSE");
	printf("\n If Result is 1, it is TRUE");
	
	result = (no1 < no2);
	printf("\n\n (no1 < no2) no1 = %d is less than no2 = %d is %d", no1, no2, result);
	
	result = (no1 > no2);
	printf("\n (no1 > no2) no1 = %d, is greater than no2 = %d is = %d", no1, no2, result);
	
	result = (no1 <= no2);
	printf("\n (no1 <= no2) no1 = %d, is less than or equal to no2 = %d is = %d", no1, no2, result);
	
	result = (no1 >= no2);
	printf("\n (no1 >= no2) no1 = %d, is greater than or equal to no2 = %d is = %d", no1, no2, result);
	
	result = (no1 == no2);
	printf("\n (no1 == no2) no1 = %d, is equal to no2 = %d is = %d", no1, no2, result);
	
	result = (no1 != no2);
	printf("\n (no1 != no2) no1 = %d, is not equal to no2 = %d is = %d\n\n", no1, no2, result);
	
	return(0);
}

/** output **

 Enter one integer : 5

 Enter another integer : 10

 If Result is 0, it is FALSE
 If Result is 1, it is TRUE

 (no1 < no2) no1 = 5 is less than no2 = 10 is 1
 (no1 > no2) no1 = 5, is greater than no2 = 10 is = 0
 (no1 <= no2) no1 = 5, is less than or equal to no2 = 10 is = 1
 (no1 >= no2) no1 = 5, is greater than or equal to no2 = 10 is = 0
 (no1 == no2) no1 = 5, is equal to no2 = 10 is = 0
 (no1 != no2) no1 = 5, is not equal to no2 = 10 is = 1
 */
