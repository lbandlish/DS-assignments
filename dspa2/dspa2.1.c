#include <stdio.h>
#include <stdlib.h>


typedef struct listnodeint {

	int val;
	struct listnodeint* next;

}	nodeint;

typedef struct listnodeop {

	char op;
	struct listnodeop* next;

}	nodeop;


nodeint* pushint(nodeint* head, int val);
nodeop* pushop(nodeop* head, char op );
nodeint* popint(nodeint* head);
nodeop* popop(nodeop* head);
nodeop* revstack(nodeop* ohead);
void evaluatepoly(nodeop* headeqn, int x, int y);
nodeint* pushfullint(nodeop** headeqn, nodeint* headint, char ch, int x, int y);
int priority(char ch);
int compute(int val1, char op, int val2);

int main()
{
	int t;

	scanf("%d", &t);
	char skip = getchar();

	int i1;

	for (i1 = 0; i1 < t; i1++)
	{
		nodeop* headeqnrev = NULL;

		char ch = getchar();

		// printf("%d\n", ch+1 );

		while(ch != '\n')
		{
			// printf("hi\n");
			headeqnrev = pushop(headeqnrev, ch);
				ch = getchar();
		}

		int x, y;

		scanf("%d %d", &x, &y);
		getchar();

		// nodeop* headeqnrev2 = headeqnrev;

		// while(headeqnrev2 != NULL)
		// {
		// 	printf("%c ",headeqnrev2->op);
		// 	headeqnrev2 = headeqnrev2->next;
		// 	printf("oad\n");
		// }

		nodeop* headeqn = revstack(headeqnrev);

		// while (headeqn != NULL)
		// 	{
		// 	printf("%c ", headeqn->op);
		// 	headeqn = headeqn->next;
		// }
		// printf("reached before evaluatepoly\n");
		evaluatepoly(headeqn, x, y);
	}

	return 0;
}

nodeint* pushint(nodeint* head, int val)
{
	nodeint* newnode = (nodeint*)malloc(sizeof(nodeint));
	newnode->val = val;
	newnode->next = head;
	return newnode;	//assign head=pushint() when calling this
}

nodeop* pushop(nodeop* head, char op )
{
	nodeop* newnode = (nodeop*)malloc(sizeof(nodeop));
	newnode->op = op;
	newnode->next = head;
	return newnode;	//assign head=pushint() when calling this
}

nodeint* popint(nodeint* head)
{
	head = head->next;
	return head;	//assign head=pushint() when calling this
}

nodeop* popop(nodeop* head)
{
	head = head->next;
	return head;	//assign head=pushint() when calling this
}

nodeop* revstack(nodeop* ohead)
{
	nodeop* nhead = NULL;

	do
	{
		nhead = pushop(nhead, ohead->op);
		ohead = popop(ohead);
	}
	while (ohead != NULL);

	return nhead;
}

void evaluatepoly(nodeop* headeqn, int x, int y)
{
	nodeint* headint = NULL;
	nodeop* headop = NULL;
	int val1;
	int val2;
	int pushval;
	char ch;

	do
	{

			// ch = headeqn->op;
			// headeqn = popop(headeqn);

			// if (ch == 'x')
			// headint = pushint(headint, x);

			// else if (ch == 'y')
			// headint = pushint(headint, y);

			// else if (ch >= 48 && ch <= 57)
			// headint = pushfullint(&headeqn, headint, ch, x, y);
			// // headint = pushint(headint, ch);

			// else if (ch == ' ')
			// continue;

			// else
			// headop = pushop(headop, ch);

		ch = headeqn->op;
		headeqn = popop(headeqn);

		if ( ch == 'x' || ch == 'y' || (ch >= '0' && ch <= '9') )
		{
			headint = pushfullint(&headeqn, headint, ch, x, y);
			
			if (headop != NULL)
			{
				if (headeqn != NULL)
				{ 
					// headeqn = headeqn->next; // getting rid of the space. (after this headeqn points to space.)

					if (priority(headop->op) >= priority((headeqn->next)->op))
					{
						val1 = headint->val;
						headint = popint(headint);
						val2 = headint->val;
						headint = popint(headint);
						headint = pushint(headint, compute(val1, headop->op, val2));
						headop = popop(headop);

						if (headop != NULL)
						{
							if ( priority(headop->op) >= priority((headeqn->next)->op) )
							{
								val1 = headint->val;
								headint = popint(headint);
								val2 = headint->val;
								headint = popint(headint);
								headint = pushint(headint, compute(val1, headop->op, val2));
								headop = popop(headop);
							}
						}
					}

				}


				else
				{
					val1 = headint->val;
					headint = popint(headint);
					val2 = headint->val;
					headint = popint(headint);
					headint = pushint(headint, compute(val1, headop->op, val2));
					headop = headop->next;

					if (headop != NULL)
					{
						val1 = headint->val;
						headint = popint(headint);
						val2 = headint->val;
						headint = popint(headint);
						headint =  pushint(headint, compute(val1, headop->op, val2));
						headop = headop->next;
					}

					if (headint->next == NULL)
					{
						printf("%d\n",headint->val);
						return;
					}

					else
					{
						printf("Error: more than one entries in int stack after full traversal of headeqn\n");
					}
				}
			}

		}

		else if (ch == '*' || ch == '/' || ch == '+' || ch == '-' )
		{
			headop = pushop(headop, ch);
		}

		else if (ch == ' ')
		{
			continue;
		}


	}
	while (headeqn != NULL);
//delete from here
	while (headint != NULL)
	{
		printf("%d ", headint->val);
		headint = popint(headint);
	}
	printf("\n");

	while (headop != NULL)
	{
		printf("%c ", headop->op);
		headop = popop(headop);
	}
	printf("\n");
//till here.
}

nodeint* pushfullint(nodeop** headeqn, nodeint* headint, char ch, int x, int y)
{
	char chint = ch;
	int helper;
	int final = 0;
	int factor = 1;

	if (chint == 'x')
	{
		if ((*headeqn)->op == 'y')
		{
			headint = pushint(headint, (x*y));
			return headint;
		}

		headint = pushint(headint, x);
		return headint;
	}

	else if (chint == 'y')
	{
		if ((*headeqn)->op == 'x')
		{
			headint = pushint(headint, (x*y));
			return headint;
		}

		headint = pushint(headint, y);
		return headint;
	}

	do 
	{

		helper = chint - 48;
		final = final*factor + helper;
		factor = factor * 10;

		if ((*headeqn) == NULL)
		{
			break;
		}

		chint = (*headeqn)->op;

		if (chint == 32)
		{
			break;
		}

		(*headeqn) = (*headeqn)->next;

		// printf("scanning %d\n", final);++
	}
	while (chint != 'x' && chint != 'y');

	if (chint == 'x')
	{
		final = final * x;
		if (*headeqn != NULL)
		{
			// (*headeqn) = (*headeqn)->next;
			chint = (*headeqn)->op;

			if (chint == 'y')
			{
				final = final * y;
				(*headeqn) = (*headeqn)->next;
			}
		}
	}

	else if (chint == 'y')
	{
		final = final * y;

		if (*headeqn != NULL)
		{
			chint = (*headeqn)->op;

			if (chint == 'x')
			{
				final = final * x;
				(*headeqn) = (*headeqn)->next;
			}
		}
	}

	headint = pushint(headint, final);
	return headint;
}

int priority(char ch)
{
	if (ch == '+' || ch == '-')
	{
		return 0;
	}

	else if (ch == '*' || ch == '/')
	{
		return 1;
	}

	// else if (ch >= '0' && ch <= '9')
	// {
	// 	return -1;
	// }

	else
	{
		printf("Error, priority received unidentifiable character.\n");
		return -2;
	}
}

int compute(int val1, char op, int val2)
{
	switch(op)
	{
		case '+': return (val2 + val1);
					break;

		case '-': return (val2 - val1);
					break;

		case '*': return (val2 * val1);
					break;

		case '/': return (val2 / val1);
					break;
	}
}