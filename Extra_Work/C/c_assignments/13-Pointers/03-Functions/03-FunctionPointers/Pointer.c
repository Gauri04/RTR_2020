#include<stdio.h>

int main()
{
	int AddIntegers(int, int);
	int SubtractIntegers(int, int);
	float AddFloats(float, float);
	
	typedef int(*AddIntsFnPtr)(int, int);
	AddIntsFnPtr grptrAddInt = NULL;
	AddIntsFnPtr grptrSub = NULL;
	
	typedef float(*AddFloatsFnPtr)(float, float);
	AddFloatsFnPtr grptrAddFlt = NULL;
	
	int griAnswer = 0;
	float grfAnswer = 0.0f;
	
	grptrAddInt = AddIntegers;
	griAnswer = grptrAddInt(10, 10);
	printf("\n Sum of integers is : %d", griAnswer);
	
	grptrSub = SubtractIntegers;
	griAnswer = grptrSub(20, 10);
	printf("\n Subtraction of integers : %d", griAnswer);
	
	grptrAddFlt = AddFloats;
	grfAnswer = grptrAddFlt(11.11f, 11.11f);
	printf("\n Addition of two floats is : %f", grfAnswer);
	
	return(0);
	
}

int AddIntegers(int a, int b)
{
	int c;
	c = a + b;
	return(c);
}

int SubtractIntegers(int a, int b)
{
	int c;
	c = a - b;
	return(c);
}

float AddFloats(float a, float b)
{
	float c;
	c = a + b;
	return(c);
}


/* output *

 Sum of integers is : 20
 Subtraction of integers : 10
 Addition of two floats is : 22.219999
 
 */



















