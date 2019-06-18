#pragma once
#include "PT.h"
class Pross
{
public:
	int *rB;
	int PFNUM;
	int num;
	int zd;
	int size;
	PT *pagTable;
	virtual void Visit(int add) {};
	virtual void Display() {};
	double res();
	void displayTable();
	Pross(int ps);
};

