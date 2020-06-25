#include<stdio.h>

struct MyPoint
{
	int x;
	int y;
};

struct MyPoint pointA, pointB, pointC, pointD, pointE;	//global declaration

int main()
{
	pointA.x = 3;
	pointA.y = 2;
	
	pointB.x = 5;
	pointB.y = 6;
	
	pointC.x = 4;
	pointC.y = 7;
	
	pointD.x = 1;
	pointD.y = 3;
	
	pointE.x = 1;
	pointE.y = 1;
	
	printf("\n Coordinates of point A are x : %d, y : %d", pointA.x, pointA.y);
	
	printf("\n Coordinates of point B are x : %d, y : %d", pointB.x, pointB.y);
	
	printf("\n Coordinates of point C are x : %d, y : %d", pointC.x, pointC.y);
	
	printf("\n Coordinates of point D are x : %d, y : %d", pointD.x, pointD.y);

	printf("\n Coordinates of point E are x : %d, y : %d", pointE.x, pointE.y);
	
	return(0);
}

/* output *

 Coordinates of point A are x : 3, y : 2
 Coordinates of point B are x : 5, y : 6
 Coordinates of point C are x : 4, y : 7
 Coordinates of point D are x : 1, y : 3
 Coordinates of point E are x : 1, y : 1
 */
