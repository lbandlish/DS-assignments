#include<stdio.h>
#include<stdlib.h>

//try input 12345*1234567891

void scaninput();
void singular_multiply(int* arr, int sq, int* c, int flag);
void subtractfordiv(int* c, int n1a);
int* add();
int* divide();
void divide_rec(int* qt, int pos, int n1a);
int find_sq_and_modify_a(int n1a);
int avsb(int* borc, int n1a, int nborc);
void printans(int* ans, int n);
void prepend(int n,int* c);
int* multiply();
void addinplace(int* arr1, int* arr2, int narr1, int narr2);
int max(int n1, int n2);
int* subtract();

int n1,n2;
int* a;
int* b;


int main()
{	
	int t, opc;

	int* a;
	int* b;
	
	//printf("scanning t\n");
	scanf("%d", &t);

	for (int i = 0; i < t; i++)
	{	
		//printf("n1 and n2\n");
		scanf("%d %d", &n1, &n2);
		scaninput();
		
		scanf("%d", &opc);
		int* ans;
		
		//printf("opc\n");
		switch(opc)
		{
			case 1: //printf("Add given\n");
				ans = add();
				//printf("out of add\n");
				printans(ans,max(n1,n2)+1);
				break;
			
			case 2:// printf("Subtract given\n");
				ans = subtract();
				printans(ans,n1);
				break;

			case 3:// printf("Multiply given\n");
				ans = multiply();
				//printf("out of multipy\n");
				printans(ans,n1+n2);
				break;

			case 4:// printf("Hi sandeep\n");
				ans = divide();
				//printf(" bye sandeep\n");
				printans(ans, n1);
				break;	
			//int *qt = (int*)calloc(*sizeof(int)):
		}
		
		
		//free(a);
		//free(b);
	}		
	return 0;
}

void scaninput()
{	
	a = (int*)calloc(n1,sizeof(int));
	b = (int*)calloc(n2,sizeof(int));

	char* s1 = (char*)malloc((n1+1)*sizeof(char));
	char* s2 = (char*)malloc((n2+1)*sizeof(char));

	//printf("s1\n");	
	scanf("%s", s1);
	//printf("s2\n");
	scanf("%s", s2);

	while (n1 != 0)
	{
		if (*s1 == '0')
		{
			s1 = s1 + 1;
			n1 = n1 - 1;
		}
		
		else break;
	}

	while (n2 != 0)
		{
			s2 = s2 + 1;
			n2 = n2 - 1;
		}
	}
	
	for (int i = 0; i < n1; i++)
	{ 
		a[i] = (int)s1[i] - 48;
	}
	
	for (int j = 0;j < n1; j++)
	{
	//	printf("a[%d] is %d\n",j,a[j]);
	}
	for (int i = 0; i < n2; i++)
	{
		b[i] = (int)s2[i] - 48;
	}
}

void printans(int* ans, int n)
{
	//printf("%d %d\n",ans[0],ans[1]);
	char* finalans = (char*)malloc(n*sizeof(char));
	
	int i = 0;
	int j = 0;

	while(ans[i] == 0 && ans[i+1] != -1)
	{
		i++;	
	}	
	
	for(j = 0; i <= n; i++,j++)
	{
		if (ans[i] == -1)
		{
			break;
		}

		finalans[j] = ans[i] + 48;
	}
	
	finalans[j] = '\0';
	printf("%s\n", finalans);
}	
	

/*int* sum(int* a, int* b)
{
}
*/

void singular_multiply(int* arr, int sq, int* c, int flag)
{	
	int j = 0;
	int carry = 0;
	
	if (flag == 1)
	{	
		for (int i = 0; i < n2; i++)
		{

			c[n2-i] = ((arr[n2-i-1] * sq + carry) % 10);
			carry = ((arr[n2-i-1] * sq + carry) / 10);
		}

		c[0] = carry;
	}

	else
	{
		for (int i = 0; i < n1; i++)
		{
			c[n1+n2-1-i] = ((arr[n1-i-1] * sq + carry) % 10);
			carry = ((arr[n1-i-1] * sq + carry) / 10);
		}

		c[n2-1] = carry;
	}

	//printans(c,n1+n1);
}

void subtractfordiv(int* c, int n1a)
{	
	for (int i = 0; i <= n2; i++)
	{
		if(a[n1a-i-1] >= c[n2-i])
		{	
			a[n1a-i-1] = a[n1a-i-1] - c[n2-i];
		}
	
		else
		{
			a[n1a-i-1] = a[n1a-i-1] - c[n2-i] + 10;
			a[n1a-i-2] = a[n1a-i-2] - 1;
		} 
		// review for checking if the biggest place digit is correctly being computed/used
	}		
}			
int* add()
{
	int maxval = max(n1,n2);
	
	int* c = (int*)calloc(maxval+2,sizeof(int));
	
	c[maxval+1] = -1;
	if (maxval == n1)
	{	
		for (int i = 0; i < n1; i++)
		{
		//	printf("Entered if\n");
			c[i+1] = a[i];
		//	printans(c,maxval);
		}

		addinplace(c,b,n1+1,n2);
	}

	else
	{
		for (int i = 0; i < n2; i++)
		{	
		//	printf("Entered else\n");
			c[i+1] = b[i];
		//	printans(c,maxval);
		}
	
		addinplace(c,a,n2+1,n1);
	}
	return c;
}

int* subtract()
{	
	a[n1] = -1;

	for (int i = 0; i < n2; i++)
	{
		a[n1-1-i] = a[n1-1-i] - b[n2-1-i];
		
		if (a[n1-1-i] < 0)
		{
			a[n1-1-i] = a[n1-1-i] + 10;
			a[n1-2-i] = a[n1-2-i] - 1;
		}
	}

	return a;
}
int* divide()
{
	//printf("a[0] is %d\n",a[0]);
	//printf("b[0] is %d\n",b[0]);
	//printf("Entered divide\n");

	int*qt = (int*)calloc(n1,sizeof(int));

	//printf("%d just after entering divide\n",avsb(b,n1,n2));

	if (avsb(b,n1,n2)==-1)	//see if n2>n1 in avsb function for using it here
	{
		qt[0] = 0;
		qt[1] = -1;
		printf("do it\n");
		return qt;
	}
	

	int sq;
	//printf("hi\n");

	if (avsb(b,n2,n2)==0)
	{
	//	printf("avsb(b,n2.n2) == 0\n");
		if (n1==n2)
		{
			qt[0] = 0;
			qt[1] = -1;
			return qt;
		}

		sq = find_sq_and_modify_a(n2+1);
		qt[0] = sq;
		//printf("value of sq is %d\n",sq);
		divide_rec(qt,1,n2+2);
		return qt;
	}
	
	else
	{	
		//printf("avsb(b,n2,n2) == 1\n");
		sq = find_sq_and_modify_a(n2);
		//printf("value of sq is %d\n",sq);
		qt[0] = sq;
		divide_rec(qt,1,n2+1);
		return qt;
	}
}

void divide_rec(int* qt, int pos, int n1a)
{	
	//printf("div_rec has been called\n");
	//printf("a[0] is %d, and a[1] is %d\n",a[0],a[1]);
	if (n1a>n1)
	{
		qt[pos] = -1; //-1 indicates end of quotient
		return;
	}

	if (avsb(b,n1a,n2)==0)
	{
		qt[pos] = 0; //pos-1 needs to be confirmed
		divide_rec(qt,pos+1,n1a+1);
		return;
	}

	else
	{
		int sq = find_sq_and_modify_a(n1a); //single digit quotient sq
		//printf("value of sq is %d\n",sq);
		qt[pos] = sq;
		divide_rec(qt,pos+1,n1a+1);
		return;
	}
}

int* multiply()
{
	int* ans = (int*)calloc(n1+n2+1,sizeof(int));
	int* helper = (int*)calloc(n1+n2+1,sizeof(int));
	
	//remove this helper line and reduce calloc for helper
	helper[n1+n2] = -1;
	ans[n1+n2] = -1;

	singular_multiply(a,b[n2-1],ans,2);
	//printans(ans,n1+n2);

	for (int i = 0; i < n2-1; i++)
	{
		for (int i = 0; i < n1+n2; i++)
		{
			helper[i] = 0;
		}

		singular_multiply(a,b[n2-i-2],helper,2);

		//printans(helper, n1+n2);
		for (int j = 0; j <= i; j++)
		{
			prepend(n1+n2-1,helper);
			//printans(helper,n1+n2);
		}
	
		addinplace(ans,helper,n1+n2,n1+n2);
	}

	//printf("%d is ans[n1+n2]\n",ans[n1+n2-1]);

	return ans;
}

void addinplace(int* arr1, int* arr2, int narr1, int narr2)
{
	int carry = 0;

	for (int i = 0; (i < narr1 && i < narr2); i++)
	{	
		int arr1i = arr1[narr1-1-i];

		arr1[narr1-1-i] = (arr1i + arr2[narr2-1-i] + carry) % 10;		

		carry = (arr1i + arr2[narr2-1-i] + carry) / 10;
	}

	if (narr1 == narr2)
	{
		return;
	}

	else	//in this case narr1 > narr2 always
	{
		arr1[narr1-1-narr2] = arr1[narr1-1-narr2] + carry;
	}
}
		
int find_sq_and_modify_a(int n1a)
{	
	int sq = 0;
	int* c = (int*)calloc((n2+1),sizeof(int));
	int avsbval;

	do
	{	
		sq++;
		singular_multiply(b,sq,c,1);
		
		if (c[0] == 0)
		{
			prepend(n2,c);
			avsbval = avsb(c,n1a,n2);
		}

		else
		{
			avsbval = avsb(c,n1a,n2+1);
		}
	}
	while(avsbval!=0);
	
	sq--;
	
	singular_multiply(b,sq,c,1);
	subtractfordiv(c,n1a);	//define subtract accordingly
	
	return sq;
}

int avsb(int* borc, int n1a, int nborc)

/* 
 * Returns -1 if a < b
 * Returns 0 if a(till n1a) < b
 * Returns 1 if a(till n1a) >= b
 */

{	
			
	if (n1a<nborc)	
	//not sure if n2 should be used for comparison in case of c being passed to avsb
	{
		return -1;
	}
	
	if (n1a>nborc)
	{
		//printf("(inside (n1a>n2))%d is the current value of n1a\n\n", n1a); 
		
		if (a[n1a-nborc-1] != 0)
		{
			return 1;
		}
	}
	
	int i = 0;

	while(i<nborc)
	{
		//printf("%d is the current value of n1a (inside while(i<n2))\n\n",n1a);
		if (a[n1a-nborc+i] > borc[i])
		{
			return 1;
		}

		if (a[n1a-nborc+i] < borc[i])
		{	
	//		printf("n1a - nborc + i is %d",n1a-nborc+i);
	//		printf("The value of i is %d, and a is %d, and borc is %d\n",i, a[n1a-nborc+i],borc[i]);
	//		printf("a is %d, borc is %d\n",a[n1a-nborc+i+1],borc[i+1]);
			return 0;
		}
		
		i++;
	}
	
	return 1;
}

void prepend(int n,int* c)
{
	for (int i = 0; i < n; i++)
	{
		c[i] = c[i+1];
	}

	c[n] = 0;
}

int max(int n1, int n2)
{
	if (n1 > n2)
		return n1;

	else return n2;
}
