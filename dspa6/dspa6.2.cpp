#include <iostream>
#include <stdlib.h>   

using namespace std;

void FindArticulation(int** A, int* B, int* P, int n, int m, int s, int* low, int* time, int* arp, int* visited);
int min(int a, int b)
{
    if (a < b)
    return a;

    else
    return b;
}

int curtime = 0;

int main()
{
    int n, m;
    int x1, x2;
    cin >> n >> m;

    int** A = (int**) calloc(n, sizeof(int*));

    for (int i = 0; i < n; i++)
    {
        A[i] = (int*)calloc(n, sizeof(int));
    }

    for (int i = 0; i < m; i++)
    {
        cin >> x1 >> x2;
        A[x1][x2] = 1;
        A[x2][x1] = 1;
    }

    int* B = (int*) malloc(n*sizeof(int));     //to store the sorted array
    int* P = (int*) malloc(n*sizeof(int));

    for (int i = 0; i < n; i++)
    {
        P[i] = -1;  // -1 means NIL
    }

    int* low = (int*) malloc(n*sizeof(int));
    int* dtime = (int*) malloc(n*sizeof(int));
    int* visited = (int*) calloc(n, sizeof(int));
    int* arp = (int*) calloc(n, sizeof(int));

    // cout << "helllo";
    visited[0] = 1;

    FindArticulation(A, B, P, n, m, 0, low, dtime, arp, visited);

    for (int i = 0; i < n; i++)
    {
        if (arp[i] == 1)
        {
            cout << i << endl;
        }
    }

    // cout << P[0] << "this is ";

    return 0;
}

void FindArticulation (int** A, int* B, int* P, int n, int m, int s, int* low, int* dtime, int* arp, int* visited)
{

    int num_child = 0;

    dtime[s] = curtime;
    curtime++;
    low[s] = dtime[s];

    for (int i = 0; i < n; i++)
    {
        if (A[s][i] == 1)
        {
            if (visited[i] == 0)
            {
                visited[i] = 1;
                num_child++;
                if (i == 0)
                {

                }
                P[i] = s;
                // cout << "hi";
                FindArticulation(A, B, P, n, m, i, low, dtime, arp, visited);
                low[s] = min(low[s], low[i]);

                    if (P[s] == -1)
                    {
                        if (num_child > 1)
                        {   //cout << "hi";
                            arp[s] = 1;
                        }    
                    }

                    else
                    {
                        if (low[i] >= dtime[s])
                        {
                            // cout << "HI";  
                            arp[s] = 1;
                        }
                    }
            }

            else
            {
                if (i != P[s])
                {
                    low[s] = min(low[s], low[i]);
                }
            } 

        }
    }


}