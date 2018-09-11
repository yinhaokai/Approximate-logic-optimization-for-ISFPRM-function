# include "header.h"

void delete_readin_list(struct readin *head)
{
	struct readin *addr;
	while (head != NULL)
	{

		addr = head->link;
		delete  head;
		head = addr;

	}


}