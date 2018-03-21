#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
using namespace std;

typedef struct node {
    char* word;
    struct node* next;
    int freq;
} htnode;

int mfreq = 1;      //maxfrequency
int mfreqid = 1;    //index of maxfrequency no.

int find_hash(char* word, int n)
{
    int rv; //return value

    unsigned long h = 5381;
    int ch;

    while (ch = *word++)
    {
        h = ((h << 5) + h) + ch;
    }

    rv = h % n;

    return rv;
}

void check_max(int freq, int index)
{
    if (freq > mfreq)
    {
        if (freq != mfreq + 1)
        {
            printf("freq is %d, and mfreq is %d", freq, mfreq);
            printf("freq != mfreq + 1 but freq > mfreq\n");
        }

        mfreq = freq;
        mfreqid = index;
    }
}

// all nodes at mfreqid must be compared.

htnode** create_ht(int n)
{
    htnode** ht = (htnode**)malloc(n * sizeof(htnode*));
    return ht;
}

void insert(htnode** ht, char* ch, int rv)
{
    htnode* newnode =(htnode*)malloc(sizeof(htnode));
    newnode->freq = 1;
    newnode->word = ch;
    newnode->next = ht[rv];
    ht[rv] = newnode;
}

int search_and_update(htnode** ht, char* ch, int rv)
{
    htnode* curr = ht[rv];

    while(curr != NULL)
    {
        if (strcmp(curr->word,ch) == 0)
        {
            curr->freq++;

            check_max(curr->freq, rv);

            return 1;
        }

        curr = curr->next;
    }

    return 0;
}

void insert_in_ht(htnode** ht, int n)
{
    char* ch = (char*)malloc(100 * sizeof(char));
    scanf("%s", ch);

    int rv = find_hash(ch, n);

    if (search_and_update(ht, ch, rv) == 0)
    {
        insert(ht, ch, rv);
    }
}

void find_and_print_fav(htnode** ht)
{
    htnode* mptr = ht[mfreqid];
    htnode* curr = mptr;

    while (curr != NULL)
    {
        if (curr->freq > mptr->freq)
        {
            mptr = curr;
        }

        curr = curr->next;
    }
    
    printf("%s\n", mptr->word);

}

int main()
{
    int n;
    scanf("%d", &n);

    if (n == 1)
    {
        char *ch = (char*)malloc(100 * sizeof(char));
        scanf("%s", ch);
        printf("%s\n", ch);
    }

    htnode** ht = create_ht(n);

    for (int i = 0; i < n; i++)
    {
        ht[i] = NULL;
    }

    for (int i = 0; i < n; i++)
    {
        insert_in_ht(ht, n);
    }

    find_and_print_fav(ht);
    // max need to be compared. printf("%s\n", ht[mfreqid]->word);
}