#include<stdio.h>			//NULL is a macro defined in stdio.h
#include<stdlib.h>
#include<string.h>		// For strcmp() 

struct Node
{
	char data[100];
	int no;
	struct Node *next;
};
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
	if(fp == NULL)
	{
		printf("\n Error : Unable to open desired file");
		exit(0);
	}
	
	fprintf(fp, "***** Logs *****\n");
	
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
				if(fp)
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
	
	if(last == NULL)
	{
		last = temp;
		last->next = temp;
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
	fprintf(fp, "\n In insert at beginning");
	fprintf(fp, "\n temp : %p", &temp);
	fprintf(fp, "\n last : %p", &last);
	
	fprintf(fp, "\n BEFORE temp->next : %p", temp->next);
	fprintf(fp, "\n BEFORE last->next : %p", last->next);
	
	temp->next = last->next;
	last->next = temp;
	
	fprintf(fp, "\n AFTER temp->next : %p", temp->next);
	fprintf(fp, "\n AFTER last->next : %p", last->next);
		
}	

void InsertAtEnd(struct Node *temp)
{
	if(last)
	{
		temp->next = last->next;
		last->next = temp;
		last = temp;
	}
	else
		InsertAtBeginning(temp);
	
}

void InsertAtPosition(struct Node *temp)
{
	struct Node *t, *prev;
	int pos, i = 1;
	
	if(last)
	{
		printf("\n Enter the position where you want to insert the node (Position should be greater than 1) : ");
		scanf("%d", &pos);
	
		t = last->next;
		while((t != last) && i < pos)
		{
			i++;
			prev = t;
			t = t->next;
		}
		prev->next = temp;
		temp->next = t;
	}
	else
		InsertAtBeginning(temp);

}

void DeleteNode()
{
	int value;
	struct Node *node, *prevNode;
	
	if(last == NULL)
	{
		printf("\n Cannot delete : Empty linkedlist");
	}
	else
	{
		printf("Enter integer number to be deleted : ");
		scanf("%d", &value);
		
		
		node = last->next;
		int flag = 0;
		
		// If node to be deleted is the first node
		if(last->next->no == value)
		{
			// if only one node is int linked list
			if(last->next == last)
			{
				free(last);
				last = NULL;
				printf("Successfully deleted node. Linkedlist now empty");
				
			}
			else
			{
				last->next = last->next->next;
				// free the first node
				printf("\n Deleting node with value %d", value);
				free(node);
			}
		}
		else								// If node to be deleted is in the middle or in the end
		{
			while(node != last)
			{
				prevNode = node;
				node = node->next;
				if(node->no == value)
				{
					prevNode->next = node->next;
					if(node == last)
					{
						last = prevNode;
						fprintf(fp, "\n Deleting last node. Now last = %p", last);
					}
					printf("Deletion Successful");
					flag = 1;
					free(node);
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
	struct Node *temp;
	
	fprintf(fp, "\n In traverse node");
	
	if(last == NULL)
	{
		fprintf(fp, "\n In traverse, Last is NULL. Empty linkedlist");
		printf("\n Empty linklist");
	}
	else
	{
		fprintf(fp, "\n In Traverse, last->next : %p", last->next);
		
		temp = last;
		
		fprintf(fp, "\n temp : %p", temp);
		fprintf(fp, "\n last : %p", last);
		do
		{
			temp = temp->next;
			printf("\n Node data : %s \t Node no : %d", temp->data, temp->no);
		}while(temp != last);
	}
}

/* output *

 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 1

 Enter string data to insert in the node : a

 Enter integer number : 10

 Insert Node successful
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 2
Enter integer number to be deleted : 10
Successfully deleted node. Linkedlist now empty
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
 Choice : 3

 Node data : a   Node no : 10
 Node data : b   Node no : 20
 Node data : d   Node no : 40
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

 Enter the position where you want to insert the node (Position should be greater than 1) : 3

 Insert Node successful
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

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
Enter integer number to be deleted : 40
Deletion Successful
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 Node data : a   Node no : 10
 Node data : b   Node no : 20
 Node data : c   Node no : 30
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

 Node data : a   Node no : 10
 Node data : c   Node no : 30
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 2
Enter integer number to be deleted : 10

 Deleting node with value 10
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 3

 Node data : c   Node no : 30
 Enter your choice :
 1. Insert node
 2. Delete Node
 3. Traverse list
 4. Exit
 Choice : 2
Enter integer number to be deleted : 30
Successfully deleted node. Linkedlist now empty
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
 
 



