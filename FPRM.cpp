#include "header.h"

void FPRM(struct convt_int *convt_head_temp1,int *chrom,struct disrelation *dis_pt,int *plarity,int VarNumber,int Num_outs)
{
	int j=0;
	int i=0;
	int p=0;
	int same;
	int *same_temp;
	same_temp=(int *)malloc(VarNumber*sizeof(int));
	struct convt_int *convt_head_temp2,*convt_head_temp_current;
	for( i=0;i<VarNumber;i++)
	{
		if(plarity[i]!=chrom[i])
		{
			same_temp[j]=i;
			same++;
			j++;
		} 
	}
	chromosome_DC(convt_head_temp1, VarNumber,chrom,dis_pt);//将染色体套若数据的无关项中
	struct convt_int *sc;
	sc = convt_head_temp1;
	printf("输出\n");
	while (sc != NULL)
	{
		printf("%d ", sc->id);

		for (int l = 0; l < VarNumber; l++)
			printf("%d", sc->bin_array[l]);
		printf("%c", ' ');
		for (int n = 0; n < Num_outs; n++)
			printf("%d", sc->out[n]);
		// printf("    %d", sc->flag);
		printf("\n");
		sc = sc->link;
	}
	convt_head_temp2=convt_head_temp1->link;
	convt_head_temp2 = DeleList(convt_head_temp2, VarNumber, Num_outs);
	struct convt_int *sc1;
	sc1 = convt_head_temp2;
	printf("输出\n");
	while (sc1 != NULL)
	{
		printf("%d ", sc1->id);

		for (int l = 0; l < VarNumber; l++)
			printf("%d", sc1->bin_array[l]);
		printf("%c", ' ');
		for (int n = 0; n < Num_outs; n++)
			printf("%d", sc1->out[n]);
		// printf("    %d", sc->flag);
		printf("\n");
		sc1 = sc1->link;
	}
	p=counter_products(convt_head_temp2);
	convt_head_temp_current=plarity_chrom(convt_head_temp2,same,same_temp,VarNumber,Num_outs);//0极性与染色体的极性相比不同的项密集展开
	struct convt_int *sc2;
	sc2 = convt_head_temp_current;
	printf("输出\n");
	while (sc2 != NULL)
	{
		printf("%d ", sc2->id);

		for (int l = 0; l < VarNumber; l++)
			printf("%d", sc2->bin_array[l]);
		printf("%c", ' ');
		for (int n = 0; n < Num_outs; n++)
			printf("%d", sc2->out[n]);
		// printf("    %d", sc->flag);
		printf("\n");
		sc2 = sc2->link;
	}
	convt_head_temp2 = DeleList(convt_head_temp2, VarNumber, Num_outs);

}
