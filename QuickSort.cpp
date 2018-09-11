#include "header.h"

struct convt_int* partition(struct convt_int *, struct convt_int *,int,int);
void swap_linklist(struct convt_int*, struct convt_int*);
void ptri_plus(convt_int *&,convt_int*);
bool bitset_compare(convt_int*,convt_int*,int,int);   //if the former is not bigger than the latter ,true,else,false
void QuickSort(struct convt_int* head, struct convt_int *end,int VarNumber,int outs)  
{                                 
	if (end!=NULL && head!=NULL)
	{
		if (head->seq_num < end->seq_num)
		{
			struct convt_int *p;
			p = partition(head, end, VarNumber, outs);
			QuickSort(head, p->prev,VarNumber,outs);
			QuickSort(p->link, end,VarNumber,outs);
		}
	}
}
struct convt_int* partition(struct convt_int *head, struct convt_int *end,int VarNumber,int outs)
{
	struct convt_int *ptr_i, *ptr_j;
	ptr_i = head->prev;
	ptr_j = head;
	while (ptr_j != end)
	{
		if (bitset_compare(ptr_j,end,VarNumber,outs))
		{
			ptri_plus(ptr_i, head);
			if (ptr_i != ptr_j)
				swap_linklist(ptr_i, ptr_j);
		}
		ptr_j = ptr_j->link;
	}
	ptri_plus(ptr_i, head);
	if (ptr_i != end)
		swap_linklist(ptr_i, end);
	return ptr_i;
}
void swap_linklist(struct convt_int *former, struct convt_int *latter)
{
	int* pt_temp, temp;
	pt_temp = former->bin_array;
	former->bin_array = latter->bin_array;
	latter->bin_array = pt_temp;
	pt_temp = former->out;
	former->out = latter->out;
	latter->out = pt_temp;
	temp = former->id;
	former->id = latter->id;
	latter->id = temp;
}
void ptri_plus(convt_int *&ptr_i,convt_int *head)
{
	if (ptr_i != NULL)
		ptr_i = ptr_i->link;
	else
		ptr_i = head;
}
bool bitset_compare(convt_int*former,convt_int*latter,int VarNumber,int outs)
{
	for (int i = 0; i < VarNumber; ++i)
	{
		if (former->bin_array[i] > latter->bin_array[i])
			return false;
		else if (former->bin_array[i] < latter->bin_array[i])
			return true;
	}
	for (int i = 0; i < outs; ++i)
	{
		if (former->out[i] > latter->out[i])
			return false;
		if (former->out[i] < latter->out[i])
			return true;
	}
	return true;
}