#include<stdio.h>

typedef int GR_INT;

int main()
{
	GR_INT Add(GR_INT, GR_INT);
	
	typedef int GR_INT;
	typedef float GR_FLOAT;
	typedef char GR_CHAR;
	typedef double GR_DOUBLE; 
	
	// typedef like in win32
	typedef unsigned int UINT;
	typedef UINT HANDLE;
	typedef HANDLE HWND;
	typedef HWND HINSTANCE;
	
	GR_INT a = 10, i;
	GR_INT iArray[] = {9, 18, 27, 26,45, 54, 63,72,81,90};
	GR_FLOAT fNum = 20.8f;
	const float fPI = 3.14;
	GR_CHAR ch = '*';
	GR_CHAR chArray01[] = "Hello";
	GR_CHAR chArray02[][10] = {"RTR", "Batch", "2020-2021"};
	
	GR_DOUBLE d = 5.343343;
	
	UINT uint = 434;
	HANDLE handle = 2232;
	HWND hwnd = 32;
	HINSTANCE hInstance = 7666;
	
	printf("\n Type GR_INT variable a : %d",a);
	
	for(i = 0; i < (sizeof(iArray) / sizeof(int)); i++)
	{
		printf("\n Type GR_INT array variable iArray[%d] : %d", i, iArray[i]);
	}
	
	printf("\n\n Type GR_FLOAT variable fNum : %f", fNum);
	printf("\n Type GR_FLOAT constant fPI : %f", fPI);
	
	printf("\n\n Type GR_DOUBLE variable d : %lf ", d);
	
	printf("\n\n Type GR_CHAR variable ch : %c ", ch);
	
	printf("\n Type GR_CHAR variable array : %s \n\n", chArray01);
	
	for(i = 0; i < (sizeof(chArray02) / sizeof(chArray02[0])); i++)
	{
		printf("%s \t", chArray02[i]);
	}
	
	printf("\n\n value of UINT variable : %d", uint);
	printf("\n\n value of handle variable : %d", handle);
	printf("\n\n value of hwnd variable : %d", hwnd);
	printf("\n\n value of hInstance variable : %d", hInstance);
	
	return(0);
}

/* output *

 Type GR_INT variable a : 10
 Type GR_INT array variable iArray[0] : 9
 Type GR_INT array variable iArray[1] : 18
 Type GR_INT array variable iArray[2] : 27
 Type GR_INT array variable iArray[3] : 26
 Type GR_INT array variable iArray[4] : 45
 Type GR_INT array variable iArray[5] : 54
 Type GR_INT array variable iArray[6] : 63
 Type GR_INT array variable iArray[7] : 72
 Type GR_INT array variable iArray[8] : 81
 Type GR_INT array variable iArray[9] : 90

 Type GR_FLOAT variable fNum : 20.799999
 Type GR_FLOAT constant fPI : 3.140000

 Type GR_DOUBLE variable d : 5.343343

 Type GR_CHAR variable ch : *
 Type GR_CHAR variable array : Hello

RTR     Batch   2020-2021

 value of UINT variable : 434

 value of handle variable : 2232

 value of hwnd variable : 32

 value of hInstance variable : 7666
 */





