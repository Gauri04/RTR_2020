#include<stdio.h>

int main()
{
	struct Point
	{
		int x;
		int y;
	}pointA, pointB, pointC, pointD, pointE;
	
	pointA.x = 2;
	pointA.y = 2;
	
	pointB.x = 0;
	pointB.y = 0;
	
	pointC.x = -5;
	pointC.y = 3;
	
	pointD.x = -3;
	pointD.y = -3;
	
	pointE.x = -13;
	pointE.y = 1;
	
	printf("\n Coordinates of point A are x : %d, y : %d", pointA.x, pointA.y);
	
	printf("\n Coordinates of point B are x : %d, y : %d", pointB.x, pointB.y);
	
	printf("\n Coordinates of point C are x : %d, y : %d", pointC.x, pointC.y);
	
	printf("\n Coordinates of point D are x : %d, y : %d", pointD.x, pointD.y);

	printf("\n Coordinates of point E are x : %d, y : %d", pointE.x, pointE.y);
	
	return(0);
	
}


/* output *
 Coordinates of point A are x : 2, y : 2
 Coordinates of point B are x : 0, y : 0
 Coordinates of point C are x : -5, y : 3
 Coordinates of point D are x : -3, y : -3
 Coordinates of point E are x : -13, y : 1
 
 */






