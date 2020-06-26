
#include<stdio.h>

struct MyData
{
	int i;
	float f;
	double d;
	char c;
};

int main()
{
	struct MyData AddStructMembers(struct MyData, struct MyData, struct MyData);
	struct MyData md1, md2, md3, resultData;
	
	printf("\n MyData 1 : \n");
	printf("\n Enter integer value for struct MyData md1 : \n");
	scanf("%d", &md1.i);
	printf("\n Enter float value for struct MyData md1 : \n");
	scanf("%f", &md1.f);
	printf("\n Enter double value for struct MyData md1 : \n");
	scanf("%lf", &md1.d);
	printf("\n Enter char value for struct MyData md1 : \n");
	md1.c = getch();
	printf("\n %c", md1.c);
	
	printf("\n\n MyData 2 : \n");
	printf("\n Enter integer value for struct MyData md2 : \n");
	scanf("%d", &md2.i);
	printf("\n Enter float value for struct MyData md2 : \n");
	scanf("%f", &md2.f);
	printf("\n Enter double value for struct MyData md2 : \n");
	scanf("%lf", &md2.d);
	printf("\n Enter char value for struct MyData md2 : \n");
	md2.c = getch();
	printf("\n %c", md2.c);
	
	printf("\n\n MyData 3 : \n");
	printf("\n Enter integer value for struct MyData md3 : \n");
	scanf("%d", &md3.i);
	printf("\n Enter float value for struct MyData md3 : \n");
	scanf("%f", &md3.f);
	printf("\n Enter double value for struct MyData md3 : \n");
	scanf("%lf", &md3.d);
	printf("\n Enter char value for struct MyData md3 : \n");
	md3.c = getch();
	printf("\n %c", md3.c);
	
	
	resultData = AddStructMembers(md1, md2, md3);
	printf("\n\n MyData resultData : \n");
	printf("\n resultData.i : %d", resultData.i);
	printf("\n resultData.f : %f", resultData.f);
	printf("\n resultData.d : %lf", resultData.d);
	
	resultData.c = md1.c;
	printf("\n resultData.c from md1.c : %c", resultData.c);
	
	resultData.c = md2.c;
	printf("\n resultData.c from md2.c : %c", resultData.c);
	
	resultData.c = md3.c;
	printf("\n resultData.c from md2.c : %c", resultData.c);
	
	return(0);
	
}


struct MyData AddStructMembers(struct MyData md1, struct MyData md2, struct MyData md3)
{
	struct MyData result;
	result.i = md1.i + md2.i + md3.i;
	result.f = md1.f + md2.f + md3.f;
	result.d = md1.d + md2.d + md3.d;
	
	return(result);
}

/* output *
 MyData 1 :

 Enter integer value for struct MyData md1 :
10

 Enter float value for struct MyData md1 :
10.1

 Enter double value for struct MyData md1 :
10.11

 Enter char value for struct MyData md1 :

 a

 MyData 2 :

 Enter integer value for struct MyData md2 :

20

 Enter float value for struct MyData md2 :
20.1

 Enter double value for struct MyData md2 :
20.11

 Enter char value for struct MyData md2 :

 b

 MyData 3 :

 Enter integer value for struct MyData md3 :
30

 Enter float value for struct MyData md3 :
30.1

 Enter double value for struct MyData md3 :
30.11

 Enter char value for struct MyData md3 :

 c

 MyData resultData :

 resultData.i : 60
 resultData.f : 60.300003
 resultData.d : 60.330000
 resultData.c from md1.c : a
 resultData.c from md2.c : b
 resultData.c from md2.c : c
 
 */





