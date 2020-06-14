#include<stdio.h>
#include<conio.h>

struct MyData
{
	int i;
	float f;
	double d;
	char c;
};

int main()
{
	struct MyData grData;
	
	printf("\n Enter integer : ");
	scanf("%d", &grData.i);
	
	printf("\n Enter float value : ");
	scanf("%f", &grData.f);
	
	printf("\n Enter double value : ");
	scanf("%lf", &grData.d);
	
	printf("\n Enter a character : ");
	grData.c = getch();
	
	printf("\n members of struct grData : ");
	printf("\n i : %d", grData.i);
	printf("\n f : %f", grData.f);
	printf("\n d : %lf", grData.d);
	printf("\n c : %c", grData.c);
	
	return(0);
	
}

/* output *

 Enter integer : 32

 Enter float value : 45.44

 Enter double value : 2323.232323

 Enter a character :
 members of struct grData :
 i : 32
 f : 45.439999
 d : 2323.232323
 c : d
 
 */

