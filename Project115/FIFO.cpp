#include "FIFO.h"
FIFO::FIFO(int ps, int PN) :Pross(ps)
{
	PFNUM = PN;
	num = 0;
	zd = 0;
	k = 0;
};
void FIFO::Display()
{
	pagFrame.display();
}
void FIFO::Visit(int add)
{
	num++;
	int pag = add / 1024;
	if (pagTable[pag].state == false)
	{
		zd++;
		if (pagFrame.Length() < PFNUM)//�п���
		{
			pagTable[pag].romNum = rB[pagFrame.Length()];
			pagTable[pag].state = true;
			PF a(rB[k++], pag);
			pagFrame.push(a);//���
		}
		else
		{
			//cout << (pagFrame.getData(1)).pagNum;
			pagTable[pagFrame.top().pagNum].remove();
			pagTable[pag].insert(pagFrame.top().romNum);
			PF b(pagFrame.top().romNum, pag);
			pagFrame.push(b);//���
			pagFrame.pop();//������
		}
	}
}
