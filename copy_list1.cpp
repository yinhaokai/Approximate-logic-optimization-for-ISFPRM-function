#include "header.h"

void copy_list1(struct convt_int *convt_head, struct convt_int *convt_head_temp, int VarNumber, int Num_outs)
{

	struct convt_int *new_node, *p, *p_temp;
	p_temp = convt_head_temp;
	p = convt_head;
	int count = 0;
	while (p != NULL)
	{
		if (count != 0)
		{
			new_node = new struct convt_int;
			new_node->bin_array = (int *)malloc(VarNumber*sizeof(int));
			new_node->out = (int *)malloc(Num_outs*sizeof(int));
			new_node->link = NULL;
			p_temp->link = new_node;
		}
		else
		{
			new_node = p_temp;
			new_node->bin_array = (int *)malloc(VarNumber*sizeof(int));
			new_node->out = (int *)malloc(Num_outs*sizeof(int));
			new_node->link = NULL;
		}
		for (int i = 0; i<VarNumber; i++)
		{
			*(new_node->bin_array + i) = *(p->bin_array + i);
		}
		for (int i = 0; i<Num_outs; i++)
		{
			*(new_node->out + i) = *(p->out + i);
		}
		p_temp = new_node;
		new_node->id = p->id;
		p = p->link;
		count++;
	}
}