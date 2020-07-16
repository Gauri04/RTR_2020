#include<stdio.h>			//NULL is a macro defined in stdio.h
#include<stdlib.h>
#include<string.h>		// For strcmp() 

struct Node
{
	char data[100];
	int no;
	struct Node *next;
};
struct Node *start;

int main()
{
	struct Node* CreateNode();
	void InsertNode();
	void DeleteNode();
	void TraverseNode();
	
	int ch;
	
	start = NULL;
	
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
	void InsetAtBeginning();
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
	
	if(start == NULL)
	{
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
				InsetAtBeginning(temp);
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

void InsetAtBeginning(struct Node *temp)
{
	temp->next = start;
	start = temp;
}	

void InsertAtEnd(struct Node *temp)
{
	struct Node *t;
	t = start;
	while(t->next != NULL)
		t = t->next;
	
	t->next = temp;
}

void InsertAtPosition(struct Node *temp)
{
	struct Node *t, *prev;
	int pos, i = 1;
		
	printf("\n Enter the position where you want to insert the node : ");
	scanf("%d", &pos);
		
	t = start;
	while((t != NULL) && i < pos )
	{
		i++;
		prev = t;
		t = t->next;
	}
	prev->next = temp;
	temp->next = t;
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
			start = start->next;
		}
		else								// If node to be deleted is in the middle or in the end
		{
			while(node->next != NULL)
			{
				prevNode = node;
				node = node->next;
				if(node->no == value)
				{
					prevNode->next = node->next;
					printf("Deletion Successful");
					flag = 1;
					free(node);
					break;
				}
					
			}
			if(flag == 0)
			{
				printf("\n Data ot be deleted not found in the list");
			}
		}
		
	}
	
}

void TraverseNode()
{
	struct Node *temp;
	if(start == NULL)
	{
		printf("\n Empty linklist");
	}
	else
	{
		temp = start;
		while(temp != NULL)
		{
			printf("\n Node data : %s \t Node no : %d", temp->data, temp->no);
			temp = temp->next;
		}
	}
}





