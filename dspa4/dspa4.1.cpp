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
    int des;    // no. of descendants + 1
    int ht;     // height of node
} node;
 
void printInorder(node* node)
{
     if (node == NULL)
          return;
 
     /* first recur on left child */
     printf("%s:\n", node->word);
     
     if (node->left != NULL)
     {
         printf("l- %s ", (node->left)->word);
     }
     
     if (node->right != NULL)
     {
         printf("r- %s ", (node->right)->word);
     }

     printf("\n");

     printInorder(node->left);
     printInorder(node->right);

     printf("\n");
}

int find_diff(node* head);
void balance_tree(node* &head, char* c);
int max(int a, int b);
int find_height(node* curr);
void insert_node(node* &curr, node* n);
int interpret (char* cmd);
void swap(node &n1, node &n2);
void learn(node* &head);
void findrank(node* &head, int flag, char* word);
void forget(node* &head);
node* right_rotate(node* head);
node* left_rotate(node* head);
node* double_left_rotate(node* head);
node* double_right_rotate(node* head);
node* delete_node(node* curr, node* prev, char dir, char* c);
node* delete_curr(node* lchild, node* par, node* &curr);


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
            case 3: findrank(head, 0, NULL);
                    break;
        }


        // printf("%s is head\n", head->word);
        printInorder(head);
        printf("\n");
    }
 
    return 0;
}

int find_diff(node* head)
{
    if (head->left == NULL)
    {
        if (head->right == NULL)
        {
            return 0;
        }
        
        else
        {
            return -1 - (head->right)->ht;
        }
    }

    else if (head->right == NULL)
    {
        return (head->left)->ht + 1;
    }

    else
    {
        return (head->left)->ht - (head->right)->ht;
    }

}

void balance_tree(node* &head, char* c)
{
    if (head == NULL)
    {
        return;
    }

    if (strcmp(c,head->word) < 0)
    {
        balance_tree(head->left, c);
    }

    else if (strcmp(c,head->word) > 0)
    {
        balance_tree(head->right, c);
    }

    else
    {
        return;
    }

    int hdiff = find_diff(head);

    // if (strcmp(head->word, "moslslslsl") == 0)
    // {
    //     printf("%d is hdiff\n", hdiff);
    // }

    if (hdiff == 0 || hdiff == 1 || hdiff == -1)
    {
        return;
    }

    else
    {
        if (hdiff == 2)
        {
            if (find_diff(head->left) >= 0)
            {
                head = right_rotate(head);
            }

            else
            {
                head = double_right_rotate(head);
            }
        }

        else if (hdiff == -2)
        {
            if (find_diff(head->right) <= 0)
            {
                head = left_rotate(head);
            }

            else
            {
                head = double_left_rotate(head);
            }
        }

        else
        {
            printf("hdiff out of bound\n (balance_tree function)");
        }
    }
}

int max(int a, int b)
{
    if (a<b)
    {
        return b;
    }

    else return a;
}

int find_height(node* curr)
{
    if (curr->left == NULL && curr->right == NULL)
    {
        return 0;
    }

    else if (curr->left == NULL)
    {
        return (curr->right)->ht + 1;
    }

    else if (curr->right == NULL)
    {
        return (curr->left)->ht + 1;
    }

    else
    {
        return max( (curr->left)->ht, (curr->right)->ht ) + 1;
    }
}

/*
 *possibility that copies of pointers
 *are being assigned values that should be
 *assigned to original pointers.
 */
void insert_node(node* &curr, node* n) 
{
    if (curr == NULL)
    {
        curr = n;
        return;
    }
 
    else 
    {
        if (strcmp(n->word, curr->word) < 0)
        {
            curr->des++;
            insert_node(curr->left, n);
        }

        else if (strcmp(n->word, curr->word) > 0)
        {
            curr->des++;
            insert_node(curr->right, n);
        }

        else
        {
            return;
        }

        curr->ht = find_height(curr);
    }
}
 
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
    n->ht = 0;  //ed
 
 
    if (head == NULL)
    {
        head = n;
    }
 
    else 
    {   
        node* curr = head;

        if (strcmp(n->word,curr->word) < 0)
        {
            curr->des++;
            insert_node(curr->left, n);
            
        }

        else if (strcmp(n->word, curr->word) > 0)
        {
            curr->des++;
            insert_node(curr->right, n);
        }

        else
        {
            return;
        }

        curr->ht = find_height(curr);        
    }
 
    balance_tree(head, n->word);

}
 
 
void findrank(node* &head, int flag, char* word)
{
    char* c;
 
    if (flag == 0)
    {
        c = (char*)malloc(11*sizeof(char));
        cin >> c;
    }
 
    else
    {
        c = word;
    }
 
    node* curr = head;
    int rank = 0;
 
    while(1)
    {
        if (strcmp(c, curr->word) < 0)
        {
            // printf("%s\n", curr->word);
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
            // printf("hey\n");
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
 
 
void forget(node* &head)
{
    char*c = (char*)malloc(11*sizeof(char));
 
    cin >> c;
    node* curr = head;
    node* prev = head;
    char dir;

    findrank(head, 1, c);

    head = delete_node(head, NULL, 'l', c);
    
    balance_tree(head, c);
 
    /*if (strcmp(c, head->word) == 0)
    {
        if (head->left != NULL)
        {
            printf("%d\n", (curr->left->des) + 1);
        }
    
        else
        {
            printf("1\n");
        }   
 
        if (head->left == NULL)
        {
            head = head->right;
        }
 
        else if (head->right == NULL)
        {
            head = head->left;
        }
 
        else
        {
            node* lchild = head->left;
                                
            if (lchild->right == NULL)
            {
                lchild->right = head->right;
                lchild->des = head->des - 1;
                
                head = lchild;
            }
 
            else
            {
                node* par;
 
                while (lchild->right != NULL)
                {
                    par = lchild;
                    lchild->des--;
                    lchild = lchild->right;
                }
 
                par->right = lchild->left;
 
                lchild->des = head->des - 1;   //check this
                lchild->left = head->left;
                lchild->right = head->right;
 
                head = lchild;
            }
        }
    }
 
 
    else
    {
        findrank(head, 1, c);
 
 

        /*while(1)    //chance of forever loop.
        {
            if (strcmp(c, curr->word) < 0)      //there is scope of saving time by calculating strcmp and saving it in variable.
            {
                dir = 'l';
                curr->des--;
                prev = curr;
                curr = curr->left;
            }
 
            else if (strcmp(c, curr->word) > 0)
            {
 
                dir = 'r';
                curr->des--;
                prev = curr;
                curr = curr->right;
            }
 
            else
            {
                if (curr->left == NULL)
                {
                    if (dir == 'l')
                    {
                        prev->left = curr->right;
                    }
 
                    else
                    {
                        prev->right = curr->right;
                    }
                }
 
                else if (curr->right == NULL)
                {
                    if (dir == 'l')
                    {
                        prev->left = curr->left;
                    }
 
                    else
                    {
                        prev->right = curr->left;
                    }
                }
 
                else
                {
                    node* lchild = curr->left;  
                    
                    if (lchild->right == NULL)
                    {
                        lchild->right = curr->right;
                        lchild->des = curr->des - 1;
                        
                        if (dir == 'l')
                        {
                            prev->left = lchild;
                        }
 
                        else
                        {
                            prev->right = lchild;
                        }
 
                    }
 
                    else
                    {
                        node* par;
 
                        while (lchild->right != NULL)
                        {
                            par = lchild;
                            lchild->des--;
                            lchild = lchild->right;
                        }
 
                        par->right = lchild->left;
 
                        lchild->des = curr->des - 1;   //check this
                        lchild->left = curr->left;
                        lchild->right = curr->right;
 
                        if (dir == 'l')
                        {
                            prev->left = lchild;
                        }
 
                        else
                        {
                            prev->right = lchild;
                        }
                    }
 
                }
 
                break;
            }
 
        }
    }*/  
}

node* right_rotate(node* head)
{
    node* temp = head->left;
    head->left = temp->right;
    temp->right = head;

    //setting the heights correctly

    head->ht = find_height(head);
    temp->ht = find_height(temp);

    //setting the des values

    if (head->left == NULL)
    {
        if (head->right == NULL)
        {
            head->des = 1;
        }

        else
        {
            head->des = (head->right)->des + 1;
        }
    }

    else if (head->right == NULL)
    {
        head->des = (head->left)->des + 1;
    }

    else
    {
        head->des = (head->left)->des + (head->right)->des + 1; 
    }

    if (temp->left == NULL)
    {
        temp->des = head->des + 1;
    }

    else
    {
        temp->des = head->des + (temp->left)->des + 1;
    }


    if (head->des != (temp->right)->des)//to be removed
    {
        printf("head->des != (temp->right)->des\n");
    }

    return temp;
}

node* left_rotate(node* head)
{
    node* temp = head->right;
    head->right = temp->left;
    temp->left = head;
    //temp is the actual head, not head


    //setting the heights correctly

    head->ht = find_height(head);
    temp->ht = find_height(temp);

    //setting the des values

    if (head->right == NULL)
    {
        if (head->left == NULL)
        {
            head->des = 1;
        }

        else
        {
            head->des = (head->left)->des + 1;
        }
    }

    else if (head->left == NULL)
    {
        head->des = (head->right)->des + 1;
    }

    else
    {
        head->des = (head->right)->des + (head->left)->des + 1; 
    }

    if (temp->right == NULL)
    {
        temp->des = head->des + 1;
    }

    else
    {
        temp->des = head->des + (temp->right)->des + 1;
    }


    if (head->des != (temp->left)->des)//to be removed
    {
        printf("head->des != (temp->left)->des\n");
    }

    return temp;
}

node* double_left_rotate(node* head)
{
    head->right = right_rotate(head->right);
    head = left_rotate(head);

    return head;
}

node* double_right_rotate(node* head)
{
    head->left = left_rotate(head->left);
    head = right_rotate(head);

    return head;
}

node* delete_node(node* curr, node* prev, char dir, char* c) //dir and prev unnecessary
{
    if (strcmp(c, curr->word) < 0)
    {
        curr->left = delete_node(curr->left, curr, 'l', c);
        curr->ht = find_height(curr);

        return curr;
    }

    else if (strcmp(c, curr->word) > 0)
    {
        curr->right = delete_node(curr->right, curr, 'r', c);
        curr->ht = find_height(curr);

        return curr;
    }

    else
    {
        if (curr->left == NULL)
        {
            return curr->right;
        }

        else if (curr->right == NULL)
        {
            return curr->left;
        }

        node* lchild = curr->left;

        if (lchild->right == NULL)
        {
            lchild->right = curr->right;
            lchild->des = curr->des - 1;
            lchild->ht = find_height(lchild);

            return lchild;
        }

        else
        {
            // node* par;

            // while (lchild->right != NULL)
            // {
            //     par = lchild;
            //     lchild->des--;
            //     lchild = lchild->right;
            // }

            return delete_curr(lchild, curr, curr);

            // par->right = lchild->left;
        }
    }
}

node* delete_curr(node* lchild, node* par, node* &curr)
{
    if (lchild->right != NULL)
    {
        lchild->des--;
        lchild->right = delete_curr(lchild->right, lchild, curr);
        lchild->ht = find_height(lchild);
    }

    else
    {
        node* returnval = lchild->left; //can returnn lchild instead of this.

        lchild->des = curr->des - 1;
        lchild->left = curr->left;
        lchild->right = curr->right;

        curr = lchild;

        return returnval;
    }
}