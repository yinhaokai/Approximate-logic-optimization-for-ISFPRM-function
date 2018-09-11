#include "header.h"

int counter_products(struct convt_int *convt_head)//计算乘积项的总个数
{
	double end;
	double start = 0, finish = 0;
	start = clock();
	int i,p_number,k;
	struct convt_int *p;

	p_number=1;

	p=convt_head->link;
	while(p!=NULL)
	{
		p_number=p_number+1;

		p=p->link;
	}

	return(p_number);
}