#include "LFU.h"
#include<iostream>
using namespace std;
LFU::LFU(int ps, int PN) :Pross(ps) {
	PFNUM = PN;
	head = new rateNode;
	nf = 1;
	k = 0;
}
void LFU::Display()
{
	rateNode*p = head->next;
	while (p != NULL)
	{
		pagNode*q = p->pN;
		while (q != NULL)
		{
			cout << "ROM" << q->romNum << ": " << q->pagNum << "rate: " << p->rate << endl;
			q = q->next;
		}
		p = p->next;
	}
}
void LFU::removeRate(rateNode*p)
{
	p->last->next = p->next;
	if (p->next != NULL)
		p->next->last = p->last;
	delete p;
}
//�����ڴ棬���ʴ���Ϊ1
void LFU::Insert(int pag, int num)
{
	if (head->next == NULL || head->next->rate != 1)//������rate��1��
	{
		//�½�rate(1���ڵ�
		rateNode*p = new rateNode;
		p->rate = 1;
		if (head->next != NULL)
			head->next->last = p;
		p->next = head->next;
		p->last = head;
		head->next = p;
	}
	//�½�ҳ�ڵ㣬����rate1�ڵ���
	pagNode*q = new pagNode(pag, num);
	q->next = head->next->pN;
	q->last = NULL;
	q->rN = head->next;
	if (head->next->pN != NULL)
		head->next->pN->last = q;
	head->next->pN = q;
	pagTable[pag].pN = q;
	pagTable[pag].state = true;
	pagTable[pag].romNum = q->romNum;
	if (q->next == NULL)
		q->rN->pNE = q;
}
//���ڴ棬���ʴ���++
void LFU::Updata(pagNode*p)
{
	//���ӵ���ǰrate+1�ڵ�
	if (p->rN->next == NULL || (p->rN->next->rate) != (p->rN->rate) + 1)
	{
		//û������ڵ㣬�½�
		rateNode*q = new rateNode;
		q->rate = (p->rN->rate) + 1;
		if (p->rN->next != NULL)
			p->rN->next->last = q;
		q->next = p->rN->next;
		q->last = p->rN;
		p->rN->next = q;
	}
	//��ҳ��ڵ���ɾ��
	if (p->last != NULL)
	{
		//���ǵ�һ���ڵ�
		p->last->next = p->next;
		if (p->next != NULL)
			p->next->last = p->last;
	}
	else
	{
		//��һ���ڵ�
		if (p->next != NULL)
			p->next->last = p->last;
		p->rN->pN = p->next;
	}
	if (p->next == NULL)
		p->rN->pNE = p->last;
	//���뵽��һ��rate�ڵ�
	rateNode *t = p->rN->next;
	if (t->pN != NULL)
		t->pN->last = p;
	p->next = t->pN;
	t->pN = p;
	p->last = NULL;
	p->rN = t;
	if (p->next == NULL)
		p->rN->pNE = p;
	if (t->last->pN == NULL) {
		//�ڵ��
		removeRate(t->last);
	}
}
void LFU::Visit(int add)
{
	int pag = add / 1024;
	num++;
	if (pagTable[pag].state == false)
	{
		zd++;
		if (nf) {
			Insert(pag, rB[k++]);
			if (k == PFNUM)
				nf = 0;
		}
		else
		{
			pagNode*p = head->next->pNE;
			if(p->next==NULL)
				p->rN->pNE = p->last;
			if (p->last == NULL)
			{
				//��Ӧ��rate��û�������ڵ㣬ɾ��rate
				removeRate(head->next);
			}
			else
				p->last->next = NULL;//ɾ���ýڵ�
			int romNum = p->romNum;
			pagTable[p->pagNum].remove();
			Insert(pag, romNum);//�½ڵ����rate��1����ͷ
			pagTable[pag].romNum = romNum;
			pagTable[pag].state = true;
			delete p;
		}
	}
	else
		//���ڴ�
	{
		Updata(pagTable[pag].pN);
	}
}
