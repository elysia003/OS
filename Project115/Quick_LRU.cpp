#include "Quick_LRU.h"
#include<iostream>
using namespace std;
Quick_LRU::Quick_LRU(int ps, int PN) :Pross(ps)
{
	PFNUM = PN;
	head = new pagNode;
	end = new pagNode;
	head->next = end;
	end->last = head;
	nf = 1;
	k = 0;
}
void  Quick_LRU::Display()
{
	pagNode *p = head->next;
	while (p != end)
	{
		cout << "Block " << p->blockNum << "  :  " << p->pagNum << endl;
		p = p->next;
	}
}
void  Quick_LRU::Insert(int pn, int rn)
{
	pagNode*p = new pagNode(pn, rn);//插到表头
	p->next = head->next;
	p->last = head;
	head->next->last = p;
	head->next = p;
	pagTable[pn].pN = p;
	pagTable[pn].blockNum = p->blockNum;
	pagTable[pn].state = true;
}
void Quick_LRU::Updata(int pag)
{
	pagNode *p = pagTable[pag].pN;//移到表头
	p->last->next = p->next;
	p->next->last = p->last;
	p->next = head->next;
	p->last = head;
	head->next->last = p;
	head->next = p;
}
void Quick_LRU::Visit(int add)
{
	num++;
	int pag = add / 1024;
	if (pagTable[pag].state == false)
	{
		zd++;
		if (nf)
		{
			Insert(pag, rB[k++]);
			if (k == PFNUM)
				nf = 0;
		}
		else
		{
			//淘汰表尾
			pagNode *p = end->last;
			int rn = p->blockNum;
			pagTable[p->pagNum].state = false;
			end->last->last->next = end;
			end->last = end->last->last;
			delete p;
			Insert(pag, rn);
		}
	}
	else
	{
		Updata(pag);
	}
}
