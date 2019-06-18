#pragma once
#include<iostream>
class pagNode;
class rateNode {
public:
	rateNode() :next(NULL), last(NULL), pN(NULL) {};
	int rate;
	rateNode*next;
	rateNode*last;
	pagNode *pN;
};
class pagNode {
public:
	pagNode(int pn, int rn) :pagNum(pn), romNum(rn), next(NULL), last(NULL) {};
	pagNode() {}
	int pagNum;
	int romNum;
	pagNode*next;
	pagNode*last;
	rateNode*rN;
};
