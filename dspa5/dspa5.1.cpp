#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

void makeNetwork(vector <int>* v, int n);
void addnode(vector <int>* v, int n);
void delnode(vector <int>* v, int n);
void addlink(vector <int>* v, int n);
void remlink(vector <int>* v, int n);


int main()
{
    int n, nop;
    cin >> n >> nop;

    n = n + 1; // so that everything can be 1 indexed.

    vector <int> v[n];
    
    for (int i = 0; i < nop; i++)
    {
        makeNetwork(v,n);
    }

    int k;
    cin >> k;

    int q;

    for (int i = 0; i < k; i++)
    {
        cin >> q;
        if (v[q].empty())
        {
            cout << "not in network" << endl;
        }

        else if (v[q].size() == 1)
        {
            cout << "no connections" << endl;
        }

        else
        {
            for (int j = 1; j < v[q].size(); j++)
            {
                cout << v[q][j] << " ";
            }
            
            cout << endl;
        }
    }
}


void makeNetwork(vector <int>* v, int n)
{
    char ins[8];
    cin >> ins;

    if (strcmp(ins,"addnode") == 0)
    {
        addnode(v, n);
    }

    else if (strcmp(ins, "delnode") == 0)
    {
        delnode(v,n);
    }

    else if (strcmp(ins, "addlink") == 0)
    {
        addlink(v,n);
    }   

    else if (strcmp(ins, "remlink") == 0)
    {
        remlink(v,n);
    }

}

void addnode(vector <int>* v, int n)
{
    int x;
    cin >> x;

    //if (!v(x).empty)
    //cout << "v(x) not empty during addnode" << endl;

    v[x].push_back(0);
}

void delnode(vector <int>* v, int n)
{
    int x;
    cin >> x;

    v[x].clear();

    for (int i = 1; i < n; i++)
    {
        int size = v[i].size();

        for (int j = 1; j < size; j++)
        {
            if (v[i][j] == x)
            {
                v[i].erase(v[i].begin() + j);
                // remove v[i][j] from v[i]
                j--;
                size--;
            }
        }
    }
}

void addlink(vector <int>* v, int n)
{
    int x,y;
    cin >> x >> y;

    v[x].push_back(y);
    v[y].push_back(x);

}

void remlink(vector <int>* v, int n)
{
    int x,y;
    cin >> x >> y;

    int size1 = v[x].size();
    int size2 = v[y].size();

    for (int i = 1; i < size1; i++)
    {
        if (v[x][i] == y)
        {
            v[x].erase(v[x].begin() + i);
            //remove v[x][i] from v[x];
            i--;
            size1--;
        }
    }

    for (int i = 0; i < size2; i++)
    {
        if (v[y][i] == x)
        {
            v[y].erase(v[y].begin() + i);
            //remove v[y][i] from v[y];
            i--;
            size2--;
        }
    }
}
