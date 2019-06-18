#pragma once
class PF {
public:
	int pagNum;
	int romNum;
	PF(int rn, int pn) :romNum(rn), pagNum(pn) {}
	PF() {pagNum = -1;romNum = -1;}
};
