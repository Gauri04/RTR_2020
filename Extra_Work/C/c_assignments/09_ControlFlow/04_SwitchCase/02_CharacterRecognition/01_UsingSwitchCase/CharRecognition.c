#include<stdio.h>
#include<conio.h>

#define CHAR_ALPHABET_UPPER_CASE_BEGINNING 65
#define CHAR_ALPHABET_UPPER_CASE_ENDING 90

#define CHAR_ALPHABET_LOWER_CASE_BEGINNING 97
#define CHAR_ALPHABET_LOWER_CASE_ENDING 122

#define CHAR_DIGIT_BEGINNING 48
#define CHAR_DIGIT_ENDING 57

int main(void)
{
	char ch;
	int ch_value;
	
	printf("\n enter character : ");
	ch = getch();
	
	switch(ch)
	{
		case 'A':
		case 'a':
		
		case 'E':
		case 'e':
		
		case 'I':
		case 'i':
		
		case 'O':
		case 'o':
		
		case 'U':
		case 'u':
			printf("\n Character entered by you : \'%c\' is a vowel ",ch);
			break;
			
		default:
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
			
			break;
	}
	
	printf("\n Switch case block complete");
	
	return(0);
	
}

/* output *

 enter character :
 ASCII value of entered character is : 98
 Character entered by you : 'b' is a consonent character
 Switch case block complete
 */




















