#include<stdio.h>

int main()
{
	struct Point 
	{
		int x, y;
	};
	
	struct Rectangle
	{
		struct Point point1;
		struct Point point2;
	};
	
	struct Rectangle rect = { {1, 3}, {4, 5} };
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
	printf("\n Area of the rectangle is : %d", area);
	
	return(0);
}

/* output *

 Length of rectangle is : 3
 Breadth of rectangle is : 2
 Area of the rectangle is : 6
 
 */
 
 
 
 