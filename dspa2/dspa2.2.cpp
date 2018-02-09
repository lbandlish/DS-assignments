#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void storeinput (vector < pair<int, int> > &v, int n);
void inorder(vector < pair<int, int> > &v, int n, int curr, int parent);


int main()
{
	int t;

	scanf("%d", &t);

	for (int i = 0; i < t; i++)
	{
		int n;
		scanf("%d", &n);

		vector< pair<int, int> > v(n); //v is 1 size bigger than reqd.

		storeinput(v, n);

		inorder(v, n, 1, 0);
		
		v.clear();

		printf("\n");
	}

	return 0;
}

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

void storeinput (vector < pair<int, int> > &v, int n)
{
	int n1, n2;

	for (int i = 0; i < n-1; i++)
	{
		scanf("%d %d", &n1, &n2);
		v[i] = make_pair(n1, n2);
		// printf("%d\n", n1);
		// printf("%d\n", n2);	
	}

}

void inorder(vector < pair<int, int> > &v, int n, int curr, int parent)
{
	vector <int> vcurr;
	
	if (curr == 1)
	{
		for (int i = 0; i < n-1; i++)
		{
			if (v[i].first == 1)
			{
				vcurr.push_back(v[i].second);
			}

			else if (v[i].second == 1)
			{
				vcurr.push_back(v[i].first);
			}
		}
	}


	else
	{
		for (int i = 0; i < n-1; i++)
		{
			if (v[i].first == curr)
			{
				if (v[i].second != parent)
				{
					vcurr.push_back(v[i].second);
				}
			}

			if (v[i].second == curr)
			{
				if (v[i].first != parent)
				{
					vcurr.push_back(v[i].first);
				}
			}
		}
	}

	qsort (vcurr.data(), vcurr.size(), sizeof(int), compare);

	for ( int i = 0; i < (vcurr.size() / 2); i++ )
	{
		inorder(v, n, vcurr[i], curr);
	}

	printf("%d ", curr);

	for (int i = (vcurr.size()/2); i < vcurr.size(); i++)
	{
		inorder(v, n, vcurr[i], curr);
	}

	vcurr.clear();
}