#include<stdio.h>
int main(void)
{
	int month;
	
	printf("\n Enter month : ");
	scanf("%d", &month);
	
	switch(month)
	{
		case 1:  //January
			printf("\n month number is %d i.e January", month);
			break;
		
		case 2:  
			printf("\n month number is %d i.e February", month);
			break;
			
		case 3:  
			printf("\n month number is %d i.e March", month);
			break;
			
		case 4:  
			printf("\n month number is %d i.e April", month);
			break;
		
		case 5:  
			printf("\n month number is %d i.e May", month);
			break;
			
		case 6:  
			printf("\n month number is %d i.e June", month);
			break;
			
		case 7:  
			printf("\n month number is %d i.e July", month);
			break;
			
		case 8:  
			printf("\n month number is %d i.e August", month);
			break;
			
		case 9:  
			printf("\n month number is %d i.e September", month);
			break;
			
		case 10:  
			printf("\n month number is %d i.e October", month);
			break;
			
		case 11:  
			printf("\n month number is %d i.e November", month);
			break;
			
		case 12:  
			printf("\n month number is %d i.e December", month);
			break;
			
		default:
			printf("\n Invalid month entered");
	}
	printf("\n Switch case block finished");
	
	return(0);
	
}

/* output *

 Enter month : 3

 month number is 3 i.e March
 Switch case block finished
 */






