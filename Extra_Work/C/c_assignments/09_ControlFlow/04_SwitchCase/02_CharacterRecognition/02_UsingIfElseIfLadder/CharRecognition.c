#include<stdio.h>
#include<conio.h>

#define CHAR_ALPHABET_UPPER_CASE_BEGINNING 65
#define CHAR_ALPHABET_UPPER_CASE_ENDING 90

#define CHAR_ALPHABET_LOWER_CASE_BEGINNING 97
#define CHAR_ALPHABET_LOWER_CASE_ENDING 122

#define CHAR_DIGIT_BEGINNING 48
#define CHAR_DIGIT_ENDING 57

int main()
{
	char ch;
	int ch_value;
	
	printf("\n Enter a character : ");
	ch = getch();
	
	if( (ch == 'A' || ch == 'a') || (ch == 'E' || ch == 'e') || (ch == 'I' || ch == 'i')
		|| (ch == 'O' || ch == 'o') || (ch == 'U' || ch == 'u') )
	{
		printf("\n Character entered by you : \'%c\' is a vowel ",ch);
	}
	
	else
	{
		ch_value = (int)ch;
		printf("\n ASCII value of entered character is : %d", ch);
			
		if((ch_value >= CHAR_ALPHABET_UPPER_CASE_BEGINNING && ch_value <= CHAR_ALPHABET_UPPER_CASE_ENDING 
			) || (ch_value >= CHAR_ALPHABET_LOWER_CASE_BEGINNING && ch_value <= CHAR_ALPHABET_LOWER_CASE_ENDING))
		{
			printf("\n Character entered by you : \'%c\' is a consonent character ", ch);
		}	
			
		else if(ch_value >= CHAR_DIGIT_BEGINNING && ch_value <= CHAR_DIGIT_ENDING)
		{
			printf("\n Character entered by you : \'%c\' is a digit character ", ch);
		}
			
		else
		{
			printf("\n Character entered by you : \'%c\' is a special character ", ch);
		}
	}
	
	return(0);
	
}

/* output *

 Enter a character :
 ASCII value of entered character is : 45
 Character entered by you : '-' is a special character
 */




