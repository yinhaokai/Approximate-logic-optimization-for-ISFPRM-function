#include "header.h"

int rnd(int low,int high)           /*������low��high֮�����һ���������*/
{
	int i;
	//float randomperc();
	//	srand((unsigned)time(NULL));
	if(low >= high)
		i = low;
	else
	{
		i=(int)(((rand()/(1.0*RAND_MAX))*(high - low + 1))+ low);//����һ������[low,high]������
		//	i = (randomperc() * (high - low + 1)) + low;
		if(i > high) i = high;
	}
	return(i);
}