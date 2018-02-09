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
        printf("error\n";)
    }
}

void swap(char* &c1, char* &c2)
{
    char* temp = c1;
    c1 = c2;
    c2 = temp;
}

void learn(vector <char[11]> &dic)
{
    int index = dic.size();

    char* c = (char*)malloc(11*sizeof(char));
    scanf("%s", c);
    dic.push_back(c);


    while(index > 1)
    {
        if (strcmp(dic[index],dic[index/2]) < 0)
        {
            swap(dic[index], dic[index/2]);
        }

        index = index/2;
    }
}

void report(vector <char[11]> &dic)
{
    cout << dic[1] << endl;
}

void forget(vector <char[11]> &dic)
{
    cout << dic[1] << endl;

    dic[1] = dic[dic.size() - 1];
    dic.resize(dic.size() - 1);

    int index = 1;

    int size = dic.size();

    while(index < size)
    {
        if (strcmp(dic[index], dic[index*2]) > 0 || strcmp(dic[index], dic[index*2 + 1]) > 0)
        {
            if (strcmp(dic[index*2],dic[index*2 + 1]) < 0)
            {
                swap(dic[index], dic[index*2]);
            }

            else
            {
                swap(dic[index], dic[index*2 + 1]);
            }
        }
    }
}

int main()
{
    char cmd[15];

    int q = 0;
    scanf("%d", &q);

    for (int i = 0; i < q; i++)
    {
        vector <char[11]> dic;
        char foo[11] = "1111111111\0"
        
        dic.push_back(foo)
        
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
}