#include "header.h"
/*
����ɾ�������У������������ͷ����

*/

void delete_B_list(struct convt_int *head)
{
	struct convt_int *p;

	p=head->link;
	while(p!=NULL)
	{
		head->link=p->link;
		delete (p);
		p=head->link;
	}
}
