#include"header.h"
#include<iostream>
using namespace std;
double  tb_to_rm0(int VarNumber, int Numofproduct, int Num_outs, int  popsize, int  pcross, struct convt_int *convt_next_head, int *p_fprm, double *p_sw){
	double start = 0, end = 0, during = 0;
	start = clock();
	int *plarity;
	struct convt_int *convt_head_current;
	struct disrelation *dis_pt;
	plarity = (int *)malloc((VarNumber + 1) * sizeof(int));
	if (plarity == NULL) {  //这个判断是必须的
		printf("plarity内存分配出错！");
		exit(1);
	}

	dis_pt = (struct disrelation*)malloc(sizeof(disrelation)*Numofproduct);  //生成无关项表
	if (dis_pt == NULL) {  //这个判断是必须的
		printf("dis_pt内存分配出错！");
		exit(1);
	}
	int counts;
	for (int p = 0; p < VarNumber; p++)
		plarity[p] = 0;//极性表置零
	struct convt_int *convt_head_new, *convt_head_new1, *convt_head_new3;
	int disrelation_num = 0;
	int i_count = 0;
	convt_head_new = convt_head_new1 = convt_next_head;
	while (convt_next_head != NULL)
	{
		int j_flag = 0;
		int n = 0;
		convt_next_head->flag = 0;
		convt_next_head->deration = (int *)malloc((VarNumber + 1)*sizeof(int));
		if (convt_next_head->deration == NULL) {
			cout << "内存耗尽" << endl;
			exit(1);
		}
		for (int i = 0; i < VarNumber + 1; i++)//如果和极性相同，那么将对应位置0，(flag+1,deration记录位置），不同置1，为2不变，相同时，
		{
			convt_next_head->deration[i] = -1;
		}
		dis_pt[i_count].position = (int *)malloc((Num_outs + 1)*sizeof(int));
		if (dis_pt[i_count].position == NULL) {
			cout << "内存耗尽" << endl;
			exit(1);
		}
		for (int i = 0; i < VarNumber; i++)//如果和极性相同，那么将对应位置0，(flag+1,deration记录位置），不同置1，为2不变，相同时，
		{
			//	printf("%d", convt_next_head->bin_array[i]);
			if (convt_next_head->bin_array[i] == 2)
				convt_next_head->bin_array[i] = 2;
			else
			{

				if (convt_next_head->bin_array[i] == plarity[i])
				{
					convt_next_head->bin_array[i] = 0;
					convt_next_head->flag = convt_next_head->flag + 1;
					convt_next_head->deration[j_flag] = i + 1;
					//printf("jj%d ", convt_next_head->deration[j]);
					j_flag++;
				}
				else
					convt_next_head->bin_array[i] = 1;
			}
		}
		for (int i = 0; i < Num_outs; i++){
			if (convt_next_head->out[i] == 2)
			{

				dis_pt[i_count].position[n] = i + 1; //无关项的位子
				n++;
				disrelation_num++;
			}
		}
		//printf("\n");
		convt_next_head->id = i_count;
		dis_pt[i_count].num = disrelation_num;//每个链表内的无关项数，没有为0，与链表对应
		i_count++;
		convt_next_head = convt_next_head->link;
	}

	while (convt_head_new != NULL)
	{
		int j_flag1 = 0;
		for (int i = 0; i < VarNumber + 1; i++)//如果和极性相同，那么将对应位置0，(flag+1,deration记录位置），不同置1，为2不变，相同时，
		{
			convt_head_new->deration[i] = -1;
		}
		for (int i = 0; i < VarNumber; i++)//如果和极性相同，那么将对应位置0，(flag+1,deration记录位置），不同置1，为2不变，相同时，
		{
			if (convt_head_new->bin_array[i] == 2)
				convt_head_new->bin_array[i] = 2;
			else
			{
				if (convt_head_new->bin_array[i] == plarity[i])
				{
					convt_head_new->bin_array[i] = 0;
					convt_head_new->deration[j_flag1] = i + 1;
					j_flag1++;
				}
				else
					convt_head_new->bin_array[i] = 1;
			}
		}
		convt_head_new = convt_head_new->link;
	}

	///零位遍历取反////可以继续优化///////////////mijji//////////////////
	//show_lianbiao(convt_head_new1, VarNumber, Num_outs);
	//freeall(convt_next_head);
	counts = 0;
	convt_head_current = convt_head_new1;
	struct convt_int *saved_head;
	while (convt_head_current != NULL)
	{
		if (convt_head_current->flag != 0)
		{

			convt_head_current->res = powerof2(convt_head_current->flag);//res记录相同的个数n的2^的值
			convt_head_current->mjchart = mj(convt_head_current->flag, convt_head_current->res);
			convt_head_current->miji_temp = (int**)malloc(sizeof(int*)*convt_head_current->res);                      ////开辟一个行为res的二维指针
			for (int s = 0; s < convt_head_current->res; s++)
				convt_head_current->miji_temp[s] = (int*)malloc(sizeof(int)*convt_head_current->flag);
			mj_rpl(convt_head_current, convt_head_current->miji_temp, convt_head_current);

			for (int i = 0; i < convt_head_current->res; i++)
			{
				int *chart;
				if (counts == 0)
				{
					convt_head_new3 = new struct convt_int;
					if (convt_head_new3 == NULL) {
						cout << "内存耗尽" << endl;
						exit(1);
					}
					saved_head = convt_head_new3;

				}
				else
				{
					struct convt_int *p_temp = convt_head_new3;
					convt_head_new3 = new struct convt_int;
					if (convt_head_new3 == NULL) {
						cout << "内存耗尽" << endl;
						exit(1);
					}

					p_temp->link = convt_head_new3;
				}
				chart = (int *)malloc((VarNumber + 1) * sizeof(int));
				if (chart == NULL) {
					cout << "内存耗尽" << endl;
					exit(1);
				}
				for (int s = 0; s < VarNumber; s++)
				{
					chart[s] = convt_head_current->bin_array[s];
				}

				for (int j = 0; convt_head_current->miji_temp[i][j] != 0 && j < convt_head_current->flag; j++)
				{
					//	printf("%d ", convt_head_current->miji_temp[i][j] - 1);
					chart[convt_head_current->miji_temp[i][j] - 1] = 1;
				}
				//system("pause");
				convt_head_new3->bin_array = (int *)malloc((VarNumber + 1) * sizeof(int));
				if (convt_head_new3->bin_array == NULL) {
					cout << "内存耗尽" << endl;
					exit(1);
				}

				convt_head_new3->out = (int *)malloc((Num_outs + 1)*sizeof(int));
				if (convt_head_new3->out == NULL) {
					cout << "内存耗尽" << endl;
					exit(1);
				}

				for (int k = 0; k < VarNumber; k++)
				{
					if (chart[k] == 2)                    ///将2置为0
						convt_head_new3->bin_array[k] = 0;
					else
						convt_head_new3->bin_array[k] = chart[k];
				}
				for (int d = 0; d < Num_outs; d++)
					convt_head_new3->out[d] = convt_head_current->out[d];
				counts++;
				convt_head_new3->id = convt_head_current->id;
			}
			for (int s = 0; s < convt_head_current->res; s++)//删除convt_head_current->miji_temp
			{
				free(convt_head_current->miji_temp[s]);
				convt_head_current->miji_temp[s] = NULL;
			}
			free(convt_head_current->miji_temp);
			convt_head_current->miji_temp = NULL;
		}
		else
		{
			if (counts == 0)
			{
				convt_head_new3 = new struct convt_int;
				saved_head = convt_head_new3;
			}
			else
			{
				struct convt_int *p_temp = convt_head_new3;
				convt_head_new3 = new struct convt_int;
				p_temp->link = convt_head_new3;
			}
			convt_head_new3->bin_array = (int *)malloc((VarNumber + 1) * sizeof(int));
			convt_head_new3->out = (int *)malloc((Num_outs + 1)*sizeof(int));
			for (int s = 0; s < VarNumber; s++)
			{
				if (convt_head_current->bin_array[s] == 2)
					convt_head_new3->bin_array[s] = 0;              //将输入里的2置为0
				else
					convt_head_new3->bin_array[s] = convt_head_current->bin_array[s];
			}

			for (int d = 0; d < Num_outs; d++)
				convt_head_new3->out[d] = convt_head_current->out[d];
			counts++;
			convt_head_new3->id = convt_head_current->id;
		}
		convt_head_current = convt_head_current->link;
	}
	convt_head_new3->link = NULL;                                //、、、、、、、，，，，，，将零遍历取反，且标志取反的位置并且把输入的无关项置0

	// freeall2(convt_head_new1);
	cout << "进入遗传算法" << endl;

	DeleList(saved_head, VarNumber, Num_outs);
	//show_lianbiao(saved_head, VarNumber, Num_outs);
	end = clock();
	during = end - start;
	printf("TB到0极性花费时间%fms\n", static_cast<double>(during)/ CLOCKS_PER_SEC * 1000);
	return small_ga(disrelation_num, VarNumber, popsize, pcross, dis_pt, plarity, Num_outs, saved_head, i_count, p_fprm, p_sw);



}