#include "header.h"
int select(struct individual *oldpop,int popsize,double sumfitness)                    /* ���̶�ѡ��*/
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
		i = rnd(1,popsize);//����һ������[1,popsize]������
	//i=(int)(rand()*popsize/(1.0*RAND_MAX)+1);//����һ������[1,popsize]������
	return(i-1);
}