//#include <stdio.h>
//#include <malloc.h>
//#include"header.h"
//
//
//int n = 0;                    //ȫ�ֱ���,��¼����ĳ��� 
//
///*---------------��������----------------------*/
//
//struct  convt_int *Create()
//{
//	struct  convt_int *head, *p1, *p2;
//	//����һ��LEN��С�Ŀռ�,����p1,p2ָ��ָ���� 
//	p2 = p1 = (struct  convt_int *)malloc(sizeof(struct convt_int));
//	//��ͷָ����ΪNULL 
//	head = NULL;
//	//��������ڵ㲢���ڵ��Ԫ�ظ�ֵ 
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
//		printf("������ѧ����ѧ�ź�����:");
//		scanf("%ld %s", &p1->id, p1->out);
//	}
//	//��β�ڵ��ָ����ΪNULL 
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
//	//�ж������Ƿ�Ϊ�� 
//	if (NULL == head)
//	{
//		printf("����Ϊ��!\n");
//	}
//	else
//	{
//		//ѭ����ӡ�����е�Ԫ�� 
//		printf("%d ����¼�ֱ�Ϊ:\n", n);
//		while (p != NULL)
//		{
//			printf("%ld %s\n", p->num, p->name);
//			//ָ��ָ����һ���ڵ� 
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
//	//�ж������Ƿ�Ϊ�� 
//	if (NULL == head)
//	{
//		printf("����Ϊ��!\n");
//		return head;
//	}
//	//�����ڵ�,�жϵ�ǰ�ڵ��ǲ�����Ҫɾ���Ľڵ㼰�Ƿ�Ϊβ�ڵ�
//	//����ҵ���Ӧ�ڵ�,�����Ѿ�������β�ڵ������ѭ�� 
//	while (p1->id != num&&p1->link != NULL)
//	{
//		p2 = p1;
//		p1 = p1->link;
//	}
//	//�ж��Ƿ��ҵ���Ӧ�ڵ� 
//	if (p1->id == num)
//	{
//		//Ҫɾ���Ľڵ��ǲ�������ĵ�һ���ڵ�
//		//�����,�ͽ�ͷָ��ָ��ýڵ�ĺ�һ���ڵ�
//		//�������,�ͽ��ýڵ��ǰһ���ڵ��ָ��ָ��ýڵ�ĺ�һ���ڵ� 
//		if (head == p1)
//		{
//			head = p1->link;
//		}
//		else
//		{
//			p2->link = p1->link;
//		}
//		n = n - 1;
//		printf("%ld �ڵ���ɾ��.\n", num);
//	}
//	else
//	{
//		printf("������û��Ҫɾ����Ԫ��.\n");
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
//	//�ж������Ƿ�Ϊ��,����ǿ�����,�ͽ��½ڵ���Ϊ��һ���ڵ� 
//	if (NULL == head)
//	{
//		head = p0;
//		p0->link = NULL;
//	}
//	else
//	{
//		//����ÿһ���ڵ��е�ѧ��,����ѧ�űȽϴ�С
//		//����ҵ�һ��ѧ�ű���ѧ�Ŵ�,�ͽ���ѧ�ŵĽڵ������֮ǰ 
//		//���β�ڵ��ѧ���Ա���ѧ��С,�ͽ��½ڵ���뵽����β�� 
//		while ((p0->num > p1->num) && (p1->link != NULL))
//		{
//			p2 = p1;
//			p1 = p1->link;
//		}
//		//�ҵ�һ������ѧ�Ŵ�Ľڵ� 
//		if (p0->num <= p1->num)
//		{
//			//�жϸýڵ��Ƿ�Ϊͷ�ڵ�,�����,���½ڵ�����Ϊͷ�ڵ� 
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
//	//�����ȼ�1 
//	n = n + 1;
//	printf("%ld ����ɹ�!\n", newStu->num);
//	return head;
//}
