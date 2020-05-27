#include<stdio.h>

#define MY_PI 3.141592658979732

#define AMC_STRING "Astromedicomp RTR 3.0"

//un-named enums
enum
{
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

enum
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

// named enum
enum Numbers
{
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE = 5,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN
};

enum boolean
{
	TRUE = 1,
	FALSE = 0
};

int main()
{
	// local constant declaration
	const double epsilon = 0.000001;
	
	printf("\n\n");
	printf("Local constant epsilon %lf\n\n", epsilon);
	
	printf("Sunday is day number %d\n", SUNDAY);
	printf("Monday is day number : %d\n", MONDAY);
	printf("Tuewsday is day number : %d\n", TUESDAY);
	printf("WEdnesday is day number : %d\n", WEDNESDAY);
	printf("THURSDAY is day number : %d\n", THURSDAY);
	printf("FRIDAY is day number : %d\n", FRIDAY);
	printf("SATURDAY is day number : %d\n\n", SATURDAY);
	
	printf("ONE is enum number = %d\n", ONE);
	printf("TWO is enum number = %d\n", TWO);
	printf("THREE is enum number = %d\n", THREE);
	printf("FOUR is enum number = %d\n", FOUR);
	printf("FIVE is enum number = %d\n", FIVE);
	printf("SIX is enum number = %d\n", SIX);
	printf("SEVEN is enum number = %d\n", SEVEN);
	printf("EIGHT is enum number = %d\n", EIGHT);
	printf("NINE is enum number = %d\n", NINE);
	printf("TEN is enum number = %d\n", TEN);
	
	printf("JANUARY is Month number = %d\n", JANUARY);
	printf("FEBRUARY is Month number = %d\n", FEBRUARY);
	printf("MARCH is Month number = %d\n", MARCH);
	printf("APRIL is Month number = %d\n", APRIL);
	printf("MAY is Month number = %d\n", MAY);
	printf("JUNE is Month number = %d\n", JUNE);
	printf("JULY is Month number = %d\n", JULY);
	printf("AUGUST is Month number = %d\n", AUGUST);
	printf("SEPTEMBER is Month number = %d\n", SEPTEMBER);
	printf("OCTOBER is Month number = %d\n", OCTOBER);
	printf("NOVEMBER is Month number = %d\n", NOVEMBER);
	printf("DECEMBER is Month number = %d\n\n", DECEMBER);
	
	printf("Value of TRUE is = %d\n", TRUE);
	printf("Value of FALSE is = %d\n", FALSE);
	
	printf("MY_PI macro value = %.10lf \n\n", MY_PI);
	printf("Area of circle of radius 2 units = %f \n\n", (MY_PI * 2.0f * 2.0f));
	
	printf("\n\n");
	
	printf(AMC_STRING);
	printf("\n\n");
	
	printf("AMC string is = %s\n", AMC_STRING);
	return(0);
	
}

/** output **


Local constant epsilon 0.000001

Sunday is day number 0
Monday is day number : 1
Tuewsday is day number : 2
WEdnesday is day number : 3
THURSDAY is day number : 4
FRIDAY is day number : 5
SATURDAY is day number : 6

ONE is enum number = 0
TWO is enum number = 1
THREE is enum number = 2
FOUR is enum number = 3
FIVE is enum number = 5
SIX is enum number = 6
SEVEN is enum number = 7
EIGHT is enum number = 8
NINE is enum number = 9
TEN is enum number = 10
JANUARY is Month number = 1
FEBRUARY is Month number = 2
MARCH is Month number = 3
APRIL is Month number = 4
MAY is Month number = 5
JUNE is Month number = 6
JULY is Month number = 7
AUGUST is Month number = 8
SEPTEMBER is Month number = 9
OCTOBER is Month number = 10
NOVEMBER is Month number = 11
DECEMBER is Month number = 12

Value of TRUE is = 1
Value of FALSE is = 0
MY_PI macro value = 3.1415926590 

Area of circle of radius 2 units = 12.566371 



Astromedicomp RTR 3.0

AMC string is = Astromedicomp RTR 3.0
*/



















