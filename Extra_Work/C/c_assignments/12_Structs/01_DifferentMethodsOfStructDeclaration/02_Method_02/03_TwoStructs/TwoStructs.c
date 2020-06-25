#include<stdio.h>

struct Point
{
	int x;
	int y;
};


struct PointProperties{
	int quadrant;
	char axisLocation[10];
};

struct Point point;
struct PointProperties pointProperties;

int main()
{
	printf("\n Enter X and Y coordinates of a point : ");
	scanf("%d%d", &point.x, &point.y);
	
	if(point.x == 0 && point.y == 0)
	{
		printf("\n Point is the origin : [%d, %d]", point.x, point.y);
	}
	else
	{
		if(point.x == 0)
		{
			if(point.y < 0)
				strcpy(pointProperties.axisLocation, "Negative Y");
			
			if(point.y > 0)
				strcpy(pointProperties.axisLocation, "Positive Y");
			
			pointProperties.quadrant = 0;	//Point lying on any of the coordinate axis is not a part of any quadrant
			
			printf("\n Point lies on %s axis", pointProperties.axisLocation);
		}
		else if(point.y == 0)
		{
			if(point.x < 0)
				strcpy(pointProperties.axisLocation, "Negative X");
			
			if(point.x > 0)
				strcpy(pointProperties.axisLocation, "Positive X");
			
			pointProperties.quadrant = 0;	//Point lying on any of the coordinate axis is not a part of any quadrant
			
			printf("\n Point lies on %s axis", pointProperties.axisLocation);
		}
		else
		{
			pointProperties.axisLocation[0] = '\0';	// Point lying on any of the 4 quadrants can't be lying on any of the axis
			
			if(point.x > 0 && point.y > 0)
				pointProperties.quadrant = 1;
			
			else if(point.x < 0 && point.y > 0)
				pointProperties.quadrant = 2;
			
			else if(point.x > 0 && point.y < 0)
				pointProperties.quadrant = 3;
			
			else
				pointProperties.quadrant = 4;
			
			printf("\n Point lies in quadrant : %d", pointProperties.quadrant);
			
		}
	}
	return(0);
	
}

/* output *


 Enter X and Y coordinates of a point : 0 -9

 Point lies on Negative Y axis
 

*/



