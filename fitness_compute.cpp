#include "header.h"

double fitness_compute(int *chrom,struct convt_int *convt_head_temp12,struct disrelation *dis_pt,int *plarity,int VarNumber,int Num_outs,int chrom_Number,double *p_sw,int *pP_fprm)
{

	double start = 0, finish = 0,end=0;
	start = clock();
	int j,P_FPRM;
	int same;
	same=0;
	int *same_temp;
	int k=0;
	double sw=0.0;
	struct convt_int *convt_head_temp1,*convt_head_temp11;
	convt_head_temp1=new struct convt_int;

	copy_list1(convt_head_temp12,convt_head_temp1,VarNumber,Num_outs);
	same_temp=(int *)malloc(VarNumber*sizeof(int));
	//printf("\n");
	//printf("未经处理rm结构\n");
	//struct convt_int *scq2;
	//scq2 = new struct convt_int;
	//scq2 = convt_head_temp1;
	//while (scq2 != NULL)
	//{
	//	printf("%d ", scq2->id);

	//	for (int l = 0; l < VarNumber; l++)
	//		printf("%d", scq2->bin_array[l]);
	//	printf("%c", ' ');
	//	for (int n = 0; n < Num_outs; n++)
	//		printf("%d", scq2->out[n]);
	//	// printf("    %d", sc->flag);
	//	printf("\n");
	//	scq2= scq2->link;
	//}
	//printf("\n");
	
	for(int l=0;l<VarNumber;l++)
	{
		if(plarity[l]!=chrom[l])
		{
			same_temp[k]=l;
			same++;
			k++;
		} 
	} 
	
	if(chrom_Number> VarNumber)
	chromosome_DC(convt_head_temp1, VarNumber,chrom,dis_pt);//将输出无关项替换为染色体


   DeleList(convt_head_temp1, VarNumber, Num_outs); //进行有准确无关项后的删除
   //printf("\n无关项转换\n");
   //struct convt_int *scq1;
   //scq1 = new struct convt_int;
   //scq1 = convt_head_temp1;
   //while (scq1 != NULL)
   //{
	  // printf("%d ", scq1->id);

	  // for (int l = 0; l < VarNumber; l++)
		 //  printf("%d", scq1->bin_array[l]);
	  // printf("%c", ' ');
	  // for (int n = 0; n < Num_outs; n++)
		 //  printf("%d", scq1->out[n]);
	  // // printf("    %d", sc->flag);
	  // printf("\n");
	  // scq1= scq1->link;
   //}
   //printf("极性展开\n");
   convt_head_temp11=plarity_chrom(convt_head_temp1,same,same_temp,VarNumber,Num_outs);//0极性与染色体的极性相比不同的项密集展开
 	finish = clock();
	//printf("小ga适应度历时%fms\n", static_cast<double>(finish - start) / CLOCKS_PER_SEC * 1000);

//	convt_head_temp11 = DeleList(convt_head_temp11, VarNumber, Num_outs);
    DeleList(convt_head_temp11, VarNumber, Num_outs);
	//struct convt_int *scq;
	//scq = new struct convt_int;
	//scq = convt_head_temp11;
	//while (scq != NULL)
	//{
	//	for (int l = 0; l < VarNumber; l++)
	//		printf("%d", scq->bin_array[l]);
	//	printf("%c", ' ');
	//	for (int n = 0; n < Num_outs; n++)
	//		printf("%d", scq->out[n]);
	//	// printf("    %d", sc->flag);
	//	printf("\n");
	//	scq = scq->link;
	//}
	P_FPRM=counter_products(convt_head_temp11);	
	*pP_fprm = P_FPRM;
	
	sw=sw_calculation(convt_head_temp11,VarNumber,Num_outs,P_FPRM);
	*p_sw = sw;end = clock();
	//printf("小ga适应度功耗成本历时%fms\n", static_cast<double>(end- finish) / CLOCKS_PER_SEC * 1000);
    freeall(convt_head_temp11);
	free(same_temp);
	//printf("%d\n",P_FPRM);
	//system("pause");
	
	return aef*P_FPRM+bet*sw;
}