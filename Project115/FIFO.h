#pragma once
#include "Pross.h"
#include "List.h"
#include"PF.h"
#include"PT.h"
class FIFO :
	public Pross
{
public:
	List<PF>pagFrame;
	int k;
	FIFO(int ps, int PN);
	void Display();
	void Visit(int add);
};

