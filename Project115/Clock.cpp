#include "Clock.h"
#include<iostream>
using namespace std;

void Clock::Display()
	{
		int t = 0;
		LinkNode<PF>*p = pagFrame->head;
		while (p->next != pagFrame->head)
		{
			if (p->data.pagNum != -1)
				cout << "Block" << (p->data).blockNum << ": " << (p->data).pagNum << "  visit:" << pagTable[(p->data).pagNum].visit;
			else
				cout << "Block" << t << ": " << '*' << "  visit:" << 0;
			if (now == p)
				cout << "<--";
			p = p->next;
			t++;
			cout << endl;
		}
		if (p->data.pagNum != -1)
			cout << "Block" << (p->data).blockNum << " :" << (p->data).pagNum << "  visit:" << pagTable[(p->data).pagNum].visit;
		else
			cout << "Block" << t << ": " << '*' << "  visit:" << 0;
		if (now == p)
			cout << "<--";
		cout << endl;
	}
Clock::Clock(int ps, int PN) :Pross(ps)
	{
		PFNUM = PN;
		k = 0;
		pagFrame = new LoopList<PF>(PFNUM);
		now = pagFrame->getHead();
	};
void Clock::Visit(int add)
	{
		num++;
		int pag = add / 1024;
		if (pagTable[pag].state == false)
		{
			zd++;
			while (true)
			{
				if (pagTable[now->data.pagNum].visit == 1)//f访问位1则置0
					pagTable[now->data.pagNum].visit = 0;
				else
				{
					if (now->data.pagNum != -1)//有内容，移除
					{
						pagTable[now->data.pagNum].remove();
					}
					pagTable[pag].visit = 1;
					now->data.pagNum = pag;//插入页框
					if (now->data.blockNum == -1)
						now->data.blockNum = rB[k++];
					pagTable[pag].blockNum = now->data.blockNum;
					pagTable[pag].state = true;
					now = now->next;
					break;
				}
				now = now->next;//替换完成，指针后移
			}
		}
		else
		{
			LinkNode<PF>*p = now;
			while (true)
			{
				if (p->data.pagNum == pag)
				{
					pagTable[p->data.pagNum].visit = 1;//访问,visit置1，指针不动
					break;
				}
				p = p->next;
			}
		}
	}