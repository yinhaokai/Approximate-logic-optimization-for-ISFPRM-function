#include "header.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;


void main()
{
	double end;
	
	int have_ON;
	char *c_out, *readterm;
	struct readin *head_read, *current_read, *new_read;
	struct readin *head_ON_read, *ON_current_read, *ON_read_new;
	struct convt_int *convt_head, *convt_current;
	struct convt_int *convt_ON_head, *convt_ON_current;
	struct convt_int *sc;

	int *chart;//����Ҫ����
	struct convt_int *convt_next_head;//�����ͷָ��
	struct convt_int *convt_next_next_head;
	struct convt_int *convt_next_head_current;

	FILE *fptr1;
	FILE *time_file;
	
	//char readterm[max_var];
	int VarNumber, Numofproduct, Num_outs;//.i,.p,.o
	char *intername[3];

	//	int counter_minterms1,counter_minterms2;
	//	int redo,loop;

	struct convt_int *new_node;  //*minterms_head1,*minterms_head2;
	//	int minterms_Num2,minterms_Num1;



	float pcross=55.0;
	//	struct individual *temp;
	int run,gen;
	int popsize=8;
	int i;

	struct convt_int *convt_head_temp,*convt_head_temp1,*convt_head_temp2,*convt_head_temp3,*convt_head_temp_current,*convt_head_new1;
	struct convt_int *convt_head_current;
	
	int *c_plarity;
	int same=0;
	int *same_temp;
	int p_number=0;
	int counts_temp = 0;
	int P_FPRM=0;
	int ID=0;
	

	convt_head_current = new struct convt_int;
	convt_head_current->link = NULL;
	int counts = 0;

//	time_file=fopen("RM_Power.pla","a");
	for (int a = 0; a < 3; a++)
		intername[a] = (char *)malloc(3 * sizeof(char));//�ַ�����Ҫ��һ���ֽ�װ���ַ�
	fptr1 = fopen("MCNC/newcwp.pla", "r");	/*read in PLA header of original file */


	if (fptr1 == NULL)
	{
		printf("\nCanONt open the file !\n");
		exit(-2);
	}
	system("pause");
	fscanf(fptr1, "%s %d", &intername[0], &VarNumber);
	fscanf(fptr1, "%s %d", &intername[1], &Num_outs);
	fscanf(fptr1, "%s %d", &intername[2], &Numofproduct);



	head_read = new struct readin; //���������е�cubes��
	head_read->link = NULL;
	current_read = head_read;


	head_ON_read = new struct readin;//����������ON cubes��
	head_ON_read->link = NULL;
	ON_current_read = head_ON_read;
	have_ON = 0;

	convt_ON_head = new struct convt_int;
	convt_ON_head->link = NULL;

	while (!feof(fptr1))//�ļ������ı�־��feof(fptr1)��δ���ļ�δʱ����ֵΪ0�����򷵻�ֵΪ����ֵ
	{

		new_read = new struct readin;
		new_read->link = NULL;

		readterm = (char *)malloc((VarNumber + 1)*sizeof(char));//������
		c_out = (char *)malloc((Num_outs + 1)*sizeof(char));//����� ��1��Ϊ�˴洢�ַ���ĩβ�Ŀ��ַ�

		fscanf(fptr1, "%s %s", readterm, c_out);

		if (readterm[0] == '.' && readterm[1] == 'e')
		{
			break;//��������,��ֹ��ѭ��,continue��������һ����ĺ���,������һѭ������
		}
		else
		{
			//�Ȳ�������ǲ���ȫ��Ϊ0����ʱ�洢�����������ټ�⡣
			current_read->link = new_read;
			current_read = new_read;
			ON_read_new = new struct readin;
			ON_read_new->link = NULL;
			ON_read_new->term = (char *)malloc((VarNumber + 1)*sizeof(char));
			ON_read_new->out = (char *)malloc((Num_outs + 1)*sizeof(char));
			//		printf("readterm= %s \n",readterm);
			strcpy(ON_read_new->term, readterm);
			strcpy(ON_read_new->out, c_out);
			ON_current_read->link = ON_read_new;
			ON_current_read = ON_read_new;//ͷ���Ϊ��ַ�������ܴ��ֵ���൱��ON_current_read ָ��linkһ��ON_current_read=ON_current_read->link��
		}
	}
	free(readterm);
	free(c_out);
	fclose(fptr1);
	///////////////////////////////////////////////////////////////////////////
	////��ʵֵװ��ON_current_read�Ľṹ����///ON_current_read = head_ON_read///
	convert_char_to_int(head_ON_read, convt_ON_head, VarNumber, Num_outs);
	delete_readin_list(head_ON_read);
	//////////////////////////////////////////////////////////////////////
	///��Ҫ���Խ������///////////////////��עID/////////////////////////////
	//convt_next_head = new struct convt_int;
	//convt_next_head->link = NULL;
	double fault_rate = 0;
	int p_out;
	if (VarNumber + Num_outs > 13){
		printf("this exe can't creat "); system("pause"); 
	}
	p_out = ((int)pow((double)2, (double)VarNumber))*Num_outs;
	cout << "��������ڵ�ֵ" << 1.0 /p_out << endl;
	//cin >> fault_rate;
	fault_rate = 0.020;
	int longth_big_chrom = (int)(p_out*fault_rate);
	cout << "�������" << (int)(p_out*fault_rate) << endl;
	cout << "������Ϊ��" << VarNumber << "�����Ϊ��" << Num_outs  << "���������ռ�" << combinator(p_out, p_out*fault_rate)  << endl;
	convt_next_head = convt_ON_head->link;
	big_ga(VarNumber, Numofproduct, Num_outs, popsize, pcross, convt_head_current, convt_next_head, convt_ON_head, longth_big_chrom);
}
