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
	if (plarity == NULL) {  //����ж��Ǳ����
		printf("plarity�ڴ�������");
		exit(1);
	}

	dis_pt = (struct disrelation*)malloc(sizeof(disrelation)*Numofproduct);  //�����޹����
	if (dis_pt == NULL) {  //����ж��Ǳ����
		printf("dis_pt�ڴ�������");
		exit(1);
	}
	int counts;
	for (int p = 0; p < VarNumber; p++)
		plarity[p] = 0;//���Ա�����
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
			cout << "�ڴ�ľ�" << endl;
			exit(1);
		}
		for (int i = 0; i < VarNumber + 1; i++)//����ͼ�����ͬ����ô����Ӧλ��0��(flag+1,deration��¼λ�ã�����ͬ��1��Ϊ2���䣬��ͬʱ��
		{
			convt_next_head->deration[i] = -1;
		}
		dis_pt[i_count].position = (int *)malloc((Num_outs + 1)*sizeof(int));
		if (dis_pt[i_count].position == NULL) {
			cout << "�ڴ�ľ�" << endl;
			exit(1);
		}
		for (int i = 0; i < VarNumber; i++)//����ͼ�����ͬ����ô����Ӧλ��0��(flag+1,deration��¼λ�ã�����ͬ��1��Ϊ2���䣬��ͬʱ��
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

				dis_pt[i_count].position[n] = i + 1; //�޹����λ��
				n++;
				disrelation_num++;
			}
		}
		//printf("\n");
		convt_next_head->id = i_count;
		dis_pt[i_count].num = disrelation_num;//ÿ�������ڵ��޹�������û��Ϊ0���������Ӧ
		i_count++;
		convt_next_head = convt_next_head->link;
	}

	while (convt_head_new != NULL)
	{
		int j_flag1 = 0;
		for (int i = 0; i < VarNumber + 1; i++)//����ͼ�����ͬ����ô����Ӧλ��0��(flag+1,deration��¼λ�ã�����ͬ��1��Ϊ2���䣬��ͬʱ��
		{
			convt_head_new->deration[i] = -1;
		}
		for (int i = 0; i < VarNumber; i++)//����ͼ�����ͬ����ô����Ӧλ��0��(flag+1,deration��¼λ�ã�����ͬ��1��Ϊ2���䣬��ͬʱ��
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

	///��λ����ȡ��////���Լ����Ż�///////////////mijji//////////////////
	//show_lianbiao(convt_head_new1, VarNumber, Num_outs);
	//freeall(convt_next_head);
	counts = 0;
	convt_head_current = convt_head_new1;
	struct convt_int *saved_head;
	while (convt_head_current != NULL)
	{
		if (convt_head_current->flag != 0)
		{

			convt_head_current->res = powerof2(convt_head_current->flag);//res��¼��ͬ�ĸ���n��2^��ֵ
			convt_head_current->mjchart = mj(convt_head_current->flag, convt_head_current->res);
			convt_head_current->miji_temp = (int**)malloc(sizeof(int*)*convt_head_current->res);                      ////����һ����Ϊres�Ķ�άָ��
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
						cout << "�ڴ�ľ�" << endl;
						exit(1);
					}
					saved_head = convt_head_new3;

				}
				else
				{
					struct convt_int *p_temp = convt_head_new3;
					convt_head_new3 = new struct convt_int;
					if (convt_head_new3 == NULL) {
						cout << "�ڴ�ľ�" << endl;
						exit(1);
					}

					p_temp->link = convt_head_new3;
				}
				chart = (int *)malloc((VarNumber + 1) * sizeof(int));
				if (chart == NULL) {
					cout << "�ڴ�ľ�" << endl;
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
					cout << "�ڴ�ľ�" << endl;
					exit(1);
				}

				convt_head_new3->out = (int *)malloc((Num_outs + 1)*sizeof(int));
				if (convt_head_new3->out == NULL) {
					cout << "�ڴ�ľ�" << endl;
					exit(1);
				}

				for (int k = 0; k < VarNumber; k++)
				{
					if (chart[k] == 2)                    ///��2��Ϊ0
						convt_head_new3->bin_array[k] = 0;
					else
						convt_head_new3->bin_array[k] = chart[k];
				}
				for (int d = 0; d < Num_outs; d++)
					convt_head_new3->out[d] = convt_head_current->out[d];
				counts++;
				convt_head_new3->id = convt_head_current->id;
			}
			for (int s = 0; s < convt_head_current->res; s++)//ɾ��convt_head_current->miji_temp
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
					convt_head_new3->bin_array[s] = 0;              //���������2��Ϊ0
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
	convt_head_new3->link = NULL;                                //���������������������������������ȡ�����ұ�־ȡ����λ�ò��Ұ�������޹�����0

	// freeall2(convt_head_new1);
	cout << "�����Ŵ��㷨" << endl;

	DeleList(saved_head, VarNumber, Num_outs);
	//show_lianbiao(saved_head, VarNumber, Num_outs);
	end = clock();
	during = end - start;
	printf("TB��0���Ի���ʱ��%fms\n", static_cast<double>(during)/ CLOCKS_PER_SEC * 1000);
	return small_ga(disrelation_num, VarNumber, popsize, pcross, dis_pt, plarity, Num_outs, saved_head, i_count, p_fprm, p_sw);



}