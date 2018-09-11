# include "header.h"

int powerof2(int x)   
{
	int res = 1;
	for (int i = 0; i < x; i++)
		res = res * 2;
	return res;
}