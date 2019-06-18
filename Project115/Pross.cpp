#include "Pross.h"
#include<iostream>
using namespace std;
double Pross::res() {
	return zd*1.0 / num*1.0;
};
void Pross::displayTable()
{
	cout << "Ò³ºÅ    " << "ÎïÀí¿éºÅ    " << "×´Ì¬Î»    " << endl;
	for (int i = 0; i < size; i++)
	{
		cout << pagTable[i].pagNum << "        " << pagTable[i].romNum << "            " << pagTable[i].state << endl;
	}
};
Pross::Pross(int ps) :size(ps / 1024) {
	pagTable = new PT[size];
	for (int i = 0; i < size; i++)
	{
		pagTable[i].pagNum = i;
	}
	rB = new int[500];
	for (int i = 0; i < 500; i++)
		rB[i] = i;
};