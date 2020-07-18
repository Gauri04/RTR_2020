#include<stdio.h>			//NULL is a macro defined in stdio.h
#include<stdlib.h>
#include<string.h>		// For strcmp() 

struct Node
{
	char data[100];
	int no;
	struct Node *next;
	struct Node *prev;
};

struct Node *start = NULL;
struct Node *last = NULL;
FILE *fp = NULL;

int main()
{
	struct Node* CreateNode();
	void InsertNode();
	void DeleteNode();
	void TraverseNode();
	
	int ch;
	
	fp = fopen("GRLogs.txt", "w");
	
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
				exit(0);
				
			default :
				break;
		}
	}
	
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
		start = temp;
		last = temp;
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
	start->prev = temp;
	start = temp;
}	

void InsertAtEnd(struct Node *temp)
{
	struct Node *t;
	t = start;
	while(t->next != NULL)
		t = t->next;
	
	t->next = temp;
	temp->prev = t;
	last = temp;
}

void InsertAtPosition(struct Node *temp)
{
	struct Node *t, *previous;
	int pos, i = 0;
		
	printf("\n Enter the position where you want to insert the node :  ");
	scanf("%d", &pos);
	
	// if user wants to insert the node at beginning i.e position 1
	if(pos == 1)
		InsertAtBeginning(temp);
	else
	{
		t = start;
		while((t->next != NULL) && i < (pos - 1))
		{
			i++;
			previous = t;
			t = t->next;
		}
	
		if(t == last)
		{
			t->next = temp;
			temp->prev = t;
			last = temp;
		}
		else
		{
			previous->next = temp;
			temp->next = t;
			temp->prev = previous;
			t->prev = temp;
		}
	
	}
	
}

void DeleteNode()
{
	int value;
	struct Node *node, *prevNode;
	
	if(start == NULL)
	{
		printf("\n Cannot delete : Empty linkedlist");
	}
	else
	{
		printf("Enter integer number to be deleted : ");
		scanf("%d", &value);
		node = start;
		int flag = 0;
		
		// If node to be deleted is the first node
		if(start->no == value)
		{
			if(start == last)
			{
				free(start);
				start = NULL;
				last = NULL;
				printf("\n Successfully deleted the ndoe. Linkedlist now empty");
			}
			else
			{
				fprintf(fp, "\n In delete node, to delete start node");
				start = start->next;
				free(start->prev);
				start->prev = NULL;
				flag = 1;
				printf("Deletion Successful");
			}
		}
		else								// If node to be deleted is in the middle or in the end
		{
			// If node to be deleted is the last node
			if(last->no == value)
			{
				fprintf(fp, "\n In delete node, to delete last node");
				node = last;
				last = last->prev;
				last->next = NULL;
				free(node);
				flag = 1;
				printf("Deletion Successful");
				
			}
			
			while(node->next != NULL)
			{
				prevNode = node;
				node = node->next;
				if(node->no == value)
				{
					fprintf(fp, "\n In delete node, to delete middle node");
					prevNode->next = node->next;
					node->next->prev = prevNode;
					flag = 1;
					free(node);
					printf("Deletion Successful");
					break;
				}
					
			}
			if(flag == 0)
			{
				printf("\n Data to be deleted not found in the list");
			}
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
	while(temp != NULL)
	{
		printf("\n Node data : %s \t Node no : %d", temp->data, temp->no);
		temp = temp->next;
	}
}

void TraverseFromEnd()
{
	struct Node *temp = NULL;
	temp = last;
	while(temp != NULL)
	{
		printf("\n Node data : %s \t Node no : %d", temp->data, temp->no);
		temp = temp->prev;
	}
	
}

/* output *
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 1

 Enter string data to insert in the node : pqr

 Enter integer number : 30

 Insert Node successful
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 1

 Enter string data to insert in the node : abc

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

 Enter string data to insert in the node : xyz

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

 Enter string data to insert in the node : lmn

 Enter integer number : 20


 1. Insert node at beginning
 2. Insert at end
 3. Insert at a specific position
 4. Exit
 Enter your choice in integer : 3

 Enter the position where you want to insert the node :  2

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

 Node data : abc         Node no : 10
 Node data : lmn         Node no : 20
 Node data : pqr         Node no : 30
 Node data : xyz         Node no : 40
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 3

 Invalid choice
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 2

 Node data : xyz         Node no : 40
 Node data : pqr         Node no : 30
 Node data : lmn         Node no : 20
 Node data : abc         Node no : 10
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 2
Enter integer number to be deleted : 20
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

 Node data : abc         Node no : 10
 Node data : pqr         Node no : 30
 Node data : xyz         Node no : 40
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 2

 Node data : xyz         Node no : 40
 Node data : pqr         Node no : 30
 Node data : abc         Node no : 10
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 2
Enter integer number to be deleted : 40
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

 Node data : abc         Node no : 10
 Node data : pqr         Node no : 30
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 4

 Invalid choice
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 2

 Node data : pqr         Node no : 30
 Node data : abc         Node no : 10
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

 Node data : pqr         Node no : 30
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 1. Traverse from beginning
 2. Traverse from last
 Enter your choice in integer : 2

 Node data : pqr         Node no : 30
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 4

*/



