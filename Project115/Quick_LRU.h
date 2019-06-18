#pragma once
#include "Pross.h"
class Quick_LRU :
	public Pross
{
public:
	int nf;
	int k;
	pagNode *head;
	pagNode *end;
	Quick_LRU(int ps, int PN);
	void Display();
	void Insert(int pn, int rn);
	void Updata(int pag);
	void Visit(int add);
};

