#include<stdio.h>

int main()
{
	int a, b, c, result;
	printf("\n Enter first integer :");
	scanf("%d", &a);
	printf("\n Enter another integer : ");
	scanf("%d", &b);
	printf("\n Enter third integer : ");
	scanf("%d", &c);
	
	printf("\n If Result is 0, it is FALSE");
	printf("\n If Result is 1, it is TRUE");
	
	result = (a <= b) && (b != c);
	printf("\nLogical AND, answer is true if both conditions are true.. \n result for a = %d, b = %d, c = %d where (a <= b) && (b != c) is %d", a,b,c, result);
	
	result = (b >= a) || (a == c);
	printf("Logical OR, answer is true if any one condition is true..");
	printf("\n result for b = %d is greater than or equal to a = %d, OR a = %d is equal to c= %d is %d", b,a,a,b,result);

	result  = !a;
	printf("\n a = %d and using logical NOT (!) operator on a gives result %d", a, result);
	
	result  = !b;
	printf("\n b = %d and using logical NOT (!) operator on b gives result %d", b, result);
	
	result  = !c;
	printf("\n c = %d and using logical NOT (!) operator on c gives result %d", c, result);
	
	result = (!(a <= b) && ! (b != c));
	printf("\n using logical NOT on (a <= b) and also on (b != c) and then ANDing them together gives result : %d", result);
	
	result = !((b >= a) || (a == c));
	printf("\n using logical NOT on entire expression (b >= a) || (a == c) gives result = %d", result);
	
	return(0);
	
}

/* output 

 Enter first integer :10

 Enter another integer : 5

 Enter third integer : 2

 If Result is 0, it is FALSE
 If Result is 1, it is TRUE
Logical AND, answer is true if both conditions are true..
 result for a = 10, b = 5, c = 2 where (a <= b) && (b != c) is 0Logical OR, answer is true if any one condition is true..
 result for b = 5 is greater than or equal to a = 10, OR a = 10 is equal to c= 5 is 0
 a = 10 and using logical NOT (!) operator on a gives result 0
 b = 5 and using logical NOT (!) operator on b gives result 0
 c = 2 and using logical NOT (!) operator on c gives result 0
 using logical NOT on (a <= b) and also on (b != c) and then ANDing them together gives result : 0
 using logical NOT on entire expression (b >= a) || (a == c) gives result = 1
 */

