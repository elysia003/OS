#pragma once
class PF {
public:
	int pagNum;
	int blockNum;
	PF(int rn, int pn) :blockNum(rn), pagNum(pn) {}
	PF() {pagNum = -1;blockNum = -1;}
};
