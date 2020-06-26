#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define MAX_STRING_LENGTH 1024

struct CharacterCount
{
	char ch;
	int chCount;
}characterCount[] = { {'A', 0},
						   {'B', 0},
						   {'C', 0},
						   {'D', 0},
						   {'E', 0},
						   {'F', 0},
						   {'G', 0},
						   {'H', 0},
						   {'I', 0},
						   {'J', 0},
						   {'K', 0},
						   {'L', 0},
						   {'M', 0},
						   {'N', 0},
						   {'O', 0},
						   {'P', 0},
						   {'Q', 0},
						   {'R', 0},
						   {'S', 0},
						   {'T', 0},
						   {'U', 0},
						   {'V', 0},
						   {'W', 0},
						   {'X', 0},
						   {'Y', 0},
						   {'Z', 0},
						};

#define SIZE_OF_ENTIRE_ARRAY_OF_STRUCTS sizeof(characterCount)
#define SIZE_OF_ONE_STRUCT_FROM_ARRAY_OF_STRUCTS sizeof(characterCount[0])
#define NUM_ELEMENTS_IN_ARRAY (SIZE_OF_ENTIRE_ARRAY_OF_STRUCTS / SIZE_OF_ONE_STRUCT_FROM_ARRAY_OF_STRUCTS)

int main()
{
	char str[MAX_STRING_LENGTH];
	int i, j, actualStringLength = 0;
	
	printf("\n Enter a string : ");
	gets_s(str, MAX_STRING_LENGTH);
	
	actualStringLength = strlen(str);
	
	printf("\n Entered string is : %s", str);
	for(i = 0; i < actualStringLength; i++)
	{
		for(j = 0; j < NUM_ELEMENTS_IN_ARRAY; j++)
		{
			str[i] = toupper(str[i]);
			if(str[i] == characterCount[j].ch)
				characterCount[j].chCount++;
			
		}
	}
	
	printf("\n No. of occurences of all characters from the aplhabet are : \n");
	for(i = 0; i < NUM_ELEMENTS_IN_ARRAY; i++)
	{
		printf("\n Character : %c \t and character count : %d", characterCount[i].ch, characterCount[i].chCount);
	}
	return(0);
}

/* output *
 Enter a string : ramesh

 Entered string is : ramesh
 No. of occurences of all characters from the aplhabet are :

 Character : A   and character count : 1
 Character : B   and character count : 0
 Character : C   and character count : 0
 Character : D   and character count : 0
 Character : E   and character count : 1
 Character : F   and character count : 0
 Character : G   and character count : 0
 Character : H   and character count : 1
 Character : I   and character count : 0
 Character : J   and character count : 0
 Character : K   and character count : 0
 Character : L   and character count : 0
 Character : M   and character count : 1
 Character : N   and character count : 0
 Character : O   and character count : 0
 Character : P   and character count : 0
 Character : Q   and character count : 0
 Character : R   and character count : 1
 Character : S   and character count : 1
 Character : T   and character count : 0
 Character : U   and character count : 0
 Character : V   and character count : 0
 Character : W   and character count : 0
 Character : X   and character count : 0
 Character : Y   and character count : 0
 Character : Z   and character count : 0
 
 */
 
 

























						   
						   
						   