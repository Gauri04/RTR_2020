#include<stdio.h>

struct Point
{
	int x;
	int y;
};

struct Rectangle
{
	struct Point point1;
	struct Point point2;
};

struct Rectangle rect = { {2, 3}, {5, 6} }; 	/* global declaration, here 2 and 3 will be rect.point1.x and rect.point1.y
															5 and 6 will be rect.point2.x and rect.point2.y */

int main()
{
	int length, breadth, area;
	
	length = rect.point2.x - rect.point1.x;
	breadth = rect.point2.y - rect.point1.y;
	
	if(length < 0)
		length = length * -1;
	if(breadth < 0)
		breadth = breadth * -1;
	
	area = length * breadth;
	
	printf("\n Length of rectangle is : %d", length);
	printf("\n Breadth of rectangle is : %d", breadth);
	printf("\n Area of rectangle is : %d", area);
	
	return(0);
}

/* ouput *

 Length of rectangle is : 3
 Breadth of rectangle is : 3
 Area of rectangle is : 9
 
*/


