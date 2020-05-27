#include<stdio.h>

int main()
{
	printf("\n\n");
	printf("Going On to next line.. using \\n escape sequence\n\n");
	printf("Demonstrating \t horizontal \t using \t \\t escape sequence !!\n\n");
	printf("\"This is a double quoted output\" done using \\\" \\\" escape sequence \n\n");
	printf("\'This is a single quoted output\' done using \\\' \\\' escape sequence \n\n");
	printf("Backspace turned to backspace\b using escape sequence \\b \n\n");
	
	printf("\r Demonstrating carriage return using \\r escape sequence \n");
	printf("Demonstrating \r carriage return \\r escape sequence \n");
	printf("Demonstrating carriage \r return \\r using \\r escape sequence\n\n");
	
	printf("Demonstrating \x41 using \\xhh escape sequence \n\n");  // 0x41 is hexadecimal code for 'A'. 'xxh' is palceholder 
								// for 'x' followed by 2 digits altogether forming hexadecimal number
				
	printf("Demonstrating \102 using \\ooo escape sequence \n\n");  // 102 is the octal letter 'B'. 'ooo' is the placeholder for
								// 3 digits forming an octal number
								
	return(0);
						
}

/* * output **


Going On to next line.. using \n escape sequence

Demonstrating 	 horizontal 	 using 	 \t escape sequence !!

"This is a double quoted output" done using \" \" escape sequence 

'This is a single quoted output' done using \' \' escape sequence 

Backspace turned to backspac using escape sequence \b 

 Demonstrating carriage return using \r escape sequence 
 carriage return \r escape sequence 
 return \r using \r escape sequence

Demonstrating A using \xhh escape sequence 

Demonstrating B using \ooo escape sequence 
*/
