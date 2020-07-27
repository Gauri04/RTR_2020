#include<stdio.h>			
#include<stdlib.h>		// for malloc()
#include<string.h>		// For strcmp() 

struct Node
{
	char data[100];
	int no;
	struct Node *next;
	struct Node *prev;
};

struct Node *start = NULL;
FILE *fp = NULL;

int main()
{
	struct Node* CreateNode();
	void InsertNode();
	void DeleteNode();
	void TraverseNode();
	
	int ch;
	
	fp = fopen("GRLogs.txt", "w");
	if(fp == NULL)
	{
		printf("\n Cannot open log file. Exiting now..");
		exit(0);
	}
	
	fprintf(fp, "**** Logs **** \n");
	
	while(1)
	{
		printf("\n Enter your choice : ");
		printf("\n 1. Insert node ");
		printf("\n 2. Delete Node ");
		printf("\n 3. Traverse list");
		printf("\n 4. Exit");	
		printf("\n Choice : ");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1 :
				InsertNode();
				break;
		
			case 2:
				DeleteNode();
				break;
			
			case 3: 
				TraverseNode();
				break;
			
			case 4:
				fclose(fp);
				exit(0);
				
			default :
				break;
		}
	}
	
	if(fp)
		fclose(fp);
	return(0);
}

struct Node* CreateNode()
{
	struct Node *temp;
	temp = (struct Node*)malloc(sizeof(struct Node));
	return(temp);
}

void InsertNode()
{
	void InsertAtBeginning();
	void InsertAtEnd();
	void InsertAtPosition();
	
	struct Node *temp;
	int choice;
	
	temp = CreateNode();
	memset(temp->data, '\0', 100);
	
	printf("\n Enter string data to insert in the node : ");
	scanf("%s", &temp->data);
	printf("\n Enter integer number : ");
	scanf("%d", &temp->no);
	
	temp->next = NULL;
	temp->prev = NULL;
	
	if(start == NULL)
	{
		temp->next = temp;
		temp->prev = temp;
		start = temp;
	}
	else
	{
		printf("\n\n 1. Insert node at beginning ");
		printf("\n 2. Insert at end ");
		printf("\n 3. Insert at a specific position");
		printf("\n 4. Exit");
		printf("\n Enter your choice in integer : ");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1 :
				InsertAtBeginning(temp);
				break;
				
			case 2 :
				InsertAtEnd(temp);
				break;
				
			case 3 :
				InsertAtPosition(temp);
				break;
				
			default :
				break;
		}
		
		
	
	}
	printf("\n Insert Node successful");
}

void InsertAtBeginning(struct Node *temp)
{
	temp->next = start;
	temp->prev = start->prev;
	start->prev->next = temp;
	start->prev = temp;
	start = temp;
}	

void InsertAtEnd(struct Node *temp)
{
	struct Node *t;
	// go to the last node
	t = start->prev;
	
	
	temp->prev = t;
	temp->next = t->next;
	t->next = temp;
	start->prev = temp;
	
}

void InsertAtPosition(struct Node *temp)
{
	struct Node *t = NULL;
	int pos, k = 1;
	
	if(start == NULL)
	{
		printf("\n Linked list empty, inserting node at first position");
		InsertAtBeginning(temp);
	}
	
	else
	{
		printf("\n Enter the position where you want to insert the node : ");
		scanf("%d", &pos);
		
		t = start;

		while(t != start->prev && k < pos)
		{
			
			k++;
			t = t->next;
		}
		temp->next = t;
		temp->prev = t->prev;
		t->prev->next = temp;
		t->prev = temp;
		
		printf("\n Data successfully inserted at %d position", pos);
	}
	
		
}

void DeleteNode()
{
	int value;
	struct Node *node, *prevNode;
	
	if(start == NULL)
	{
		printf("\n Error : Cannot delete : Empty linkedlist");
	}
	else
	{
		printf("\n Enter integer number to be deleted : ");
		scanf("%d", &value);
		node = start;
		int flag = 0;
		
		// If node to be deleted is the first node
		if(start->no == value)
		{				
			fprintf(fp, "\n In delete node, to delete start node");
			// If deleting the  last remaining node from the linked list
			if(start == start->next)
			{
				start->next = NULL;
				start->prev = NULL;
				free(start);
				start = NULL;
				flag = 1;
				printf("\n Deletion successful. LinkedList now empty");
			}
			else
			{
				start = start->next;
				start->prev = node->prev;
				node->prev->next = start;
				free(node);
				flag = 1;
				printf("\n Deletion Successful");
			}
		}
		else								// If node to be deleted is in the middle or in the end
		{
			// If node to be deleted is the last node
			while(node != start->prev)
			{
				node = node->next;
				if(node->no == value)
				{
					prevNode = node->prev;
					prevNode->next = node->next;
					node->next->prev = prevNode;
					free(node);
					flag = 1;
					printf("\n Node deleted successfully ");
				}
					
			}
		}
		
		if(flag == 0)
		{
			printf("\n Data to be deleted not found in the list");
		}
		
	}
	
}

void TraverseNode()
{
	void TraverseFromBeginning();
	void TraverseFromEnd();
	
	int choice;
	if(start == NULL)
	{
		printf("\n Empty linklist");
	}
	else
	{
		printf("\n 1. Traverse from beginning");
		printf("\n 2. Traverse from last ");
		printf("\n Enter your choice in integer : ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1 :
				TraverseFromBeginning();
				break;
				
			case 2 :
				TraverseFromEnd();
				break;
				
			default :
				printf("\n Invalid choice");
				break;
		}
	}
}

void TraverseFromBeginning()
{
	struct Node *temp = NULL;
	temp = start;
	do
	{
		printf("\n Node data : %s \t Node no : %d", temp->data, temp->no);
		temp = temp->next;
	}while(temp != start);
}

void TraverseFromEnd()
{
	struct Node *temp = NULL;
	temp = start->prev;
	do
	{
		printf("\n Node data : %s \t Node no : %d", temp->data, temp->no);
		temp = temp->prev;
	}while(temp != start->prev);
	
}

/* output *

 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 1

 Enter string data to insert in the node : b

 Enter integer number : 20

 Insert Node successful
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 1

 Enter string data to insert in the node : a

 Enter integer number : 10


 1. Insert node at beginning
 2. Insert at end
 3. Insert at a specific position
 4. Exit
 Enter your choice in integer : 1

 Insert Node successful
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 1

 Enter string data to insert in the node : d

 Enter integer number : 40


 1. Insert node at beginning
 2. Insert at end
 3. Insert at a specific position
 4. Exit
 Enter your choice in integer : 2

 Insert Node successful
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 1

 Enter string data to insert in the node : c

 Enter integer number : 30


 1. Insert node at beginning
 2. Insert at end
 3. Insert at a specific position
 4. Exit
 Enter your choice in integer : 3

 Enter the position where you want to insert the node : 3

 Data successfully inserted at 3 position
 Insert Node successful
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 1

 Node data : a   Node no : 10
 Node data : b   Node no : 20
 Node data : c   Node no : 30
 Node data : d   Node no : 40
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 2

 Node data : d   Node no : 40
 Node data : c   Node no : 30
 Node data : b   Node no : 20
 Node data : a   Node no : 10
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 1

 Enter string data to insert in the node : e

 Enter integer number : 50


 1. Insert node at beginning
 2. Insert at end
 3. Insert at a specific position
 4. Exit
 Enter your choice in integer : 2

 Insert Node successful
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 2

 Enter integer number to be deleted : 50

 Node deleted successfully
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 1

 Node data : a   Node no : 10
 Node data : b   Node no : 20
 Node data : c   Node no : 30
 Node data : d   Node no : 40
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 2

 Node data : d   Node no : 40
 Node data : c   Node no : 30
 Node data : b   Node no : 20
 Node data : a   Node no : 10
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 1

 Node data : a   Node no : 10
 Node data : b   Node no : 20
 Node data : c   Node no : 30
 Node data : d   Node no : 40
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 2

 Enter integer number to be deleted : 10

 Deletion Successful
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 1

 Node data : b   Node no : 20
 Node data : c   Node no : 30
 Node data : d   Node no : 40
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 2

 Node data : d   Node no : 40
 Node data : c   Node no : 30
 Node data : b   Node no : 20
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 2

 Enter integer number to be deleted : 30

 Node deleted successfully
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 1

 Node data : b   Node no : 20
 Node data : d   Node no : 40
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 2

 Node data : d   Node no : 40
 Node data : b   Node no : 20
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 1

 Enter string data to insert in the node : a

 Enter integer number : 10


 1. Insert node at beginning
 2. Insert at end
 3. Insert at a specific position
 4. Exit
 Enter your choice in integer : 1

 Insert Node successful
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 1

 Node data : a   Node no : 10
 Node data : b   Node no : 20
 Node data : d   Node no : 40
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 2

 Node data : d   Node no : 40
 Node data : b   Node no : 20
 Node data : a   Node no : 10
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 2

 Enter integer number to be deleted : 40

 Node deleted successfully
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 2

 Enter integer number to be deleted : 20

 Node deleted successfully
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 1

 Node data : a   Node no : 10
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 2

 Node data : a   Node no : 10
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 2

 Enter integer number to be deleted : 10

 Deletion successful. LinkedList now empty
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 Empty linklist
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 4

*/