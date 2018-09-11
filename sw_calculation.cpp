#include "header.h"
#include <math.h>
#include <time.h>
#include"sw_calculation.h"
double sw_calculation(struct convt_int *&convt_head,int VarNumber,int Num_outs,int P_FPRM )
{
	int memory[100][50]={0};//改成动态数组不然内存不够
	double sw;
	struct convt_int *pt = convt_head, *prev = NULL;
	clock_t start, finish;
	double  duration;
	int innumber_1,innumber_0;
	int outnumber_1,outnumber_0;
	int order_lian=0;
	int k = 0;
	int j;
	start = clock();
	pt = convt_head;
while (pt != NULL)//链的所有乘积项
{ 
	outnumber_1=outnumber_0=0;
	innumber_1=innumber_0=0;
	for (int i = 0; i < VarNumber; ++i)
	{
		if (pt->bin_array[i]==1) innumber_1++;
		else if(pt->bin_array[i]==0) innumber_0++;
		//printf("%d",pt->bin_array[i]);
	}
		//printf("input:size of zero is %d,size of one is %d\n ",innumber_0,innumber_1);
		//if(innumber_1>4){system("pause");}
	for (int i = 0; i < Num_outs; ++i)
	{
		//printf("%d",pt->out[i]);
		if (pt->out[i]==1) {
			outnumber_1++;}
		else if (pt->out[i]==0) 
		    {outnumber_0++;}
		if (pt->out[i]==1) {
		for(j=0;j<50;j++)
			{
				if(memory[i][j]==0)
				{
					memory[i][j]=order_lian;
					break;
				}
			}
		}
	
	  }
	/*printf("output:size of zero is %d,size of one is %d\n ",outnumber_0,outnumber_1);
	printf("\n");
	printf("lian=%d",order_lian);*/
	//printf("\n");
	pt = pt->link;
		
	order_lian++; 
}


	/*printf("乘积项=%d\n",P_FPRM);
	for(int i=0;i<Num_outs;i++){
			for(j=0;j<15;j++)
			{
				printf("%d ",memory[i][j]);
				if(j== 14){printf("\n");}
			}
     }*/
	sw=struction(convt_head,VarNumber,Num_outs,P_FPRM,memory);
	//system("pause");
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
//	printf("%f seconds\n", duration);
	return sw;
}
