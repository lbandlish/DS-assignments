#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int val;
	struct node* next;
} queue;


void enqueue(queue** head, queue** tail);
void dequeue(queue** head, queue** tail);
void Is_Empty(queue** head);

int main()
{
	int t;

	scanf("%d",&t);

	for (int i = 0; i < t; i++)
	{
		int n,q;

		scanf("%d %d", &n, &q);

		queue** head = (queue**)malloc(n*sizeof(queue*));
		queue** tail = (queue**)malloc(n*sizeof(queue*));

		//printf("after first mallocs\n");
		
		for (int i = 0; i < n; i++)
		{
			head[i] = NULL;
			tail[i] = NULL;
		}

		for (int i = 0; i < q; i++)
		{
			int opc;
			scanf("%d", &opc);

			switch (opc)
			{
				case 1:	enqueue(head,tail);
					break;

				case 2: dequeue(head,tail);
					break;

				case 3: Is_Empty(head);
					break;

			}
		}
	}

	return 0;
}

void enqueue(queue** head, queue** tail)
{
	int index;
	int val;

	scanf("%d %d", &val, &index);
	printf("%d\n", val);

	queue* new_entry = (queue*)malloc(sizeof(queue));

	new_entry->val = val;
	new_entry->next = NULL;

	if (head[index-1]==NULL)
	{
		head[index-1] = new_entry;
		tail[index-1] = new_entry;
	}

	else
	{
		tail[index-1]->next = new_entry;
		tail[index-1] = new_entry;
	}
}

void dequeue(queue** head, queue** tail)
{
	int index;

	scanf("%d", &index);

	if (head[index-1]==NULL)
	{
		printf("Empty\n");
	}

	else if (head[index-1]->next==NULL)
	{
		printf("%d\n", head[index-1]->val);
		head[index-1] = NULL;
		tail[index-1] = NULL;
	}

	else
	{
		printf("%d\n", head[index-1]->val);
		head[index-1] = head[index-1]->next;
	}
}

void Is_Empty(queue** head)
{
	int index;
	scanf("%d", &index);

	if (head[index-1] == NULL)
	{
		printf("True\n");
	}

	else
	{
		printf("False\n");
	}
}
