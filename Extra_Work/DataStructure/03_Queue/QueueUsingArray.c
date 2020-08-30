#include<stdio.h>
#include<stdlib.h>
#define MAX_INT 9999
#define MIN_INT -9999

struct Queue
{
	int front; 
	int rear;
	int size; // to check total no. of elements currently present in array
	int capacity; // capacity of array
	int *array;
};


int main()
{
	// funcion declaration
	struct Queue* CreateQueue(unsigned int);
	
	int Enqueue(struct Queue*, int data);
	int Dequeue(struct Queue*);
	int GetFront(struct Queue*);
	int GetRear(struct Queue*);
	
	// local variable declaration
	int choice;
	int capacity;
	struct Queue *queue;
	int result;
	int data;
	
	
	printf("\n Enter capacity for queue : ");
	scanf("%d", &capacity);
	queue = CreateQueue(capacity);
	while(1)
	{
		printf("\n\n **** Queue ****");
		printf("\n   Operations   ");
		printf("\n 1. Enqueue");
		printf("\n 2. Dequeue");
		printf("\n 3. Exit");
		printf("\n Enter your choice in integer : ");
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 1 :
				printf("\n Enter an integer item to add in the queue : ");
				scanf("%d", &data);
				result = Enqueue(queue, data);
				if(result == MAX_INT)
				{
					printf("\n Unable to add item, queue is full. Please delete an item and try again");
					break;
				}
				printf("\n Successfully added item : %d in the queue", result);
				printf("\n Front : %d, rear : %d", GetFront(queue), GetRear(queue));
				break;
				
			case 2 :
				result = Dequeue(queue);
				if(result == MIN_INT)
				{
					printf("\n Unable to delete item, queue is empty, Please add an item and try again");
					break;
				}
				printf("\n Successfully deleted item : %d from the queue", result);
				printf("\n Front : %d, rear : %d", GetFront(queue), GetRear(queue));
				break;
				
			case 3 :
				exit(0);
				break;
				
			default : 
				printf("\n Invalid choice");
				break;
				
		}
	}
	
	return(0);
}

struct Queue* CreateQueue(unsigned int qCapacity)
{
	struct Queue *queue = (struct Queue*)malloc(sizeof(struct Queue));
	queue->front = 0;
	queue->size = 0;
	queue->capacity = qCapacity;
	queue->rear = qCapacity - 1;
	queue->array = (int *)malloc(queue->capacity * sizeof(int));
	return(queue);
}

int IsFull(struct Queue *queue)
{
	// if capacity and size are equal, queue is full
	return(queue->capacity == queue->size);
}

int IsEmpty(struct Queue *queue)
{
	// if size (no. of elements currently in queue) is empty, queue is empty
	return(queue->size == 0);
}

int Enqueue(struct Queue *queue, int data)
{
	// function declaration
	int IsFull(struct Queue*);
	
	if(IsFull(queue))
	{
		//printf("\n Unable to add item, queue is full. Please delete a data and try again");
		return(MAX_INT);
	}
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = data;
	queue->size = queue->size + 1;
	//printf("\n Successfully inserted item : %d into queue", data);
	return(data);
}

int Dequeue(struct Queue *queue)
{
	// function declaration
	int IsEmpty(struct Queue*);
	
	if(IsEmpty(queue))
	{
		//printf("\n Unable to delete item, queue is full. Please add data and try again");
		return(MIN_INT);
	}
	
	int data = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size = queue->size - 1;
	//printf("\n Successfully deleted item : %d from queue", data);
	return(data);
}

int GetFront(struct Queue *queue)
{
	// function declaration
	int IsEmpty(struct Queue*);
	
	if(IsEmpty(queue))
	{
		return(MIN_INT);
	}
	return(queue->array[queue->front]);
}

int GetRear(struct Queue *queue)
{
	// function declaration
	int IsEmpty(struct Queue*);
	
	if(IsEmpty(queue))
	{
		return(MIN_INT);
	}
	return(queue->array[queue->rear]);
}









