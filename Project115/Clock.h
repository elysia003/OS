#pragma once
#include"LoopList.h"
#include"Node.h"
#include"List.h"
#include "Pross.h"
#include"PF.h"
class Clock :
	public Pross
{
public:
	int k;
	LoopList<PF>*pagFrame;//ѭ������
	LinkNode<PF>*now;//��ָ̭��
	void Display();
	Clock(int ps, int PN);
	void Visit(int add);
};

