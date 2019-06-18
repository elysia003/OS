#include "LRU.h"
#include<iostream>
using namespace std;
LRU::LRU(int ps, int PN) :Pross(ps)
{
	PFNUM = PN;
	pagFrame = new PF[PFNUM];
	for (int i = 0; i < PFNUM; i++)
	{
		pagFrame[i].pagNum = -1;
		pagFrame[i].romNum = rB[i];
	}
	num = 0; zd = 0; full = 0;
}
void LRU::Display()
{
	for (int i = 0; i < PFNUM; i++)
	{
		if (pagFrame[i].pagNum != -1)
			cout << "Rom" << pagFrame[i].romNum << ": " << pagFrame[i].pagNum << " time:" << pagTable[pagFrame[i].pagNum].time << endl;
	}
}
void LRU::Visit(int add)
{
	num++;
	int pag = add / 1024;
	if (pagTable[pag].state == false) {
		zd++;
		int max = -1;
		int maxIndex = 0;
		for (int i = 0; i < PFNUM; i++)//更新time，找最大，淘汰
		{
			if (pagFrame[i].pagNum != -1)
				pagTable[pagFrame[i].pagNum].time++;
			else {
				maxIndex = i;
				break;
			}
			if ((pagTable[pagFrame[i].pagNum].time) > max)
			{
				//cout<<pagTable[pagFrame[i].pagNum].time<<"@";
				max = pagTable[pagFrame[i].pagNum].time;
				maxIndex = i;
			}
		}
		//cout << maxIndex;
		if (pagFrame[maxIndex].pagNum != -1)
			pagTable[pagFrame[maxIndex].pagNum].remove();//更新页表
														 //更新页框
		pagFrame[maxIndex].pagNum = pag;
		pagTable[pag].time = 0;
		pagTable[pag].insert(pagFrame[maxIndex].romNum);
	}
	else
	{
		for (int i = 0; i < PFNUM; i++)//更新time
		{
			if (pagFrame[i].pagNum != -1)
				pagTable[pagFrame[i].pagNum].time++;
			if (pagFrame[i].pagNum == pag)
				pagTable[pagFrame[i].pagNum].time = 0;//访问，time清零
		}
	}
}
