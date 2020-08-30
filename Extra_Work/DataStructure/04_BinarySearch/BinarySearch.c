#include<stdio.h>
#define MAX 100
int main()
{
	int numberArray[MAX];
	int n, i, no, lower, upper, mid;
	int flag;
	
	printf("\n Enter the number of elements you want to insert : ");
	scanf("%d", &n);
	printf("\n Enter the elements in sorted order ");
	for(i = 0; i < n; i++)
	{
		scanf("%d", &numberArray[i]);
	}
	printf("\n Enter the element to search : ");
	scanf("%d", &no);
	
	if(no < numberArray[0] || no > numberArray[n - 1])
	{
		printf("\n Number not found");
		exit(0);
	}
	
	lower = 0;
	upper = n - 1;
	flag = 0;
	while(upper >= lower)
	{
		mid = (lower + upper) / 2;
		if(no == numberArray[mid])
		{
			printf("\n Number %d successfully found at %d location", no, mid);
			flag = 1;
			break;
		}
		else if(no > numberArray[mid])
		{
			lower = mid + 1;
		}
		else
			upper = mid - 1;
		
	}
	if(flag == 0)
		printf("\n Number %d not found", no);
	
	return(0);
}
