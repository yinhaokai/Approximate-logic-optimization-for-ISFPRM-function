#include "header.h"

void freeall1(struct convt_int *convt_head_temp)
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
		free(p->deration);
		p->deration = NULL;
		free(p->mjchart);
		p->mjchart = NULL;
		delete p;
		p=convt_head_temp;
	}
}
void freeall2(struct convt_int *convt_head_temp)
{
	struct convt_int *p;
	p = convt_head_temp;
	while (p != NULL)
	{
		convt_head_temp = p->link;
		free(p->bin_array);
		p->bin_array = NULL;
		free(p->out);
		p->out = NULL;
	//	free(p->deration);
	//	p->deration = NULL;
	//	free(p->mjchart);
	//	p->mjchart = NULL;
		delete p;
		p = convt_head_temp;
	}
}