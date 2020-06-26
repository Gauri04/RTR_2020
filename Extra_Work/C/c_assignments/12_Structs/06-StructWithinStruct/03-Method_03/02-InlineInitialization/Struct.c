#include<stdio.h>

int main()
{
	int length, breadth, area;
	
	struct Rectangle
	{
		struct Point
		{
			int x;
			int y;
		}point1, point2;
	}rect = { {2, 2}, {5, 6} };			// Local declaration and hardcoded initialization
	
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

/* ouput *

 Length of rectangle is : 3
 Breadth of rectangle is : 4
 Area of the rectangle is : 12
 
 */


