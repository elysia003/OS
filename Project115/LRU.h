#pragma once
#include "Pross.h"
#include "PF.h"
class LRU :
	public Pross
{
public:
	PF* pagFrame;
	int full;
	LRU(int ps, int PN);
	void Display();
	void Visit(int add);
};

