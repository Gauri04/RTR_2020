#include<stdio.h>

struct MyPoint
{
	int x;
	int y;
}pointA, pointB, pointC, pointD, pointE;  	//global declaration

int main()
{
	pointA.x = 6;
	pointA.y = 7;
	
	pointB.x = 4;
	pointB.y = 7;
	
	pointC.x = 0;
	pointC.y = 0;
	
	pointD.x = 2;
	pointD.y = 3;
	
	pointE.x = 9;
	pointE.y = 12;
	
	printf("\n x and y coordinates of point A are x : %d, y : %d", pointA.x, pointA.y);
	
	printf("\n x and y coordinates of point B are x : %d, y : %d", pointB.x, pointB.y);
	
	printf("\n x and y coordinates of point C are x : %d, y : %d", pointC.x, pointC.y);
	
	printf("\n x and y coordinates of point D are x : %d, y : %d", pointD.x, pointD.y);

	printf("\n x and y coordinates of point E are x : %d, y : %d", pointE.x, pointE.y);
	
	return(0);
}

/* output *

 x and y coordinates of point A are x : 6, y : 7
 x and y coordinates of point B are x : 4, y : 7
 x and y coordinates of point C are x : 0, y : 0
 x and y coordinates of point D are x : 2, y : 3
 x and y coordinates of point E are x : 9, y : 12
 
 */