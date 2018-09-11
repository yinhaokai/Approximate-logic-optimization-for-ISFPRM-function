#include "header.h"
int select(struct individual *oldpop,int popsize,double sumfitness)                    /* 轮盘赌选择*/
{
	//	extern float randomperc();
	double sum, pick;
	int i;
	//pick = randomperc();

	//	srand((unsigned)time(NULL));
	pick=(double)rand()/RAND_MAX;

	sum = 0;
	if(sumfitness != 0)
	{
		for(i = 0; (sum < pick) && (i < popsize); i++)
			sum=sum + (oldpop[i].fitness/sumfitness);
	}
	else
		i = rnd(1,popsize);//产生一个介于[1,popsize]的整数
	//i=(int)(rand()*popsize/(1.0*RAND_MAX)+1);//产生一个介于[1,popsize]的整数
	return(i-1);
}