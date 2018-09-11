#include "header.h"
#include<math.h>
#include<conio.h>
void find_arry(struct convt_int *h, int varnum, int temp[1024][15], int outnum);
void DeleteList(struct convt_int *h, int i, int n);
void Compare_arry(struct convt_int *h, int varnum, int outnum, int **temp_complete, int same_posion[1024][15], int same_num[1024]);

void pla_to_min(struct convt_int * convt_next_head, int VarNumber, int Num_outs, int **temp_complete, int same_posion[1024][15], int same_num[1024])
{
	Compare_arry(convt_next_head, VarNumber, Num_outs, temp_complete, same_posion, same_num);
	
}
void struct_orientlist(int varnum, int **temp,int outnum)
{
	//printf("%d",varnum);
	int i, j;
	int carry = 0;
	//int *temp_arry;
	//temp_arry=(int*)malloc(varnum*pow((double)2,(double)varnum)*sizeof(int));

	for (i = 0; i<pow((double)2, (double)varnum); i++)
	{
		for (j = 0; j<varnum+outnum; j++)
		{
			temp[i][j] = 0;
		}
	}
	for (i = 1; i<pow((double)2, (double)varnum); i++)
	{
		temp[i][0] = temp[i - 1][0] + 1;
		if (temp[i][0] == 2)
		{
			temp[i][0] = 0;
			carry = 1;
		}
		else
			carry = 0;
		for (j = 1; j<varnum; j++)
		{
			temp[i][j] = temp[i - 1][j] + carry;
			carry = 0;
			if (temp[i][j] == 2)
			{
				temp[i][j] = 0;
				carry = 1;
			}
		}
	}

}
void Compare_arry(struct convt_int *h, int varnum, int outnum,int **temp_complete, int same_posion[1024][15], int same_num[1024]){
	int temp_have[1024][15];
	int value_0[1024][15];
	struct convt_int *temp_h1;
	temp_h1 = h;
	int products = 0;
	int i = 0; int j = 0; int ii = 0; int count = 0;
	struct_orientlist(varnum, temp_complete,outnum);
	find_arry(h, varnum, temp_have,outnum);
	int temp_products_of_have_products =counter_products(temp_h1);
	//printf("%d", temp_products_of_have_products);
	for (i = 0; i < temp_products_of_have_products; i++)
	{
		temp_have[i][outnum + varnum] = i;
	}




	for ( i = 0; i < temp_products_of_have_products; i++)
	{
		for ( j = 0; j < varnum; j++)
		{
			if (temp_have[i][j] == 2){
				temp_have[i][j] =0;
				
				for (int ii = 0; ii < varnum; ii++)
				{
					temp_have[temp_products_of_have_products][ii] = temp_have[i][ii];

				}
				for (int jj = varnum; jj < outnum + varnum; jj++)
				{
					temp_have[temp_products_of_have_products][jj] = temp_have[i][jj];

				}
				temp_have[temp_products_of_have_products][outnum + varnum] = temp_have[i][outnum + varnum];
				temp_have[temp_products_of_have_products][j] = 1;
				temp_products_of_have_products++;
			}
		}
	}

	//测试代码
	//int ceshi = 0;

	//for (i = 0; i < temp_products_of_have_products; i++)
	//{
	//	for (j = 0; j < varnum; j++)
	//	{
	//		if (temp_have[i][j] == 2){
	//			ceshi++;
	//		}
	//		temp_have[i][14] = ceshi;
	//		ceshi = 0;
	//	}
	//}
	//int sum = 0;
	//for (i = 0; i < temp_products_of_have_products; i++)
	//{
	//	sum = sum + pow((double)2, (double)temp_have[i][14]);
	//}


	//printf("\n%d", sum);
	//system("pause");


	//printf("最小项为1表\n");
	//for (i = 0; i<temp_products_of_have_products; i++)
	//{
	//	for (j = 0; j<varnum+outnum+1; j++){
	//		printf("%d", temp_have[i][j]);
	//	}
	//	printf("\n");
	//}
	//system("pause");
	for (i = 0; i<pow((double)2, (double)varnum); i++)
	{
		for (j = 0; j < 5; j++){
			same_posion[i][j]=-1;
		}
	}

	same_num[1024] = { 0 };
	int tt = 0;
	for (i = 0; i<temp_products_of_have_products;i++)
	{
		for (ii = 0; ii<pow((double)2, (double)varnum); ii++)
		{
			for (j = 0; j<varnum; j++){
				if (temp_have[i][j] == temp_complete[ii][j])
				{
					count++; 
				}
			}
			if (count == varnum)
			{
				tt++;
				//printf("tt=%d",tt);	
				for (j = 0; j < varnum+outnum; j++){
					temp_complete[ii][j] =temp_have[i][j];
				}
				same_posion[ii][same_num[ii]] = temp_have[i][varnum + outnum];
				//printf("%d", temp_have[i][varnum + outnum]);
				same_num[ii] = same_num[ii]+1;
			//	printf("%d", same_num[ii]);
				if (same_num[ii]>4){ printf("out the arry"); exit(1); }
			}
			else
				count = 0;
		}
	}

	//printf("完全最小项表\n");

	//for (i = 0; i<pow((double)2, (double)varnum); i++)
	//{
	//	for (j = 0; j<varnum + outnum; j++){
	//		if (j == varnum){ printf(" "); }
	//		printf("%d", temp_complete[i][j]);
	//	}
	//	printf("\n");
	//}
	//printf("最小项表对应的原列表个数\n");

	//for (i = 0; i<pow((double)2, (double)varnum); i++)
	//{
	//
	//	printf("%d ", same_num[i]);
	//	printf("\n");
	//}

	//printf("最小项表对应的原列表系数\n");

	//for (i = 0; i<pow((double)2, (double)varnum); i++)
	//{
	//	for (j = 0; j < 5; j++){
	//		printf("%d ", same_posion[i][j]);
	//	}
	//	printf("\n");
	//}



	int count_0 = 0;
	int zero_hang = 0;
	int al_hang =(int) pow((double)2, (double)varnum);
	for (i = 0; i<pow((double)2, (double)varnum); i++)
	{
		for (j = varnum; j < outnum + varnum; j++)
		{
			if (temp_complete[i][j]==0)
			{
					count_0++;
			}
		}
		if (count_0==outnum){
			for (j = 0; j < varnum + outnum; j++){
				value_0[zero_hang][j] = temp_complete[i][j];
			}
			zero_hang++;
		}
		count_0 = 0;
	}
	printf("what fuck\n");
	//printf("最小项为0表\n");
	//for (i = 0; i<zero_hang; i++)
	//{
	//	for (j = 0; j<varnum + outnum; j++){
	//		printf("%d", value_0[i][j]);
	//	}
	//	printf("\n");
	//}
	//printf("零行有%d", zero_hang);
	//printf("have 行有%d", temp_products_of_have_products);
	//printf("总行有 %d", al_hang);
 //   system("pause");
}
void find_arry(struct convt_int *h, int varnum, int temp[1024][15], int outnum)
{
	int j = 0;
	int i, ii;
	int products;
	struct convt_int *temp_h1;
	temp_h1 = h;
	for (i = 0; i<pow((double)2, (double)varnum); i++)
	{
		for (j = 0; j<varnum+outnum; j++)
		{
			temp[i][j] = 0;
		}
	}
	products = counter_products(temp_h1);
	temp_h1 = h;
	for (i = 0; i<products; i++)
	{

		//	printf("dizhi=%d\n",temp_h1);
		for (ii = 0; ii<varnum; ii++)
		{
			temp[i][ii] = temp_h1->bin_array[ii];
		}
		for (int jj = varnum; jj <outnum+varnum; jj++)
		{
			temp[i][jj] = temp_h1->out[jj-varnum];

		}
		temp_h1 = temp_h1->link;
	}

}
