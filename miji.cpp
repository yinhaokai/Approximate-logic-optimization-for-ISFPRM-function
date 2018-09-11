
#include "header.h"
#include<iostream>
using namespace std;

const int N = 20;//求导阶数
int n_stack[N], r, n , m; //全局变量n_stack[]、r、n、l、svae[]、m
long long int l;

long long int lec(int c, int t)                                  //组合数

{
	long long int i, a[2], s;
	a[0] = 1;
	a[1] = 1;
	for (i = t+1; i <= c; i++)
		a[0] = a[0] * i;
	for (i = 1; i <= c - t; i++)
		a[1] = a[1] * i;
	s = a[0]/a[1];
	return s;
}

void p_stack(int *save)
{
	int i;
	for (i = 0; i<r - 1; i++)
	{
		*(save + l) = n_stack[i]; l++;
	}
	if (n_stack[0] != m - n + 1)
	{
		*(save + l) = n_stack[i]; l++;
	}
	else
	{
		*(save + l) = n_stack[i]; l++;
	}
}
void gen(int *save)
{
	r = 0;
	n_stack[r++] = 1;
	while (1)
	{
		while (r<n)
			n_stack[r++] = n_stack[r - 1] + 1;
		p_stack(save);
		while (n_stack[r - 1]<m)
		{
			n_stack[r - 1]++;
			p_stack(save);
		}
		while (n_stack[r - 1] == m - n + r && r != 0)
			r--;
		if (r == 0) return;
		n_stack[r - 1]++;
	}
}
int **mj(int tar,int res)   //tar表示对几个求幂集，fin是对哪几个求幂集、、flag和res
{
	m = tar;
	l = 0;
	long long int q, i, j, tt = 0, rr = 0;
	long long int  countnum[N];
	memset(n_stack, 0, sizeof(n_stack));
	int *save = (int *)malloc(sizeof(int) *(res/2)*m);
	for (n = 1; n <= m; n++)
		gen(save);
	int **chart = (int **)malloc(sizeof(int*) * res);
	for (i = 1; i <= m; i++)
		countnum[i] = lec(m, i);
	for (i = 0; i<res; i++)
	{
		chart[i] = (int*)malloc(sizeof(int)*m);
		if (chart[i] == NULL) {
			cout << "内存耗尽" << endl;
			exit(1);
		}
		for (j = 0; j < m; j++)
			chart[i][j] = 0;
	}
	for (q = 1; q <= m; q++)
	{
		for (i = rr; i<countnum[q] + rr; i++)
		{
			for (j = 0; j<q; j++)
			{
				chart[i][j] = *(save + tt);
				tt++;
			}
		}
		rr = i;
	}

	/*for (int i = 0; i < res; i++){
		for (int j = 0; j < tar; j++)
		{
			printf("%d ", chart[i][j]);
		}
		printf("\n");
	}*/
	free(save);
	save = NULL;
	return chart;
}