#include "header.h"

void freeall(struct convt_int *convt_head_temp)
{
	struct convt_int *p;
	p=convt_head_temp;
	while(p!=NULL)
	{
		convt_head_temp=p->link;
		free(p->bin_array);
		p->bin_array = NULL;
		free(p->out);
		p->out = NULL;
		delete p;
		p=convt_head_temp;
	}
}