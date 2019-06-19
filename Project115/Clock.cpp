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
				if (pagTable[now->data.pagNum].visit == 1)//f����λ1����0
					pagTable[now->data.pagNum].visit = 0;
				else
				{
					if (now->data.pagNum != -1)//�����ݣ��Ƴ�
					{
						pagTable[now->data.pagNum].remove();
					}
					pagTable[pag].visit = 1;
					now->data.pagNum = pag;//����ҳ��
					if (now->data.blockNum == -1)
						now->data.blockNum = rB[k++];
					pagTable[pag].blockNum = now->data.blockNum;
					pagTable[pag].state = true;
					now = now->next;
					break;
				}
				now = now->next;//�滻��ɣ�ָ�����
			}
		}
		else
		{
			LinkNode<PF>*p = now;
			while (true)
			{
				if (p->data.pagNum == pag)
				{
					pagTable[p->data.pagNum].visit = 1;//����,visit��1��ָ�벻��
					break;
				}
				p = p->next;
			}
		}
	}