# include "header.h"

void mj_rpl(struct convt_int *mc, int **mj_temp,struct convt_int *r)
{
	double start=0, end1=0, end2=0;
	for (int i = 0; i < mc->res; i++)
	   for (int j = 0; j <mc->flag ; j++)
			mj_temp[i][j] = 0;                          //初始化置mi_temp为零
	   for (int i = 0; i < mc->res; i++){
			for (int j = 0; j < mc->flag; j++)
			{
				int k = mc->mjchart[i][j];
			//	printf("%d ", k);
				if (k==0)
				{
					break;
				}
				else
				{
					mj_temp[i][j] = r->deration[k - 1];
				}

			}
			//printf("\n");
	   }
	  // printf("小ga适应度历时%fms\n", static_cast<double>(finish - start) / CLOCKS_PER_SEC * 1000);
	/*  for (int i = 0; i < 8; i++){ 
		   printf("%d ", r->deration[i - 1]);
	   }*/

	   /*for (int i = 0; i < mc->res; i++)
	   for (int j = 0; j <mc->flag; j++)
		  printf("%d ",mj_temp[i][j]);*/
	 //  system("pause");
	
}