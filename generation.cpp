#include "header.h"

void	generation1(struct individual *oldpop,struct individual *newpop,int popsize,int VarNumber,int pcross,struct convt_int *convert_head)
{

	int mate1, mate2, jcross, j = 0;
	double totalfitness;
	int i;
	int P_FPRM;
	int mutted1,mutted2;

	/*  每代运算前进行预选 */
	totalfitness=0.0;
	for(i=0;i<popsize;i++)
		totalfitness=totalfitness+oldpop[i].fitness;



	/* 选择, 交叉, 变异 */
	do
	{
		/* 挑选交叉配对 */
		mate1 = select(oldpop,popsize,totalfitness);
		mate2 = select(oldpop,popsize,totalfitness);

		/* 交叉和变异，jcross=0 表示没有进行交叉 */
		jcross = crossover(oldpop[mate1].chrom, oldpop[mate2].chrom, newpop[j].chrom, newpop[j+1].chrom, pcross,VarNumber);//交叉的位置

		/*mutted1,2=0表示，没有进行变异 */
		mutted1=mutation(newpop[j].chrom,VarNumber);
		mutted2=mutation(newpop[j+1].chrom,VarNumber);

		/* 解码, 计算适应度 */
		if ((jcross!=0) || (mutted1 !=0) || (mutted2 !=0))
		{
			P_FPRM=fitness_compute(newpop[j].chrom,convert_head,VarNumber);
			newpop[j].P_of_FPRM=P_FPRM;
			newpop[j].fitness=1.0/P_FPRM;
		}
		else //父代没有发生交叉和变异，所以fitness保持不变
		{
			newpop[j].P_of_FPRM=oldpop[mate1].P_of_FPRM;
			newpop[j].fitness=oldpop[mate1].fitness;
		}

		/*记录亲子关系和交叉位置 */
		newpop[j].parent[0] = mate1+1;
		newpop[j].xsite = jcross;
		newpop[j].parent[1] = mate2+1;

		if ((jcross!=0) || (mutted2 !=0 ) || (mutted2 !=0))
		{
			P_FPRM=fitness_compute(newpop[j+1].chrom,convert_head,VarNumber);
			newpop[j+1].P_of_FPRM=P_FPRM;
			newpop[j+1].fitness=1.0/P_FPRM;
		}
		else //父代没有发生交叉和变异，所以fitness保持不变
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