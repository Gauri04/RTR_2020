#include<stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	void FunctionCountry();
	
	FunctionCountry();
	return(0);
}

void FunctionCountry()
{
	void OfAMC();
	OfAMC();
	printf("\n I live in India");
}

void OfAMC()
{
	void Surname();
	Surname();
	printf("\n Of AstroMediComp");
}

void Surname()
{
	void MiddleName();
	MiddleName();
	printf("\n Ranade");
}

void MiddleName()
{
	void FirstName();
	FirstName();
	printf("\n Uday");
}

void FirstName()
{
	void Is();
	Is();
	printf("\n Gauri");
}

void Is()
{
	void Name();
	Name();
	printf("\n Is");
}

void Name()
{
	void My();
	My();
	printf("\n Name");
}

void My()
{
	printf("\n My");
}

/* ouput *
 My
 Name
 Is
 Gauri
 Uday
 Ranade
 Of AstroMediComp
 I live in India
 */


