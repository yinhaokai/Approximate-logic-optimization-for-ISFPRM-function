#include "header.h"
/*
链表删除过程中，保留了链表的头部。

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
