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
	LoopList<PF>*pagFrame;//—≠ª∑¡¥±Ì
	LinkNode<PF>*now;//Ã‘Ã≠÷∏’Î
	void Display();
	Clock(int ps, int PN);
	void Visit(int add);
};

