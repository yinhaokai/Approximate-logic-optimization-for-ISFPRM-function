//#include <stdio.h>
//#include <malloc.h>
//#include"header.h"
//
//
//int n = 0;                    //全局变量,记录链表的长度 
//
///*---------------函数定义----------------------*/
//
//struct  convt_int *Create()
//{
//	struct  convt_int *head, *p1, *p2;
//	//开辟一个LEN大小的空间,并让p1,p2指针指向它 
//	p2 = p1 = (struct  convt_int *)malloc(sizeof(struct convt_int));
//	//将头指针置为NULL 
//	head = NULL;
//	//创建链表节点并给节点的元素赋值 
//	while (p1->link != 0)
//	{
//		n = n + 1;
//		if (NULL == head)
//		{
//			head = p1;
//		}
//		else
//		{
//			p2->link = p1;
//		}
//		p2 = p1;
//		p1 = (struct  convt_int *)malloc(sizeof(struct convt_int));
//		printf("请输入学生的学号和姓名:");
//		scanf("%ld %s", &p1->id, p1->out);
//	}
//	//将尾节点的指针置为NULL 
//	p2->link = NULL;
//	return head;
//}
//
//
//void Print(struct  convt_int *head)
//{
//	struct  convt_int * p;
//	p = head;
//
//	//判断链表是否为空 
//	if (NULL == head)
//	{
//		printf("链表为空!\n");
//	}
//	else
//	{
//		//循环打印链表中的元素 
//		printf("%d 个记录分别为:\n", n);
//		while (p != NULL)
//		{
//			printf("%ld %s\n", p->num, p->name);
//			//指针指向下一个节点 
//			p = p->link;
//		}
//	}
//}
//
//
//struct  convt_int *Delete(struct  convt_int * head, int num)
//{
//	struct  convt_int *p1;
//	struct  convt_int *p2;
//	p1 = head;
//	//判断链表是否为空 
//	if (NULL == head)
//	{
//		printf("链表为空!\n");
//		return head;
//	}
//	//遍历节点,判断当前节点是不是需要删除的节点及是否为尾节点
//	//如果找到相应节点,或者已经遍历到尾节点就跳出循环 
//	while (p1->id != num&&p1->link != NULL)
//	{
//		p2 = p1;
//		p1 = p1->link;
//	}
//	//判断是否找到相应节点 
//	if (p1->id == num)
//	{
//		//要删除的节点是不是链表的第一个节点
//		//如果是,就将头指针指向该节点的后一个节点
//		//如果不是,就将该节点的前一个节点的指针指向该节点的后一个节点 
//		if (head == p1)
//		{
//			head = p1->link;
//		}
//		else
//		{
//			p2->link = p1->link;
//		}
//		n = n - 1;
//		printf("%ld 节点已删除.\n", num);
//	}
//	else
//	{
//		printf("链表中没有要删除的元素.\n");
//	}
//	return head;
//}
//
//
//struct  convt_int *Insert(struct  convt_int * head, struct  convt_int * newStu)
//{
//	struct  convt_int *p0;
//	struct  convt_int *p1;
//	struct  convt_int *p2;
//	p0 = newStu;
//	p1 = head;
//	//判断链表是否为空,如果是空链表,就将新节点作为第一个节点 
//	if (NULL == head)
//	{
//		head = p0;
//		p0->link = NULL;
//	}
//	else
//	{
//		//遍历每一个节点中的学号,与新学号比较大小
//		//如果找到一个学号比新学号大,就将新学号的节点插入它之前 
//		//如果尾节点的学号仍比新学号小,就将新节点插入到链表尾部 
//		while ((p0->num > p1->num) && (p1->link != NULL))
//		{
//			p2 = p1;
//			p1 = p1->link;
//		}
//		//找到一个比新学号大的节点 
//		if (p0->num <= p1->num)
//		{
//			//判断该节点是否为头节点,如果是,则将新节点设置为头节点 
//			if (p1 == head)
//			{
//				head = p0;
//			}
//			else
//			{
//				p2->link = p0;
//			}
//			p0->link = p1;
//		}
//		else
//		{
//			p1->link = p0;
//			p0->link = NULL;
//		}
//	}
//	//链表长度加1 
//	n = n + 1;
//	printf("%ld 插入成功!\n", newStu->num);
//	return head;
//}
