#include "header.h"

void chromosome_DC(struct convt_int *convt_head_temp1,int VarNumber,int *chrom,struct disrelation *dis_pt)
{
	double end;
	double start = 0, finish = 0;
	start = clock();
	struct convt_int *convt_head_temp;
	//convt_head_temp= new struct convt_int;

	int i;
	convt_head_temp=convt_head_temp1;

	while(convt_head_temp!=NULL)                                   //无关项用染色体替换过程
	{      int ID=0;             
		ID=convt_head_temp->id;
		//printf("id=%d dis_pt[ID].num=%d\n",ID,dis_pt[ID].num);
		if(convt_head_temp->id==0)
			for( i=0;i<dis_pt[ID].num;i++)
				convt_head_temp->out[dis_pt[ID].position[i]-1]=chrom[VarNumber+i];    //这是对的

		else
		{
			if(dis_pt[ID-1].num!=dis_pt[ID].num)//链表非空	
				for(int i=0;i<dis_pt[ID].num-dis_pt[ID-1].num;i++)//该链表的2的个数
					convt_head_temp->out[dis_pt[ID].position[i]-1]=chrom[VarNumber+dis_pt[ID-1].num+i];//极性+上个个数+i

		}
		convt_head_temp=convt_head_temp->link;
	}
	//system("pause");
}