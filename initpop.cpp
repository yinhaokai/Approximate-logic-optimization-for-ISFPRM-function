#include "header.h"

void initpop(struct individual *oldpop, int Varnumber, int popsize)           /* �����ʼ����Ⱥ */
{
	int j, k;
	for(j = 0; j < popsize; j++)
	{
		for(k = 0; k < Varnumber; k++)
		{
			oldpop[j].chrom[k] = 0;
			if(flip(50))
				oldpop[j].chrom[k] = 1;

		}
		oldpop[j].parent[0] = 0;     /* ��ʼ��������Ϣ */
		oldpop[j].parent[1] = 0;
		oldpop[j].xsite = 0;
	//	oldpop[j].fitness_need = 1;

		//		objfunc(&(oldpop[j]));       /* �����ʼ��Ӧ��*/
	}
}