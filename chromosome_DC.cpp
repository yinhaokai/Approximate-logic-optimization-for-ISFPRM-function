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

	while(convt_head_temp!=NULL)                                   //�޹�����Ⱦɫ���滻����
	{      int ID=0;             
		ID=convt_head_temp->id;
		//printf("id=%d dis_pt[ID].num=%d\n",ID,dis_pt[ID].num);
		if(convt_head_temp->id==0)
			for( i=0;i<dis_pt[ID].num;i++)
				convt_head_temp->out[dis_pt[ID].position[i]-1]=chrom[VarNumber+i];    //���ǶԵ�

		else
		{
			if(dis_pt[ID-1].num!=dis_pt[ID].num)//����ǿ�	
				for(int i=0;i<dis_pt[ID].num-dis_pt[ID-1].num;i++)//�������2�ĸ���
					convt_head_temp->out[dis_pt[ID].position[i]-1]=chrom[VarNumber+dis_pt[ID-1].num+i];//����+�ϸ�����+i

		}
		convt_head_temp=convt_head_temp->link;
	}
	//system("pause");
}