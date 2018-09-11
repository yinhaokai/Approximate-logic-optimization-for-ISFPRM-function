#include"header.h"
#include<iostream>
using namespace std;
double small_ga(int  disrelation_num, int VarNumber, int popsize, int pcross, struct disrelation *dis_pt, int *plarity, int Num_outs, struct convt_int *saved_head, int i_count,int* pFAULT_fprm, double *pFAULT_sw)
{	////////////////////////////////////////////////////遗传/////////////////////////////
	double start = 0, end = 0;
	start = clock();
	struct individual *oldpop;             /* 当前代种群 */
	struct individual *newpop;             /* 新一代种群 */
	struct individual *temp_pop;
	struct best_individual *best_chrom;
	int chrom_Number;
	chrom_Number = disrelation_num + VarNumber;
	srand((unsigned)time(NULL));                                  //播种，提供随机种子
	oldpop = (struct individual *)malloc(popsize*sizeof(struct individual));
	newpop = (struct individual *)malloc(popsize*sizeof(struct individual));    //定义popsize=100个链表节点
	best_chrom = (struct best_individual *)malloc(1 * sizeof(struct best_individual));
	best_chrom->chrom = (int *)malloc(chrom_Number*sizeof(int));
	best_chrom->best_fitness = 0.0;
	int i;
	double sw=0.0;
	double *p_sw=&sw;
	int P_FPRM=0;
	int *pP_FPRM = &P_FPRM;
	double FIT=0.0;
	double return_fit;
	int gen;
	for (i = 0; i<popsize; i++)
	{
		oldpop[i].chrom = (int *)malloc(chrom_Number*sizeof(int));
		newpop[i].chrom = (int *)malloc(chrom_Number*sizeof(int));    //开辟空间
	}

	initpop(oldpop, chrom_Number, popsize);                         //初始化种群,种群大小为100
	for (int i = 0; i<popsize; i++)
	{
		int k = 0;
		sw = 0.0, P_FPRM = 0; FIT = 0.0;
		FIT = fitness_compute(oldpop[i].chrom, saved_head, dis_pt, plarity, VarNumber, Num_outs, chrom_Number,p_sw,pP_FPRM);
		//printf("chrom_Number=%d\n",chrom_Number);
		oldpop[i].P_of_sw = sw;          //P_FPRM计算的
		oldpop[i].P_of_FPRM = P_FPRM;
		oldpop[i].fitness = 1.0 / FIT;                   //一个染色体的适应度计算，fitness越大越好，P_FPRM越小越好
	}
	//find_best_individual(oldpop,popsize,chrom_Number,best_chrom);

	//printf("\n the best polarity is:\n");
	//for (i=0;i<chrom_Number;i++)
	//printf("%d ", *(best_chrom->chrom+i));	
	for (gen = 0; gen<maxgen; gen++)                           //遗传产生新一代
	{
		//* 产生新一代 
		generation1(oldpop, newpop, popsize, VarNumber, pcross, saved_head, dis_pt, plarity, Num_outs, chrom_Number);
		find_best_individual(newpop, popsize, chrom_Number, best_chrom);      //选出适应度最高的一个染色体     
		temp_pop = oldpop;
		oldpop = newpop;
		newpop = temp_pop;


	}
	//printf("\n the best polarity is:\n");
	//for (i = 0; i<chrom_Number; i++)
	//{
	//	printf("%d ", *(best_chrom->chrom + i));
	//	if (i == VarNumber - 1){ printf("|"); }
	//}	
	end = clock();
	printf("小ga花费时间%fms\n", static_cast<double>(end-start) / CLOCKS_PER_SEC * 1000);
	*pFAULT_fprm= best_chrom->P_of_FPRM;
	*pFAULT_sw= best_chrom->P_of_sw;
	printf("\n the sw is: %f \n", best_chrom->P_of_sw);
	
	printf("\n the fprm is: %d \n", best_chrom->P_of_FPRM);
	printf("\n the fitness is: %f \n",1/ best_chrom->best_fitness);
	return_fit = 1/best_chrom->best_fitness;
	//system("pause");
	//for (i = 0; i < 1; i++){
	//	free(dis_pt[i_count].position);
	//	dis_pt[i_count].position = NULL;
	//}
	////free(dis_pt);
	////dis_pt = NULL;


	for (i = 0; i<popsize; i++)
	{
		free(oldpop[i].chrom);
		oldpop[i].chrom = NULL;
		free(newpop[i].chrom);     //开辟空间
		newpop[i].chrom = NULL;
	}

	free(best_chrom->chrom);
	best_chrom->chrom = NULL;
	free(best_chrom);
	best_chrom = NULL;
	free(newpop);
	newpop = NULL;
	free(oldpop);
	oldpop = NULL;
	freeall(saved_head);
	free(plarity);
	plarity = NULL;


	return return_fit;
}