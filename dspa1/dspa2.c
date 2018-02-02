#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node* next;
} queue;


void enqueue(queue** head, queue** tail);
void dequeue(queue** head, queue** tail);
void Is_Empty(queue** head);


int main()
{
	int t,q,opc;

	scanf("%d", &t);
	
	queue* head;
	queue* tail;
	
	for (int i = 0; i < t; i++)
	{
		head = NULL;
		tail = NULL;
		scanf("%d",&q);
		
		for (int j = 0; j < q; j++)
		{
			scanf("%d", &opc);

			switch (opc)
			{
				case 1:	{
						enqueue(&head,&tail);
						break;
					}

				case 2:	{
					       	dequeue(&head,&tail);
						break;
					}

				case 3: {
						Is_Empty(&head);
						break;
					}
			}
		}

	}

	return 0;
}

void enqueue(queue** head, queue** tail)
{	
	queue* new_entry = (queue*)malloc(sizeof(queue));
	int entry_val;

	scanf("%d", &entry_val);
	printf("%d\n", entry_val);

	new_entry->val = entry_val;
	new_entry->next = NULL;

	if (*head==NULL)
	{
		*head = new_entry;
		*tail = new_entry;
	}

	else
	{
		(*tail)->next = new_entry;
		*tail = new_entry;
	}

	//printf("%p is HEAD and %p",*head,*tail);
}

void dequeue(queue** head, queue** tail)
{	
	if (*head==NULL)
	{
		printf("Empty\n");
	}

	else if((*head)->next==NULL)
	{	
		printf("%d\n", (*head)->val);
		//printf("%p %p",*head,*tail);	
		*head = NULL;
		*tail = NULL;	
		//printf("head val is %d, and tail val is %d\n",(*head)->val, (*tail)->val);
	}

	else
	{
		printf("%d\n", (*head)->val);
		*head = (*head)->next;
		//printf("head val is %d, and tail val is %d\n",(*head)->val, (*tail)->val);
	}


}

void Is_Empty(queue** head)
{
	if (*head==NULL)
	{
		printf("True\n");
	}

	else
	{
		printf("False\n");
	}
}
