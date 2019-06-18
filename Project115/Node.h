#pragma once
#include<iostream>
class pagNode;
class rateNode {
public:
	rateNode() :next(NULL), last(NULL), pN(NULL) {};
	int rate;
	rateNode*next;
	rateNode*last;
	pagNode *pN;//页表节点头
	pagNode *pNE;//页表节点尾巴
};
class pagNode {
public:
	pagNode(int pn, int rn) :pagNum(pn), romNum(rn), next(NULL), last(NULL) {};
	pagNode() {}
	int pagNum;
	int romNum;
	pagNode*next;
	pagNode*last;
	rateNode*rN;//访问次数节点
};
