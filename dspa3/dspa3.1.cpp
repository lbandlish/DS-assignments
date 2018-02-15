#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>

using namespace std;

int interpretcmd(char* cmd)
{
    char l[] = "learn";
    char r[] = "reportsmallest";
    char f[] = "forgetsmallest";

    if (strcmp(cmd, l) == 0)
    {
        return 1;    
    }

    else if (strcmp(cmd, r) == 0)
    {
        return 2;
    }

    else if (strcmp(cmd, f) == 0)
    {
        return 3;
    }

    else {
        printf("error\n");
    }
}

void swap(char* &c1, char* &c2)
{
    char* temp = c1;
    c1 = c2;
    c2 = temp;
}

void learn(vector <char*> &dic)
{
    int index = dic.size();

    char* c = (char*)malloc(11*sizeof(char));
    scanf("%s", c);
    dic.push_back(c);
    
    // cout << "size is" << dic.size() << endl;
    while(index > 1)
    {
        // cout << "hey";
        if (strcmp(dic[index],dic[index/2]) < 0)
        {
            // cout << "hi";
            swap(dic[index], dic[index/2]);
            index = index/2;
        }

        else
        {
            break;
        }
    }

    // for (int i = 0; i < dic.size(); i++)
    // {
    //     cout << "value at " << i << " is " << dic[i] << endl;
    // }

    // cout << "input string: " << c << endl;
}

void report(vector <char*> &dic)
{
    cout << dic[1] << endl;
}

void forget(vector <char*> &dic)
{
    cout << dic[1] << endl;
    int finalsize = dic.size() - 1;
    dic[1] = dic[finalsize];
    dic.resize(finalsize);

    int index = 1;

    int size = dic.size() - 1;

    while(index <= size/2)
    {
        if (size == 2*index)
        {
            if (strcmp(dic[index], dic[index*2]) > 0)
            {
                swap(dic[index*2], dic[index]);
                break;
            }

            else
            {
                break;
            }
        }

        if (strcmp(dic[index], dic[index*2]) > 0 || strcmp(dic[index], dic[index*2 + 1]) > 0)
        {
            if (strcmp(dic[index*2],dic[index*2 + 1]) < 0)
            {
                swap(dic[index], dic[index*2]);
                index = index*2;
            }

            else
            {
                swap(dic[index], dic[index*2 + 1]);
                index = index*2 + 1;
            }
        }

        else
        {
            break;
        }
    }


    // for (int i = 1; i < dic.size(); i++)
    // {
    //     cout << "value at " << i << " is " << dic[i][0] << endl;
    // }
}

int main()
{
    char cmd[15];

    int q = 0;
    scanf("%d", &q);

    vector <char*> dic;

    char foo[11] = "1111111111";
    char *bar = foo;
    dic.push_back(bar);

    for (int i = 0; i < q; i++)
    {
        scanf("%s", cmd);
        
        int ip = interpretcmd(cmd);

        switch(ip)
        {
            case 1: learn(dic);
            break;

            case 2: report(dic);
            break;

            case 3: forget(dic);
            break;

        }
    }
    return 0;
}