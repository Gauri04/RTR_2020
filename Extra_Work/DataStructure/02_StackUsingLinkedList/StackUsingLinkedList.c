#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node *ptr;
}
Node;

// global variable declaration
Node *top = NULL;
FILE *fp = NULL;

int main()
{
	// function declaration
	void PushToStack();
	void PopFromStack();
	void PeekFromStack();
	Node* CreateNode();
	int isEmpty();
	
	// variable declaration
	char ch;
	
	fp = fopen("GRLogs.txt", "w");
	if(fp == NULL)
	{
		printf("\n Error : Logs file cannot be opened. Exiting Now..");
		exit(0);
	}
	
	fprintf(fp, "**** Logs ****\n");
	
	while(1)
	{
		printf("\n\n ***** Menu ******");
		printf("\n 1. Push data to the stack");
		printf("\n 2. Pop data from the stack");
		printf("\n 3. Peek data (top) from the stack");
		printf("\n 4. Exit");
		printf("\n Enter your choice : ");
		ch = getch();
		printf("\n %c", ch);
		
		switch(ch)
		{
			case '1' :
				PushToStack();
				break;
				
			case '2' :
				PopFromStack();
				break;
				
			case '3' :
				PeekFromStack();
				break;
				
			case '4' :
				if(fp)
					fclose(fp);
				exit(0);
				break;
				
			default :
				printf("\n Invalid choice..!!");
				break;
				
		}
		
	}
	
	if(fp)
		fclose(fp);
	
	return(0);
	
}

Node* CreateNode()
{
	Node *temp = (Node *)malloc(sizeof(Node));
	return(temp);
}

int isEmpty()
{
	if(top == NULL)
		return(0);
	
	return(1);
}

void PushToStack()
{
	// variable declaration
	Node *temp;
	
	temp = CreateNode();
	printf("\n Enter the data that you want to push to stack : ");
	scanf("%d", &temp->data);
	temp->ptr = top;
	top = temp;
	fprintf(fp, "\n In push to stack, top : %p, top->data : %d", top, top->data);
	printf("\n Successfully pushed the data (%d) to the stack", temp->data);
}

void PopFromStack()
{
	Node *temp;
	int data = 0;
	
	if(isEmpty() == 1)
	{
		temp = top;
		data = top->data;
		top = top->ptr;
		temp->ptr = NULL;
		free(temp);
		fprintf(fp, "\n\n In pop from stack, popped data : %d", data);
		printf("\n Successfully popped the data (%d) from stack", data);
	}
	else
		printf("\n Stack empty");
}

void PeekFromStack()
{
	if(isEmpty() == 1)
		printf("\n Data from top of the stack : %d", top->data);
	else
		printf("\n Stack empty");
}

/* output *

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 1
 Enter the data that you want to push to stack :
20

 Successfully pushed the data (20) to the stack

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 2
 Successfully popped the data (20) from stack

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 1
 Enter the data that you want to push to stack : 100

 Successfully pushed the data (100) to the stack

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 1
 Enter the data that you want to push to stack : 200

 Successfully pushed the data (200) to the stack

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 1
 Enter the data that you want to push to stack : 300

 Successfully pushed the data (300) to the stack

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 3
 Data from top of the stack : 300

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 2
 Successfully popped the data (300) from stack

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 3
 Data from top of the stack : 200

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 2
 Successfully popped the data (200) from stack

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 1
 Enter the data that you want to push to stack : 400

 Successfully pushed the data (400) to the stack

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 3
 Data from top of the stack : 400

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 2
 Successfully popped the data (400) from stack

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 2
 Successfully popped the data (100) from stack

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 3
 Stack empty

 ***** Menu ******
 1. Push data to the stack
 2. Pop data from the stack
 3. Peek data (top) from the stack
 4. Exit
 Enter your choice :
 4


*/











