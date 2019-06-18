#pragma once
#include "Pross.h"
class LFU :
	public Pross
{
public:
	int nf;
	int k;
	rateNode*head;
	LFU(int ps, int PN);
	void Display();
	void removeRate(rateNode*p);
	void Insert(int pag, int num);
	void Updata(pagNode*p);
	void Visit(int add);
};

