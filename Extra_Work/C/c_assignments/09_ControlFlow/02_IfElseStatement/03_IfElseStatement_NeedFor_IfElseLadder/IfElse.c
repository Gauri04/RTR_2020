#include<stdio.h>

int main(void)
{
	int num;
	
	printf("\n Enter value for num : ");
	scanf("%d", &num);
	
	if(num < 0)
	{
		printf("\n num : %d is less than 0 (Negative)", num);
	}
	else	// else 1
	{
		if((num > 0) && (num <= 100))
		{
			printf("\n Num %d is between 0 and 100", num);
		}
		
		else	// else 2
		{
			
			if((num > 100) && (num <= 200))
			{	
				printf("\n Num %d is between 100 and 200", num);
			}
			else	// else 3
			{
				
				if((num > 200) && (num <= 300))
				{
					printf("\n Num %d is between 200 and 300", num);
				}
				else	// else 4
				{
					
					if((num > 300) && (num <= 400))
					{
						printf("\n Num %d is between 300 and 400", num);
					}
					else
					{
						
						if((num > 400) && (num <= 500))
						{
							printf("\n Num %d is between 400 and 500", num);
						}
						else
						{
							printf("\n Num is greater than 500");
						}
					}
				}
			}
		}		
		
	}
	printf("\n");
	return(0);
	
}

/* output *

 Enter value for num : 400

 Num 400 is between 300 and 400
*/
