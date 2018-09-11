# include "header.h"

struct convt_int* plarity_chrom(struct convt_int *convt_head_temp1,int same,int *same_temp,int VarNumber,int Num_outs)
{
	int j;
	struct convt_int *convt_head_temp_current,*convt_head_new1,*convt_head_temp3;
	int counts_temp = 0;
	int k;
	int i=0;
    convt_head_temp3=convt_head_temp1;
	double start = 0, end1 = 0, end2 = 0;
	
	while(convt_head_temp3!=NULL)                               //计算成绩相熟
	{
	   start = clock();
       k=0;
	   j=0;
	   convt_head_temp3->deration=(int *)malloc(VarNumber*sizeof(int));
	   convt_head_temp3->flag=0;
	   for(i=0;i<same;i++)
	   {
		   if(convt_head_temp3->bin_array[same_temp[i]]==1)
		   {
			  convt_head_temp3->flag=convt_head_temp3->flag+1;
		    convt_head_temp3->deration[j]=same_temp[i]+1;
			j++;
		   }
	   }
	   if(convt_head_temp3->flag!=0)
	   {
		convt_head_temp3->res = powerof2(convt_head_temp3->flag);
		convt_head_temp3->mjchart = mj(convt_head_temp3->flag, convt_head_temp3->res);

		convt_head_temp3->miji_temp = (int**)malloc(sizeof(int*)*convt_head_temp3->res); ////开辟一个行为res的二维指针

		for (int s = 0; s < convt_head_temp3->res; s++)
			convt_head_temp3->miji_temp[s] = (int*)malloc(sizeof(int)*convt_head_temp3->flag);


		mj_rpl(convt_head_temp3, convt_head_temp3->miji_temp,convt_head_temp3);
		
		for (int i = 0; i < convt_head_temp3->res; i++)
		{
			
			if (counts_temp == 0)
			{
				convt_head_new1 = new struct convt_int;
				convt_head_temp_current = convt_head_new1;
			}
			else
			{
				struct convt_int *p_temp = convt_head_new1;
				convt_head_new1 = new struct convt_int;
				p_temp->link = convt_head_new1;
			}
		
			convt_head_new1->bin_array = (int *)malloc((VarNumber + 1) * sizeof(int));
			convt_head_new1->out = (int *)malloc((Num_outs + 1)*sizeof(int));
			for (int s = 0; s < VarNumber; s++)
				convt_head_new1->bin_array[s] = convt_head_temp3->bin_array[s];
			for (int j = 0; convt_head_temp3->miji_temp[i][j] != 0 && j < convt_head_temp3->flag; j++)
				convt_head_new1->bin_array[convt_head_temp3->miji_temp[i][j]-1] = 0;

			
			for (int d = 0; d < Num_outs; d++)
				convt_head_new1->out[d] = convt_head_temp3->out[d];
			
			counts_temp++;
			convt_head_new1->id = convt_head_temp3->id;
         
		}
		for (int s = 0; s < convt_head_temp3->res; s++)//删除convt_head_current->miji_temp
			{
				free(convt_head_temp3->miji_temp[s]);
				free(convt_head_temp3->mjchart[s]);
		    }
            free(convt_head_temp3->mjchart);
		    free(convt_head_temp3->miji_temp); 
		    free(convt_head_temp3->deration);
	   }
	   else
	   {
		   if (counts_temp == 0)
		   {
			   convt_head_new1 = new struct convt_int;
			   convt_head_temp_current = convt_head_new1;
		   }
		   else
		   {
			   struct convt_int *p_temp = convt_head_new1;
			   convt_head_new1 = new struct convt_int;
			   p_temp->link = convt_head_new1;
		   }
		   convt_head_new1->bin_array = (int *)malloc((VarNumber + 1) * sizeof(int));
		   convt_head_new1->out = (int *)malloc((Num_outs + 1)*sizeof(int));

		   for (int s = 0; s < VarNumber; s++)
		      convt_head_new1->bin_array[s] = convt_head_temp3->bin_array[s];

		   for (int d = 0; d < Num_outs; d++)
			   convt_head_new1->out[d] = convt_head_temp3->out[d];
		   counts_temp++;
		   convt_head_new1->id = convt_head_temp3->id;
	   }

	   convt_head_temp3=convt_head_temp3->link;
	   end1 = clock();
	  // printf("极性转换主要%fms\n", static_cast<double>(end1 - start) / CLOCKS_PER_SEC * 1000);
	}
	convt_head_new1->link = NULL;
	freeall(convt_head_temp1);
	
	return convt_head_temp_current;
}