#include "header.h"
using namespace std;
#include<iostream>
void show_lianbiao(struct convt_int * convt_next_head,int VarNumber,int Num_outs){
	struct convt_int *scq2;
	scq2 = convt_next_head;
	cout << "�����������" << endl;
	while (scq2 != NULL)
	{
		//cout<<"flagΪ"<<scq2->flag<<endl;
		//cout << "resΪ"<< scq2->res << endl;

		for (int l = 0; l < VarNumber; l++)
			printf("%d", scq2->bin_array[l]);
		printf("%c", ' ');
		for (int n = 0; n < Num_outs; n++)
			printf("%d", scq2->out[n]);
		// printf("    %d", sc->flag);
		printf("\n");
		//cout << scq2->id << endl;
		scq2 = scq2->link;
	}
	printf("\n");
}

int combinator(int n, int m)
{
	int temp;
	int k = 0;
	int isum = 1;
	if (n<m)
	{
		temp = n;
		n = m;
		m = temp;
	}
	for (k = 1; k <= m; k++)
	{
		isum = (isum*(n - m + k)) / k;//����˷����������㣨m-n+k��/k�������������
	}
	return isum;
}