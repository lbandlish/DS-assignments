#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>

using namespace std;


struct Node{
    string word;
    int nodes_below;
    int height;
    struct Node * left;
    struct Node * right;
    struct Node * parent;//TODO: check if redundant
};
typedef struct Node NODE;

NODE * create_node(string word)
{
    NODE * p = (NODE *) malloc(sizeof(NODE));
    p -> left = NULL;
    p -> parent = NULL;
    p -> right = NULL;
    p -> height = 0;
    p -> nodes_below = 0;
    p -> word = word;
    return p;
}

int max(int a, int b)
{
    if(a > b) return a;
    else return b;
}

int height(NODE * node)
{
    if(node == NULL)
    {
        return -1;
    }
    else return node -> height;
}

int balance_factor(NODE * node)
{
    if(node == NULL) return 0;
    return height(node -> right) - height(node -> left);
}

int is_left_child(NODE *node)
{
    if(node -> parent -> left == node)
        return 1;
    return 0;
}

int nodes_below(NODE * node)
{
    if(node == NULL) 
        return -1;
    return node -> nodes_below;
}

NODE * RR_Rotation(NODE * node)
//initial: bf of node = -2; left = -1
//final: node = 0; left = 0;?????not necessary
{
    NODE *Left = node -> left;
    if(node -> parent == NULL);
    else if (is_left_child(node))
    {
        node -> parent -> left = Left;
    }
    else if(is_left_child(node) == 0)
    {
        node -> parent -> right = Left;
    }
    Left -> parent = node -> parent;
    node -> left = Left -> right;
    if (Left -> right)
        Left -> right -> parent = node;
    Left -> right = node;
    node -> parent = Left;
    node -> nodes_below = 1 + nodes_below(node -> left) + 1 + nodes_below(node -> right); 
    Left -> nodes_below = 1 + nodes_below(Left -> left) + 1 + nodes_below(Left -> right);
    node -> height = height(node);
    Left -> height = height(Left);
    return Left;
}

NODE * LL_Rotation(NODE * node)
{
    NODE *Right = node -> right;
    if(node -> parent == NULL);
    else if (is_left_child(node))
    {
        node -> parent -> left = Right;
    }
    else if(is_left_child(node) == 0)
    {
        node -> parent -> right = Right;
    }
    Right -> parent = node -> parent;
    node -> right = Right -> left;
    if(Right -> left)
        Right -> left -> parent = node;
    Right -> left = node;
    node -> parent = Right;
    node -> nodes_below = 1 + nodes_below(node -> left) + 1 + nodes_below(node -> right); 
    Right -> nodes_below = 1 + nodes_below(Right -> left) + 1 + nodes_below(Right -> right);
    node -> height = height(node);
    Right -> height = height(Right);
    return Right;
}

NODE * RR_Rotate(NODE * node)
{
    NODE * temp_node = RR_Rotation(node);
    return temp_node;
}

NODE * LL_Rotate(NODE * node)
{
    NODE * temp_node = LL_Rotation(node);
    return temp_node;
}

NODE * RL_Rotate(NODE * node)
{
    NODE *temp = RR_Rotation(node -> right);
    temp =  LL_Rotation(node);
    return temp;
}

NODE * LR_Rotate(NODE * node)
{
    NODE * temp = LL_Rotation(node -> left);
    temp = RR_Rotation(node);
    return temp;
}

NODE * insert(NODE *node, string new_word)
{
    if(node == NULL)
    {
        node = create_node(new_word);
        return node;
    }
    NODE *new_node;
    node -> nodes_below++;
    if(new_word < node -> word)
    {
        if(node -> left == NULL)
        {
            node -> left = create_node(new_word);
            node -> left -> parent = node;
            new_node = node -> left;
        }
        else
        {
            new_node =  insert(node -> left, new_word);
            if(balance_factor(node) == -2)
            {
                if(new_word < node -> left -> word)
                {
                    RR_Rotate(node);
                }
                else 
                {
                    LR_Rotate(node);
                }
            }
        }
    }
    else
    {
        if(node -> right == NULL)
        {
            node -> right = create_node(new_word);
            node -> right -> parent = node;
            new_node = node -> right;
        }
        else
        {
            new_node = insert(node -> right, new_word);
            if(balance_factor(node) == 2)//in calculating balance factor we use updated values of heights of children
            {
                if(new_word > node -> right -> word)
                {
                    LL_Rotate(node);
                }
                else 
                {
                    RL_Rotate(node);
                }
            }
        }
    }
    node -> height = max(height(node -> left), height(node -> right)) + 1;//if leaf node then -1 + 1
    return new_node;
}

int find_rank(string word, NODE *head)
{
    int count = 0;
    NODE *node = head;
    while(node -> word != word)
    {
        if(word > node -> word)
        {
            if(node -> left != NULL)
                count += (node -> left -> nodes_below + 1);
            count++;
            node = node -> right;
        }
        else
        {
            node = node -> left;
        }
    }
    if(node -> left != NULL)
        count += (node -> left -> nodes_below + 1);
    return count + 1;//rank = count + 1
}

NODE * forget_word(string word, NODE *node)//returns NULL if node node exists else returns root of the subtree
{
    node -> nodes_below--;
    NODE *temp = node;
    if(node == NULL)
    {
        //ERROR....
        return node;
    }
    if(word < node -> word)
    {
        node -> left = forget_word(word, node -> left);//update node -> left in case due to rotations its subtree's root changes
    }
    else if(word > node -> word)
    {
        node -> right = forget_word(word, node -> right);
    }
    else
    {
        if(node -> left == NULL && node -> right == NULL)
        {
            if (node -> parent == NULL) return NULL;// CHeck... TODO.......
            if (node == node -> parent -> right)
            {
                node -> parent -> right = NULL;
                //free node
            }
            else
            {
                node -> parent -> left = NULL;
                //free node
            }
            return NULL;
        }
        else if(node -> left == NULL)
        {
            //if(node == head)
            if(node -> parent == NULL)
            {
                node -> right -> parent = NULL;
                //return node -> right;
            }
            else if (node == node -> parent -> right)
            {
                node -> parent -> right = node -> right;
                node -> right -> parent = node -> parent;
                //free node
            }
            else
            {
                node -> parent -> left = node -> right;
                node -> right -> parent = node -> parent;
                //free node
            }
            return node -> right;//free after this
        }
        else if(node -> right == NULL)
        {
            //if(node == head)
            if(node -> parent == NULL)
            {
                node -> left -> parent = NULL;
                //return node -> left;
            }
            if (node == node -> parent -> right)
            {
                node -> parent -> right = node -> left;
                node -> left -> parent = node -> parent;
                //free node
            }
            else
            {
                node -> parent -> left = node -> left;
                node -> left -> parent = node -> parent;
                //free node
            }
            return node -> left;
        }
        else
        {
            NODE *pred = node -> left;
            while(pred -> right != NULL)
            {
                // pred -> nodes_below--;
                pred = pred -> right;
            }
            node -> word = pred -> word;
            node -> left = forget_word(pred -> word, node -> left);//TODO case when no children of predecessor etc.. teturn values check
        }
    }
    if(balance_factor(node) == -2)
    {
        if(balance_factor(node -> left) <= 0)
        {
            temp = RR_Rotate(node);
        }
        else 
        {
            temp = LR_Rotate(node);
        }
    }
    else if(balance_factor(node) == 2)
    {
        if(balance_factor(node -> right) >= 0)
        {
            temp = LL_Rotate(node);
        }
        else 
        {
            temp = RL_Rotate(node);
        }
    }
    node -> height = max(height(node -> left), height(node -> right)) + 1;//if leaf node then -1 + 1
    return temp;

}

void print_bst(NODE *node)
{
    cout << node -> word << " balance_factor: " << balance_factor(node) << " nodes nodes_below = " << node -> nodes_below <<endl;
    if(node -> left != NULL)
    {
        cout << "l ";
        print_bst(node -> left);
    }
    if(node -> right != NULL)
    {
        cout << "r ";
        print_bst(node -> right);
    }
}

int main()
{
    int q;
    string s1, s2;
    cin >> q;
    NODE *bst = NULL; 
    NODE *node = NULL;
    while(q--)
    {
        cin >> s1;
        if(s1[0] == 'l')
        {
            cin >> s2;
            if(bst == NULL)
            {
                bst = insert(bst, s2);
            }
            else
            {
                node = insert(bst, s2);
                //update root
                while(node -> parent)
                {
                    node = node -> parent;
                }
                bst = node;
            }
        }
        if(s1 == "forget")
        {
            cin >> s2;
            cout << find_rank(s2, bst) << endl;
            node = forget_word(s2, bst);
            if(node == NULL)
            {
                bst = NULL;
                continue;
            }
            while(node -> parent)
            {
                node = node -> parent;
            }
            bst = node;
        }
        if(s1 == "findrank")
        {
            cin >> s2;
            cout << find_rank(s2, bst)<<endl;
        }
        // print_bst(bst);
    }

    return 0;
}
