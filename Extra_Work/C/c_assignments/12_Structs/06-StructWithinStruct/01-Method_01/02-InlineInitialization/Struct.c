
#include<stdio.h>

struct Rectangle
{
	struct Point
	{
		int x;
		int y;
	}point1, point2;
}rect = { {2, 3}, {5, 6} };

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
	printf("\n Area of given ractangle is : %d", area);
	
	return(0);
	
}

/* output *

 Length of rectangle is : 3
 Breadth of rectangle is : 3
 Area of given ractangle is : 9
 
 */
 
