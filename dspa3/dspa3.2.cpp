#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

typedef struct bstnode {
    char* word;
    struct bstnode* left;
    struct bstnode* right;
    int des;   //no. of descendants + 1
} node;

int interpret (char* cmd)
{
    char l[] = "learn";
    char fo[] = "forget";
    char fi[] = "findrank";

    if (strcmp(cmd,l) == 0)
    {
        return 1;
    }

    else if (strcmp(cmd,fo) == 0)
    {
        return 2;
    }

    else if (strcmp(cmd, fi) == 0)
    {
        return 3;
    }
    
    else 
    {
        printf("error\n");
        return -1;
    }
}

void swap(node &n1, node &n2)
{
      node temp = n1;
      n1 = n2;
      n2 = temp;
}

void learn(node* &head)
{
    node* n = (node*)malloc(sizeof(node));
    char* c = (char*)malloc(11*sizeof(char));

    cin >> c;
    n->word = c;
    n->left = NULL;
    n->right = NULL;
    n->des = 1;


    if (head == NULL)
    {
        head = n;
    }

    else 
    {
        node* curr = head;

        while (1)
        {
            if (strcmp(n->word,curr->word) < 0)
            {
                curr->des++;

                if (curr->left == NULL)
                {
                    curr->left = n;
                    break;
                }

                else 
                {
                    curr = curr->left;
                }
            }

            else if (strcmp(n->word, curr->word) > 0)
            {
                curr->des++;

                if (curr->right == NULL)
                {
                    curr->right = n;
                    break;
                }

                else
                {
                    curr = curr->right;
                }
            }

            else
            {
                break;
            }
        }
    }

}

void forget(node* &head)
{
    
}

void findrank(node* &head)
{
    char* c = (char*)malloc(11*sizeof(char));

    cin >> c;
    node* curr = head;
    int rank = 0;

    while(1)
    {
        if (strcmp(c, curr->word) < 0)
        {
            curr = curr->left;
        }

        else if (strcmp(c, curr->word) > 0)
        {   
            if (curr->left != NULL)
            {
                rank = rank + (curr->left)->des;
            }

            rank = rank + 1;
            curr = curr->right;
        }

        else
        {
            
            if (curr->left != NULL)
            {
                rank = rank + (curr->left)->des + 1;
            }

            else
            {
                rank = rank + 1;
            }

            break;
        }
    }

    cout << rank << endl;
}

int main()
{
    int q;
    cin >> q;

    node* head = NULL;
    char cmd[11];

    for (int i = 0; i < q; i++)
    {
        cin >> cmd;

        int ip = interpret(cmd);

        switch(ip)
        {
            case 1: learn(head);
                    break;
            case 2: forget(head);
                    break;
            case 3: findrank(head);
                    break;
        }
    }

    return 0;
}