#pragma once
#include<iostream>
class pagNode;
class rateNode {
public:
	rateNode() :next(NULL), last(NULL), pN(NULL) {};
	int rate;
	rateNode*next;
	rateNode*last;
	pagNode *pN;//ҳ��ڵ�ͷ
	pagNode *pNE;//ҳ��ڵ�β��
};
class pagNode {
public:
	pagNode(int pn, int rn) :pagNum(pn), blockNum(rn), next(NULL), last(NULL) {};
	pagNode() {}
	int pagNum;
	int blockNum;
	pagNode*next;
	pagNode*last;
	rateNode*rN;//���ʴ����ڵ�
};
