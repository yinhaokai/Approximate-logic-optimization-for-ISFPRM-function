#include "header.h"

void find_best_individual(struct individual *newpop,int popsize,int VarNumber,struct best_individual *best_chrom)
{
	int i,site,find_best;
	double  total_fitness,avg_fitness,best_fitness;

	best_fitness=best_chrom->best_fitness;
	total_fitness=0.0;
	find_best=0;

	for (i=0;i<popsize;i++)
	{
		total_fitness=total_fitness+newpop[i].fitness;
		if(newpop[i].fitness > best_fitness)
		{
			find_best=1;
			//	best_FPRM=newpop[i].P_of_FPRM;
			site=i;
			best_fitness=newpop[i].fitness;
		}
	}

	avg_fitness=total_fitness/popsize;
	if (find_best) //只有在newpop中找到比oldpop更好的best_chrom,原先的best_chrom才被替换。
	{
		for (i=0;i<VarNumber;i++)
		{
			*(best_chrom->chrom+i)=newpop[site].chrom[i];
		}
		best_chrom->best_fitness=newpop[site].fitness;
		best_chrom->avg_fitness=avg_fitness;
		best_chrom->P_of_FPRM=newpop[site].P_of_FPRM;
		best_chrom->P_of_sw=newpop[site].P_of_sw;
		
	
	}
}