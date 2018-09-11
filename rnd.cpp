#include "header.h"

int rnd(int low,int high)           /*在整数low和high之间产生一个随机整数*/
{
	int i;
	//float randomperc();
	//	srand((unsigned)time(NULL));
	if(low >= high)
		i = low;
	else
	{
		i=(int)(((rand()/(1.0*RAND_MAX))*(high - low + 1))+ low);//产生一个介于[low,high]的整数
		//	i = (randomperc() * (high - low + 1)) + low;
		if(i > high) i = high;
	}
	return(i);
}