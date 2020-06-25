#include<stdio.h>

struct Point
{
	int x;
	int y;
};

int main()
{
	struct Point pointA, pointB, pointC, pointD, pointE;		//local declaration
	
	pointA.x = 6;
	pointA.y = 5;
	
	pointB.x = 5;
	pointB.y = 5;
	
	pointC.x = 7;
	pointC.y = 77;
	
	pointD.x = 12;
	pointD.y = 23;
	
	pointE.x = 3;
	pointE.y = 2;
	
	printf("\n Coordinates of point A are x : %d, y : %d", pointA.x, pointA.y);
	
	printf("\n Coordinates of point B are x : %d, y : %d", pointB.x, pointB.y);
	
	printf("\n Coordinates of point C are x : %d, y : %d", pointC.x, pointC.y);
	
	printf("\n Coordinates of point D are x : %d, y : %d", pointD.x, pointD.y);

	printf("\n Coordinates of point E are x : %d, y : %d", pointE.x, pointE.y);
	
	return(0);
	
}

/* output *

 Coordinates of point A are x : 6, y : 5
 Coordinates of point B are x : 5, y : 5
 Coordinates of point C are x : 7, y : 77
 Coordinates of point D are x : 12, y : 23
 Coordinates of point E are x : 3, y : 2
*/



