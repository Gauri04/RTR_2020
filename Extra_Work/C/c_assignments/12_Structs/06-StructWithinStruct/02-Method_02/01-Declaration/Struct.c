#include<stdio.h>

struct Point
{
	int x;
	int y;
};

struct Rectangle
{
	struct Point point1, point2;
};

int main()
{
	struct Rectangle rect;
	int length, breadth, area;
	
	printf("\n Enter leftmost X coordinate and bottom-left Y coordinates of a rectangle : ");
	scanf("%d%d", &rect.point1.x, &rect.point1.y);
	printf("\n Enter rightmost X coordinate and bottom-right Y coordinates of a rectangle : ");
	scanf("%d%d", &rect.point2.x, &rect.point2.y);
	
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
 Enter leftmost X coordinate and bottom-left Y coordinates of a rectangle : 0
0

 Enter rightmost X coordinate and bottom-right Y coordinates of a rectangle : 2 4

 Length of rectangle is : 2
 Breadth of rectangle is : 4
 Area of given ractangle is : 8
 
 */
 
 