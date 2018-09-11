#include "header.h"

//int crossover (unsigned *parent1, unsigned *parent2, unsigned *child1, unsigned *child2)

int crossover(int *parent1,int *parent2,int *child1,int *child2, float pcross, int VarNumber)
	/* 由两个父个体交叉产生两个子个体 */
{
	int jcross, k;
	//int mask, temp;
	int do_cross;
	do_cross=flip(pcross);
	if(do_cross)//以pcross概率进行交叉
	{
	
		jcross = rnd(1 ,(VarNumber - 1));/* Cross between 1 and VarNumber-1 */

		for(k=0;k<VarNumber;k++)
		{
			if (jcross >= k) // 染色体后部分交叉
			{
				child1[k]=parent1[k];
				child2[k]=parent2[k];
			}
			else //if (jcross < k)
			{
				child1[k]=parent2[k];
				child2[k]=parent1[k];
			}
		}
	}
	else
	{
		for(k = 0; k < VarNumber; k++) // 1-pcross概率 不进行交叉
		{
			child1[k] = parent1[k];
			child2[k] = parent2[k];
		}
		jcross = 0;
	}
	return(jcross);
}
