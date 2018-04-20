#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

string table[4097];
string op;

int main()
{   
    for (int i = 0; i <= 25; i++)
    {
        table[i].push_back(i+65);
    }

    for (int i = 26; i <= 51; i++)
    {
        table[i].push_back(i+71);
    }

    for (int i = 52; i <= 61; i++)
    {
        table[i].push_back(i-4);
    }
    
    table[62].push_back(' ');
    table[63].push_back(';');
    
    int x;
    int y = 64;                      // y is the position of table index

    while(1)
    {   
        string prev = "";
        string curr = "";
        string tabentry = "";   // A way to check if a file is corrupted can be to check if tabentry is already present in the table.


        cin >> x;


        if (x >= 64)
        {
           cout << "Archive is corrupted!";
            exit(0);
        }

        if (x == -1)
        {
            exit(0);
        }
        
        if (x == 63)        // UNNECESSARY for valid file
        {
            continue;
        }

        prev += table[x];
        op += table[x];
         

        while (1)
        {
            cin >> x;

            if (x >= y)
            {
                cout << "Archive is corrupted!";
                exit(0);
            }

            if (x == -1)
            {
                cout << op;
                return 0;   // check this
            }

            if (x == 63)
            {
                y = 64;
                break;
            }
            
            
            op += table[x];
            prev.push_back(table[x][0]);

            /*for (int i = 0; i < y; i++)
            {
                if (!table[i].compare(prev))
                {
                    cout << "Archive is corrupted!";
                    exit(0);
                }
            }*/

            table[y] = prev;
            y++;
            prev = table[x];
            
        }
    }

    return 0;
}

//abcababad
// 0
// 1
// 2
// 64
// 67
// 3   