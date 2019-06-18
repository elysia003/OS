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
//不在内存，访问次数为1
void LFU::Insert(int pag, int num)
{
	if (head->next == NULL || head->next->rate != 1)//不存在rate（1）
	{
		//新建rate(1）节点
		rateNode*p = new rateNode;
		p->rate = 1;
		if (head->next != NULL)
			head->next->last = p;
		p->next = head->next;
		p->last = head;
		head->next = p;
	}
	//新建页节点，插入rate1节点下
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
//在内存，访问次数++
void LFU::Updata(pagNode*p)
{
	//连接到当前rate+1节点
	if (p->rN->next == NULL || (p->rN->next->rate) != (p->rN->rate) + 1)
	{
		//没有这个节点，新建
		rateNode*q = new rateNode;
		q->rate = (p->rN->rate) + 1;
		if (p->rN->next != NULL)
			p->rN->next->last = q;
		q->next = p->rN->next;
		q->last = p->rN;
		p->rN->next = q;
	}
	//从页表节点里删除
	if (p->last != NULL)
	{
		//不是第一个节点
		p->last->next = p->next;
		if (p->next != NULL)
			p->next->last = p->last;
	}
	else
	{
		//第一个节点
		if (p->next != NULL)
			p->next->last = p->last;
		p->rN->pN = p->next;
	}
	if (p->next == NULL)
		p->rN->pNE = p->last;
	//插入到下一个rate节点
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
		//节点空
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
				//对应的rate下没有其他节点，删掉rate
				removeRate(head->next);
			}
			else
				p->last->next = NULL;//删掉该节点
			int romNum = p->romNum;
			pagTable[p->pagNum].remove();
			Insert(pag, romNum);//新节点插入rate（1）的头
			pagTable[pag].romNum = romNum;
			pagTable[pag].state = true;
			delete p;
		}
	}
	else
		//在内存
	{
		Updata(pagTable[pag].pN);
	}
}
