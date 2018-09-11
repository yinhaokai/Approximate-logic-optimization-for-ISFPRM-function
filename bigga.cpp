#include<time.h>
#include "header.h"
#include<iostream>
using namespace std;
void Change_LIAN(struct convt_int *convt_head_USE, int posion_of_zhulie, int  posion_of_out, int  single_minterm[15], int varnum, int outnum);
void FAULT_initpop(struct FAULT_individual *FAULT_oldpop, int FAULT_chrom_Number, int VarNumber, int Num_out);
void copy_list2(struct convt_int *convt_next_head, struct convt_int *convt_head_oldest, int VarNumber,int  Num_outs);
double FAULT_fitness_compute(int *FAULT_chrom, struct convt_int *convt_head_oldest, struct convt_int *convt_next_head, int VarNumber, int Num_outs, int longth_big_chrom, int **temp_complete, int same_posion[1024][15], int same_num[1024], int popsize, int  pcross,int  Numofproduct,int *a,double *b);
void  FAULT_INSTERT(struct convt_int *convt_head_USE, int VarNumber, int Num_outs, int *FAULT_chrom, int **temp_complete, int same_posion[1024][15], int same_num[1024], int longth_big_chrom);
void Change_LIAN(struct convt_int *convt_head_USE, int posion_of_zhulie, int  posion_of_out, int  single_minterm[15], int varnum, int outnum);
void Search_list(struct convt_int *Cursor, int Marker);
void Insert_Noexistent_Mintern(struct convt_int *convt_head_USE,int  posion_of_out, int single_minterm[15],int  varnum,int outnum);
int Fault_select(struct FAULT_individual *FAULT_oldpop, double sumfitness);
int Fault_crossover(int *parent1, int *parent2, int *child1, int *child2, int VarNumber);

int  Fault_mutation(int *child, int longth_big_chrom, int VarNumber, int Num_outs);

void FAULT_find_best_FAULT_individual(struct  FAULT_individual *newpop, int longth_big_chrom, struct best_FAULT_individual *best_chrom);
void FAULT_generation(struct  FAULT_individual *FAULT_oldpop, struct  FAULT_individual *FAULT_newpop, struct convt_int *convt_head_oldest, struct convt_int *convt_next_head, int VarNumber, int Num_outs, int longth_big_chrom, int **temp_complete, int same_posion[1024][15], int same_num[1024], int popsize, int  pcross, int  Numofproduct);


int big_ga(int VarNumber, int Numofproduct, int Num_outs, int  popsize, int  pcross, struct convt_int *convt_head_current, struct convt_int *convt_next_head, struct convt_int *convt_ON_head, int longth_big_chrom){
	//pla_to_min(convt_next_head, VarNumber, Num_outs);
	//show_lianbiao(convt_next_head, VarNumber, Num_outs);
	int **temp_complete = (int **)malloc((pow((double)2, (double)VarNumber))* sizeof(int));
	for (int s = 0; s < pow((double)2, (double)VarNumber); s++)
		temp_complete[s] = (int*)malloc((Num_outs + 1 + VarNumber)*sizeof(int));
	for (int i = 0; i <pow((double)2, (double)VarNumber); i++)
	{
		for (int j = 0; j < Num_outs + 1+VarNumber; j++)
		{
			temp_complete[i][j] = 0;
		}
	}
	int same_posion[1024][15] = { 0 };
	int *same_num = (int *)malloc(1025*sizeof(int));
	double FAULT_sw = 0.0;
	int FAULT_fprm = 0;
	double FAULT_FIT = 0.0;
	double *pFAULT_sw = &FAULT_sw;
	int *pFAULT_fprm = &FAULT_fprm;
	for (int  i = 0; i < 1025; i++)
	{
		same_num[i] = 0;
	}
	struct FAULT_individual  *FAULT_oldpop;             /* ��ǰ����Ⱥ */
	struct FAULT_individual  *FAULT_newpop;             /* ��һ����Ⱥ */
	struct FAULT_individual  *FAULT_temp_pop;
	struct best_FAULT_individual  *FAULT_best_chrom;
	int FAULT_chrom_Number;
	FAULT_chrom_Number = longth_big_chrom;
	srand((unsigned)time(NULL));                                  //���֣��ṩ�������
	FAULT_oldpop = (struct FAULT_individual  *)malloc(FAULT_popsize*sizeof(struct FAULT_individual));
	FAULT_newpop = (struct FAULT_individual  *)malloc(FAULT_popsize*sizeof(struct FAULT_individual));    //����popsize=100������ڵ�
	FAULT_best_chrom = (struct best_FAULT_individual  *)malloc(1 * sizeof(struct best_FAULT_individual));
	FAULT_best_chrom->chrom = (int *)malloc(longth_big_chrom*sizeof(int));
	FAULT_best_chrom->best_fitness = 0.0;
	FAULT_best_chrom->FAULT_fprm = 0;
	FAULT_best_chrom->FAULT_sw = 0.0;

	struct convt_int *convt_head_oldest;
	convt_head_oldest = new struct convt_int;
	copy_list2(convt_next_head, convt_head_oldest, VarNumber, Num_outs);
	//for (int i = 1; i < 100; i++){
	//	copy_list2(convt_head_oldest, convt_next_head, VarNumber, Num_outs);
	//	tb_to_rm0(VarNumber, Numofproduct, Num_outs, popsize, pcross, convt_next_head);
	//}
	//tb_to_rm0(VarNumber, Numofproduct, Num_outs, popsize, pcross, convt_head_oldest);
	
	//show_lianbiao(convt_next_head, VarNumber, Num_outs);



	pla_to_min(convt_next_head, VarNumber, Num_outs, temp_complete, same_posion, same_num);


	double start = 0, finish = 0; double end = 0;
	start = clock();


	int gen;
	for (int i = 0; i<FAULT_popsize; i++)
	{
		FAULT_oldpop[i].chrom = (int *)malloc(FAULT_chrom_Number*sizeof(int));
		FAULT_newpop[i].chrom = (int *)malloc(FAULT_chrom_Number*sizeof(int));    //���ٿռ�
	}


	FAULT_initpop(FAULT_oldpop, FAULT_chrom_Number, VarNumber,Num_outs);                         //��ʼ����Ⱥ,��Ⱥ��СΪ100
	double FAULT_FPRM=0;
	for (int i = 0; i<FAULT_popsize; i++)
	{
		FAULT_FIT = 0.0; FAULT_sw = 0.0; FAULT_fprm = 0;
		FAULT_FIT = FAULT_fitness_compute(FAULT_oldpop[i].chrom, convt_head_oldest, convt_next_head, VarNumber, Num_outs, longth_big_chrom, temp_complete, same_posion, same_num, popsize, pcross, Numofproduct, pFAULT_fprm, pFAULT_sw);
		FAULT_oldpop[i].FAULT_fprm = FAULT_fprm;
		FAULT_oldpop[i].FAULT_sw= FAULT_sw;
		FAULT_oldpop[i].fitness = 1.0 / FAULT_FIT;                   //һ��Ⱦɫ�����Ӧ�ȼ��㣬fitnessԽ��Խ�ã�P_FPRMԽСԽ��
	}
	for (gen = 0; gen<FAULT_maxgen; gen++)                           //�Ŵ�������һ��
	{
		//* ������һ�� 
		FAULT_generation(FAULT_oldpop, FAULT_newpop, convt_head_oldest, convt_next_head, VarNumber, Num_outs, longth_big_chrom, temp_complete, same_posion, same_num, popsize, pcross, Numofproduct);
		FAULT_find_best_FAULT_individual(FAULT_newpop, longth_big_chrom, FAULT_best_chrom);      //ѡ����Ӧ����ߵ�һ��Ⱦɫ��     
		FAULT_temp_pop = FAULT_oldpop;
		FAULT_oldpop = FAULT_newpop;
		FAULT_newpop = FAULT_temp_pop;
		printf("\n the faultbestsw is: %f \n", FAULT_best_chrom->FAULT_sw);
		printf("\n the faultbestfprm is: %d \n", FAULT_best_chrom->FAULT_fprm);
		printf("\n the firness is: %f \n", 1 / FAULT_best_chrom->best_fitness);
	}

	for (int i = 0; i<longth_big_chrom; i++)
	{
		printf("%d ", *(FAULT_best_chrom->chrom + i));
		if (i == VarNumber - 1){ printf("|"); }
	}
	end = clock();
	printf("\n the faultbestsw is: %f \n", FAULT_best_chrom->FAULT_sw);
	printf("\n the faultbestfprm is: %d \n", FAULT_best_chrom->FAULT_fprm);
	printf("��ʱ%fms", static_cast<double>(end - start)/CLOCKS_PER_SEC*1000);
	printf("\n the firness is: %f \n", 1/FAULT_best_chrom->best_fitness);
	system("pause");
	return 0;

}
void FAULT_initpop(struct FAULT_individual *FAULT_oldpop, int FAULT_chrom_Number, int VarNumber, int Num_outs)           /* �����ʼ����Ⱥ */
{
	int j, k;
	for (j = 0; j < FAULT_popsize; j++)
	{
		for (k = 0; k < FAULT_chrom_Number; k++)
		{
			FAULT_oldpop[j].chrom[k] = rand() % (int)(pow((double)2, (double)VarNumber)*Num_outs);
			
		}
		FAULT_oldpop[j].parent[0] = 0;     /* ��ʼ��������Ϣ */
		FAULT_oldpop[j].parent[1] = 0;
		FAULT_oldpop[j].xsite = 0;
	}
}
void copy_list2(struct convt_int *convt_next_head, struct convt_int *convt_head_oldest, int VarNumber, int  Num_outs){
	struct convt_int *new_node, *p, *p_temp;
	p_temp = convt_head_oldest;
	p = convt_next_head;
	int count = 0;
	while (p != NULL)
	{
		if (count != 0)
		{
			new_node = new struct convt_int;
			new_node->bin_array = (int *)malloc(VarNumber*sizeof(int));
			if (new_node->bin_array == NULL) {
				cout << "�ڴ�ľ�" << endl;
				exit(1);
			}

			new_node->out = (int *)malloc(Num_outs*sizeof(int));
			if (new_node->out == NULL) {
				cout << "�ڴ�ľ�" << endl;
				exit(1);
			}

			new_node->link = NULL;
			p_temp->link = new_node;
		}
		else
		{
			new_node = p_temp;
			new_node->bin_array = (int *)malloc(VarNumber*sizeof(int));
			if (new_node->bin_array == NULL) {
				cout << "�ڴ�ľ�" << endl;
				exit(1);
			}
			new_node->out = (int *)malloc(Num_outs*sizeof(int));

			if (new_node->out == NULL) {
				cout << "�ڴ�ľ�" << endl;
				exit(1);
			}

			new_node->link = NULL;
		}
		for (int i = 0; i<VarNumber; i++)
		{
			*(new_node->bin_array + i) = *(p->bin_array + i);
		}
		for (int i = 0; i<Num_outs; i++)
		{
			*(new_node->out + i) = *(p->out + i);
		}
		p_temp = new_node;
		new_node->id = p->id;
		p = p->link;
		count++;
	}
}
double FAULT_fitness_compute(int *FAULT_chrom, struct convt_int *convt_head_oldest, struct convt_int *convt_next_head, int VarNumber, int Num_outs, int longth_big_chrom, int **temp_complete, int same_posion[1024][15], int same_num[1024], int popsize, int  pcross, int  Numofproduct,int *p_fprm,double *p_sw)
{
	
	double FAULT_best_fit=0.0;
	struct convt_int *convt_head_USE;
	convt_head_USE = new struct convt_int;
	copy_list2(convt_head_oldest, convt_head_USE, VarNumber, Num_outs);
	FAULT_INSTERT(convt_head_USE, VarNumber, Num_outs, FAULT_chrom, temp_complete, same_posion, same_num, longth_big_chrom);//������޹����滻ΪȾɫ��


	FAULT_best_fit = tb_to_rm0(VarNumber, Numofproduct, Num_outs, popsize, pcross, convt_head_USE, p_fprm, p_sw);

	////sw=sw_calculation(convt_head_temp11,VarNumber,Num_outs,P_FPRM);
	//freeall(convt_head_temp11);
	//free(same_temp);
	//return P_FPRM;
	return FAULT_best_fit;
}
void  FAULT_INSTERT(struct convt_int *convt_head_USE, int varnum, int outnum, int *FAULT_chrom, int **temp_complete, int same_posion[1024][15], int same_num[1024], int longth_big_chrom){
	struct convt_int *q_creat, *posion;//�ȶ���2��ָ��һ������ָ��
	int ii = 0;
	int i = 0;
	int **fault_hanglie;
	int product = counter_products(convt_head_USE);
	posion = convt_head_USE;//��ָ��pָ��Ҫ�����ͷ���	
	fault_hanglie = (int **)malloc((longth_big_chrom+1)* sizeof(int));
	for (int s = 0; s < longth_big_chrom+1; s++)
		fault_hanglie[s] = (int*)malloc(sizeof(int)*3);


	for (i = 0; i < longth_big_chrom; i++){
		fault_hanglie[i][0] = FAULT_chrom[i] /(int) pow((double)2, (double)varnum) + 1;//��n�����
		fault_hanglie[i][1] = FAULT_chrom[i] % (int)pow((double)2, (double)varnum);//��m����С����ʽ
	}
	int posion_of_zhulie=0;
	int posion_of_out = 0;
	int single_minterm[20] = { 0 };



	for (i = 0; i < longth_big_chrom; i++){
		for (int j = 0; j < varnum+outnum; j++){
			single_minterm[j] = temp_complete[fault_hanglie[i][1]][j];
		}
		posion_of_out = fault_hanglie[i][0];
		if (same_num[fault_hanglie[i][1]]==0)
		{
			Insert_Noexistent_Mintern(convt_head_USE, posion_of_out, single_minterm, varnum, outnum);
		}
		else
		{
			for (int j = 0; j < same_num[fault_hanglie[i][1]]; j++){
			posion_of_zhulie = same_posion[fault_hanglie[i][1]][j];
			Change_LIAN(convt_head_USE, posion_of_zhulie, posion_of_out, single_minterm, varnum, outnum);
			//printf("%d ", same_posion[fault_hanglie[i][1]][j]);
			}
			Insert_Noexistent_Mintern(convt_head_USE, posion_of_out, single_minterm, varnum, outnum);
		}	
		cout << endl;
	}
	for (int s = 0; s < longth_big_chrom; s++)
	{
		free(fault_hanglie[s]);
		fault_hanglie[s] = NULL;
	}
	free(fault_hanglie); 
	fault_hanglie = NULL;


}
void Change_LIAN(struct convt_int *convt_head_USE, int posion_of_zhulie, int  posion_of_out, int  single_minterm[15], int varnum, int outnum){
	struct convt_int *Head, *Cursor;
	Head = Cursor = convt_head_USE;
	//�ı��Ӧ���б��λ�õ����
	Search_list(Cursor, posion_of_zhulie);

	for (int i = 0; i < varnum; i++){
		if (Cursor->bin_array[i]==2)
		{
			if (single_minterm[i] == 0)
				Cursor->bin_array[i] = 1;
			else if (single_minterm[i] == 1)
				Cursor->bin_array[i] = 0;
			else
			{
				printf("fault");
				exit(1);
			}
			break;
		}
	}
}

void Insert_Noexistent_Mintern(struct convt_int *convt_head_USE, int  posion_of_out, int single_minterm[15], int  varnum, int outnum){
	struct convt_int *Head, *Cursor,*Creation;
	int i;
	Head = Cursor = convt_head_USE;
	while (Cursor->link!=NULL)
	{
		Cursor = Cursor->link;
	}
	Creation = (convt_int *)malloc(sizeof(convt_int));
	Creation->bin_array = (int *)malloc(varnum*sizeof(int));
	Creation->out = (int *)malloc(outnum*sizeof(int));
	for (i = 0; i<varnum; i++)
	{
		Creation->bin_array[i] = single_minterm[i];
	}
	for (i = 0; i<outnum; i++)
	{
		if (i != posion_of_out)
			Creation->out[i] = single_minterm[i + varnum];
		else
		if (Creation->out[i] == 1){
			Creation->out[i] = 0;
		}
		else{
			Creation->out[i] = 1;
		}
			
	}
	Creation->id = -1;
	// q->link = NULL;/*����ǽ��²���Ľ��ָ����ָ����һ�����ָ����ָ��Ľ���ַ��Ϊp->next*/
	Cursor->link = Creation;
	Creation->link = NULL;	/*��Ҫ������λ��ǰ��Ľ��ָ����ָ�����ڲ���Ľ���׵�ַ*/
	Cursor = Creation;



}
void Search_list(struct convt_int *Cursor, int Marker){
	int temp=0;
	while (temp<Marker)
	{
		Cursor = Cursor->link;
		temp++;
	}
}
void FAULT_generation(struct  FAULT_individual *FAULT_oldpop, struct  FAULT_individual *FAULT_newpop, struct convt_int *convt_head_oldest, struct convt_int *convt_next_head, int VarNumber, int Num_outs, int longth_big_chrom, int **temp_complete, int same_posion[1024][15], int same_num[1024], int popsize, int  pcross, int  Numofproduct)
{

	int Fault_mate1, Fault_mate2, Fault_jcross, j = 0;
	double Fault_totalfitness;
	int Fault_P_FPRM = 0;
	double FAULT_fit;
	int Fault_mutted1, Fault_mutted2;
	double FAULT_sw = 0.0;
	int FAULT_fprm = 0;
	double FAULT_FIT = 0.0;
	double *pFAULT_sw = &FAULT_sw;
	int *pFAULT_fprm = &FAULT_fprm;

	/*  ÿ������ǰ����Ԥѡ */
	Fault_totalfitness = 0.0;


	/* ѡ��, ����, ���� */
	do
	{
		/* ��ѡ������� */
		Fault_mate1 = Fault_select(FAULT_oldpop, Fault_totalfitness);
		Fault_mate2 = Fault_select(FAULT_oldpop, Fault_totalfitness);

		/* ����ͱ��죬jcross=0 ��ʾû�н��н��� */
		Fault_jcross = Fault_crossover(FAULT_oldpop[Fault_mate1].chrom, FAULT_oldpop[Fault_mate1].chrom, FAULT_newpop[j].chrom, FAULT_newpop[j + 1].chrom, longth_big_chrom);

		/*mutted1,2=0��ʾ��û�н��б��� */
		Fault_mutted1 = Fault_mutation(FAULT_newpop[j].chrom, longth_big_chrom,VarNumber,Num_outs);
		Fault_mutted2 = Fault_mutation(FAULT_newpop[j + 1].chrom, longth_big_chrom, VarNumber, Num_outs);
		/* ����, ������Ӧ�� */
		if ((Fault_jcross != 0) || (Fault_mutted1 != 0) || (Fault_mutted2 != 0))
		{
			FAULT_fit = FAULT_fitness_compute(FAULT_oldpop[j].chrom, convt_head_oldest, convt_next_head, VarNumber, Num_outs, longth_big_chrom, temp_complete, same_posion, same_num, popsize, pcross, Numofproduct, pFAULT_fprm, pFAULT_sw);
			FAULT_newpop[j].fitness = 1.0 / FAULT_fit;
			FAULT_newpop[j].FAULT_fprm = FAULT_fprm;
			FAULT_newpop[j].FAULT_sw = FAULT_sw;
			//printf(" %f,%d,%f\n", FAULT_newpop[j].fitness, FAULT_oldpop[j].FAULT_fprm, FAULT_oldpop[j].FAULT_sw);
			//printf("%d", FAULT_oldpop[j].FAULT_fprm);
		}
		else //����û�з�������ͱ��죬����fitness���ֲ���
		{
			FAULT_newpop[j].fitness = FAULT_oldpop[Fault_mate1].fitness;
			FAULT_newpop[j].FAULT_fprm = FAULT_oldpop[Fault_mate1].FAULT_fprm;
			FAULT_newpop[j].FAULT_sw = FAULT_oldpop[Fault_mate1].FAULT_sw;
			//printf(" %f,%d,%f\n", FAULT_newpop[j ].fitness, FAULT_oldpop[j ].FAULT_fprm, FAULT_oldpop[j ].FAULT_sw);
		}

		/*��¼���ӹ�ϵ�ͽ���λ�� */
		FAULT_newpop[j].parent[0] = Fault_mate1 + 1;
		FAULT_newpop[j].xsite = Fault_jcross;
		FAULT_newpop[j].parent[1] = Fault_mate2 + 1;

		if ((Fault_jcross != 0) || (Fault_mutted2 != 0) || (Fault_mutted2 != 0))
		{
			FAULT_fit = FAULT_fitness_compute(FAULT_oldpop[j].chrom, convt_head_oldest, convt_next_head, VarNumber, Num_outs, longth_big_chrom, temp_complete, same_posion, same_num, popsize, pcross, Numofproduct,pFAULT_fprm, pFAULT_sw);
			FAULT_newpop[j+1].fitness = 1.0 / FAULT_fit;
			FAULT_newpop[j + 1].FAULT_fprm = FAULT_fprm;
			FAULT_newpop[j + 1].FAULT_sw = FAULT_sw;
			//printf(" %f,%d,%f\n", FAULT_newpop[j + 1].fitness, FAULT_oldpop[j + 1].FAULT_fprm, FAULT_oldpop[j + 1].FAULT_sw);
		}
		else //����û�з�������ͱ��죬����fitness���ֲ���
		{
			FAULT_newpop[j + 1].fitness = FAULT_oldpop[Fault_mate2].fitness;
			FAULT_newpop[j+1].FAULT_fprm = FAULT_oldpop[Fault_mate1].FAULT_fprm;
			FAULT_newpop[j+1].FAULT_sw = FAULT_oldpop[Fault_mate1].FAULT_sw;
			//printf(" %f,%d,%f\n", FAULT_newpop[j + 1].fitness, FAULT_oldpop[j + 1].FAULT_fprm, FAULT_oldpop[j + 1].FAULT_sw);
		}

		FAULT_newpop[j + 1].parent[0] = Fault_mate1 + 1;
		FAULT_newpop[j + 1].xsite = Fault_jcross;
		FAULT_newpop[j + 1].parent[1] = Fault_mate2 + 1;
		j = j + 2;
	} while (j < (FAULT_popsize - 1));
}
void FAULT_find_best_FAULT_individual(struct  FAULT_individual *newpop, int longth_big_chrom, struct best_FAULT_individual *best_chrom)
{
	int i, site, find_best, best_FPRM;
	double  total_fitness, avg_fitness, best_fitness;

	best_fitness = best_chrom->best_fitness;
	total_fitness = 0.0;
	find_best = 0;

	for (i = 0; i<FAULT_popsize; i++)
	{
		total_fitness = total_fitness + newpop[i].fitness;

		if (newpop[i].fitness > best_fitness)

		{
			find_best = 1;
			//	best_FPRM=newpop[i].P_of_FPRM;
			site = i;
			best_fitness = newpop[i].fitness;
		}
	}

	avg_fitness = total_fitness / FAULT_popsize;
	if (find_best) //ֻ����newpop���ҵ���oldpop���õ�best_chrom,ԭ�ȵ�best_chrom�ű��滻��
	{
		for (i = 0; i<longth_big_chrom; i++)
		{
			*(best_chrom->chrom + i) = newpop[site].chrom[i];
		}
		best_chrom->best_fitness = newpop[site].fitness;
		best_chrom->FAULT_fprm = newpop[site].FAULT_fprm;
		best_chrom->FAULT_sw = newpop[site].FAULT_sw;
		best_chrom->avg_fitness = avg_fitness;
	}
}
int Fault_select(struct FAULT_individual *FAULT_oldpop, double sumfitness){
	double sum, pick;
	int i;
	//pick = randomperc();

	//	srand((unsigned)time(NULL));
	pick = (double)rand() / RAND_MAX;

	sum = 0;
	if (sumfitness != 0)
	{
		for (i = 0; (sum < pick) && (i < FAULT_popsize); i++)
			sum = sum + (FAULT_oldpop[i].fitness / sumfitness);
	}
	else
		i = rnd(1, FAULT_popsize);//����һ������[1,popsize]������
	//i=(int)(rand()*popsize/(1.0*RAND_MAX)+1);//����һ������[1,popsize]������
	return(i - 1);
}
int Fault_crossover(int *parent1, int *parent2, int *child1, int *child2, int VarNumber)
/* �����������彻����������Ӹ��� */
{
	int jcross, k;
	//int mask, temp;
	int do_cross;
	do_cross = flip(Fault_pcross);
	if (do_cross)//��pcross���ʽ��н���
	{

		jcross = rnd(1, (VarNumber - 1));/* Cross between 1 and VarNumber-1 */

		for (k = 0; k<VarNumber; k++)
		{
			if (jcross >= k) // Ⱦɫ��󲿷ֽ���
			{
				child1[k] = parent1[k];
				child2[k] = parent2[k];
			}
			else //if (jcross < k)
			{
				child1[k] = parent2[k];
				child2[k] = parent1[k];
			}
		}
	}
	else
	{
		for (k = 0; k < VarNumber; k++) // 1-pcross���� �����н���
		{
			child1[k] = parent1[k];
			child2[k] = parent2[k];
		}
		jcross = 0;
	}
	return(jcross);
}
int  Fault_mutation(int *child, int longth_big_chrom, int VarNumber, int Num_outs)  /*�������*/
{
	int j, k;
	int mutted;
	int do_mutation;

	mutted = 0;

	for (k = 0; k <longth_big_chrom; k++)
	{
		do_mutation = flip(Fault_pmutation);
		if (do_mutation)
		{
			mutted = 1;
			child[k] = rand() % (int)(pow((double)2, (double)VarNumber)*Num_outs);

		}

	}

	return(mutted);
}

