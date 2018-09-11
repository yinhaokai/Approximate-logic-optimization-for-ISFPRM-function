#include "header.h"
void 	generation1(struct individual *oldpop,struct individual *newpop,int popsize,int VarNumber,int pcross,struct convt_int *convert_head,struct disrelation *dis_pt,int *plarity,int Num_outs,int chrom_Number)
{
	double end;
	double start = 0, finish = 0;
	start = clock();
	int mate1, mate2, jcross, j = 0;
	double totalfitness;
	int i;
	int P_FPRM;
	int mutted1,mutted2;


	/*  ÿ������ǰ����Ԥѡ */
	totalfitness=0.0;


	/* ѡ��, ����, ���� */
	do
	{
		/* ��ѡ������� */
		mate1 = select(oldpop,popsize,totalfitness);
		mate2 = select(oldpop,popsize,totalfitness);

		/* ����ͱ��죬jcross=0 ��ʾû�н��н��� */
		jcross = crossover(oldpop[mate1].chrom, oldpop[mate2].chrom, newpop[j].chrom, newpop[j+1].chrom, pcross,chrom_Number);

		/*mutted1,2=0��ʾ��û�н��б��� */
		mutted1=mutation(newpop[j].chrom,chrom_Number);
		mutted2=mutation(newpop[j+1].chrom,chrom_Number);
		/* ����, ������Ӧ�� */
		if ((jcross!=0) || (mutted1 !=0) || (mutted2 !=0))
		{
			P_FPRM=fitness_compute( newpop[j].chrom,convert_head,dis_pt,plarity,VarNumber,Num_outs,chrom_Number);
			newpop[j].P_of_FPRM=P_FPRM;
			newpop[j].fitness=1.0/P_FPRM;
		}
		else //����û�з�������ͱ��죬����fitness���ֲ���
		{
			newpop[j].P_of_FPRM=oldpop[mate1].P_of_FPRM;
			newpop[j].fitness=oldpop[mate1].fitness;
		}

		/*��¼���ӹ�ϵ�ͽ���λ�� */
		newpop[j].parent[0] = mate1+1;
		newpop[j].xsite = jcross;
		newpop[j].parent[1] = mate2+1;

		if ((jcross!=0) || (mutted2 !=0 ) || (mutted2 !=0))
		{
			P_FPRM=fitness_compute(newpop[j+1].chrom,convert_head,dis_pt,plarity,VarNumber,Num_outs,chrom_Number);
			newpop[j+1].P_of_FPRM=P_FPRM;
			newpop[j+1].fitness=1.0/P_FPRM;
		}
		else //����û�з�������ͱ��죬����fitness���ֲ���
		{
			newpop[j+1].P_of_FPRM=oldpop[mate2].P_of_FPRM;
			newpop[j+1].fitness=oldpop[mate2].fitness;

		}

		newpop[j+1].parent[0] = mate1+1;
		newpop[j+1].xsite = jcross;
		newpop[j+1].parent[1] = mate2+1;
		j = j + 2;
	}
	while(j < (popsize-1));

}