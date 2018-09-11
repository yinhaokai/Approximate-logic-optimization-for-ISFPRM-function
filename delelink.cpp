#include "header.h"
#include <math.h>
#include <time.h>
void DeleList(struct convt_int *&convt_head,int VarNumber,int Num_outs )
{

	struct convt_int *pt = convt_head, *prev = NULL;
	clock_t start, finish;
	double  duration;
	int k = 0;
	while (pt!= NULL)                                     //指向尾节点
	{
		pt->prev = prev;
		pt->seq_num = k++;
		prev = pt;
		pt = pt->link;
	}
	start = clock();
	QuickSort(convt_head,prev,VarNumber,Num_outs);
	convt_head = delete_linklist(convt_head, VarNumber, Num_outs);
}
