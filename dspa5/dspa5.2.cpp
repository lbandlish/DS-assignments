#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <limits>

using namespace std;

typedef struct block{
    int p;      //parent
    int d;      //distance from 0
} blk;

void FindShortestRoute(vector < vector <int> > &Adj, int n);

int main()
{
    int n, m;
    cin >> n >> m;

    int v1, v2, l;

    vector < vector <int> > Adj(n, vector<int> (n,0));  
    // all entries in Adj Matrix are 0 (including self and non-connected)

    for (int i = 0; i < m; i++)
    {
        cin >> v1 >> v2 >> l;
        Adj[v1][v2] = l;
        Adj[v2][v1] = l;
    }

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << Adj[i][j] << " ";
    //     }

    //     cout << endl;
    // }

    FindShortestRoute(Adj,n);
}

void FindShortestRoute(vector < vector <int> > &Adj, int n){
    vector <struct block> blkstat(n);
    // int flag = 0;

    blkstat[0].p = -1;
    blkstat[0].d = 0;

    for (int i = 1; i < n; i++)
    {
        blkstat[i].p = -1;
        blkstat[i].d = numeric_limits<int>::max();

    }

    vector <int> S, Q;

    S.push_back(0);
    int u = 0;
    
    for (int i = 1; i < n; i++)
    {
        Q.push_back(i);
    }

    while (1)
    {
        for (int i = 0; i < n; i++)
        {
            if (Adj[u][i] != 0)
            {
                if (blkstat[i].d > blkstat[u].d + Adj[u][i])
                {
                    blkstat[i].d = blkstat[u].d + Adj[u][i];
                    blkstat[i].p = u;
                } 
            }
        }

        int min = numeric_limits<int>::max();

        int mini = -1;

        for (vector<int>::iterator itr = Q.begin(); itr != Q.end(); ++itr)
        {
            int it = (int)*itr;

            if (blkstat[it].d < min)
            {
                min = blkstat[it].d;
                mini = it;
                u = mini;
            }
        }

    // if (flag < 3)
    // {
    //     for (int i = 0; i < n; i++)
    //     {
    //         cout << blkstat[i].p << "," << blkstat[i].d << " ";
    //     }

    //     cout << endl << endl;
    // }

        if (mini == n-1)
        {
            cout << min << endl;
            exit(0);
        }

        if (mini == -1)
        {
            cout << -1 << endl;
            exit(0);
        }

        // flag++;

        S.push_back(mini);
        
        for (int i = 0; i < n; i++)
        {
            if (Q[i] == mini)
            {
                Q.erase(Q.begin() + i);
            }
        }
    }
}