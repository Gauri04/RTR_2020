#include<stdio.h>

struct Point
{
	int x;
	int y;
};

int main()
{
	struct Point pointA, pointB, pointC, pointD, pointE;
	
	printf("\n Enter x and y coordinates for point A : ");
	scanf("%d%d", &pointA.x, &pointA.y);
	
	printf("\n Enter x and y coordinates for point B : ");
	scanf("%d%d", &pointB.x, &pointB.y);
	
	printf("\n Enter x and y coordinates for point C : ");
	scanf("%d%d", &pointC.x, &pointC.y);
	
	printf("\n Enter x and y coordinates for point D : ");
	scanf("%d%d", &pointD.x, &pointD.y);
	
	printf("\n Enter x and y coordinates for point E : ");
	scanf("%d%d", &pointE.x, &pointE.y);
	
	printf("\n Printing all point coordinates :");
	
	printf("\n Coordinates of point A are : [%d, %d]", pointA.x, pointA.y);
	
	printf("\n Coordinates of point B are : [%d, %d]", pointB.x, pointB.y);
	
	printf("\n Coordinates of point C are : [%d, %d]", pointC.x, pointC.y);
	
	printf("\n Coordinates of point D are : [%d, %d]", pointD.x, pointD.y);

	printf("\n Coordinates of point E are : [%d, %d]", pointE.x, pointE.y);
	
	return(0);
}

/* output *
 Printing all point coordinates :
 Coordinates of point A are : [5, 6]
 Coordinates of point B are : [1, 23]
 Coordinates of point C are : [2, 5]
 Coordinates of point D are : [0, 0]
 Coordinates of point E are : [2, 2]
 
*/

