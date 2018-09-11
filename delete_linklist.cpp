#include "header.h"
#include <stdlib.h>
convt_int* ptr_update(convt_int*,bool);
void remake_link(convt_int*,convt_int*&);
bool equal_judge(convt_int*,convt_int*,int,int);    //if equal,return true,else,false ,k=0 judge out,k=1 judge input
bool all_zero(convt_int*, int, int);
void merge_out(convt_int*, convt_int*,int);
convt_int* delete_linklist(convt_int *head, int VarNumber, int outs)
{
	convt_int *ptr = head, *new_head = head;
	bool all_equal = false, input_equal = false, const_equal = false, delete_state = true;
	int delete_times = 0;
	convt_int *ptr_next;
	while (ptr != NULL)
	{
		ptr_next = ptr->link;
		delete_state = true;
		if (all_zero(ptr, VarNumber, outs))
			remake_link(ptr, new_head);
		else
		{
			input_equal = equal_judge(ptr, ptr_next, VarNumber, 1);
			if (input_equal)
			{
				all_equal = equal_judge(ptr, ptr_next, outs, 0);
				if (const_equal && all_equal)
				{
					remake_link(ptr, new_head);
					delete_times += 1;
				}
				else if (!const_equal && all_equal)
				{
					const_equal = true;
					remake_link(ptr, new_head);
					delete_times = 1;
				}
				else if (const_equal && !all_equal)
				{
					if (delete_times % 2 == 1)
						remake_link(ptr, new_head);
					else
						delete_state = false;
					const_equal = false;
					delete_times = 0;
				}
				else
				{
					delete_times = 0;
					remake_link(ptr, new_head);
					merge_out(ptr, ptr_next, outs);
				}
			}
			else
			{
				if (const_equal)
				{
					if (delete_times % 2 == 1)
						remake_link(ptr, new_head);
					else
						delete_state = false;
					const_equal = false;
					delete_times = 0;
				}
				else
					delete_state = false;
			}
		}
		ptr = ptr_update(ptr, delete_state);
	}
	return new_head;
}
convt_int* ptr_update(convt_int *ptr, bool state)
{
	convt_int *temp;
	if (state)
	{
		temp = ptr->link;
		free(ptr->bin_array);
		free(ptr->out);
		delete ptr;
	}
	else
		temp = ptr->link;
	return temp;
}
void remake_link(convt_int* ptr,convt_int*& new_head)
{
	if (ptr->prev != NULL && ptr->link == NULL)
	{
		ptr->prev->link = NULL;
	}
	else if (ptr->prev == NULL && ptr->link != NULL)
	{
		new_head = ptr->link;
		ptr->link->prev = NULL;
	}
	else if (ptr->prev != NULL && ptr->link != NULL)
	{
		ptr->prev->link = ptr->link;
		ptr->link->prev = ptr->prev;
	}
}
bool equal_judge(convt_int*former,convt_int*latter,int nums,int k)
{
	if (latter == NULL)
		return false;
	if (k == 0)
	{
		if (former->out[0] != latter->out[0] || former->out[nums - 1] != latter->out[nums - 1])
			return false;
		for (int i = 0; i < nums; i++)
			if (former->out[i] != latter->out[i])
				return false;
	}
	else
	{
		if (former->bin_array[0] != latter->bin_array[0] || former->bin_array[nums - 1] != latter->bin_array[nums - 1])
			return false;
		for (int i = 0; i < nums; i++)
			if (former->bin_array[i] != latter->bin_array[i])
				return false;
	}
	return true;
}
bool all_zero(convt_int* ptr, int VarNumber, int outs)
{
	for (int i = outs-1; i >=0; --i)
		if (ptr->out[i] != 0)
			return false;
	return true;
}
void merge_out(convt_int*former, convt_int*latter,int outs)
{
	for (int i = 0; i < outs; ++i)
		latter->out[i] = latter->out[i] ^ former->out[i];
}