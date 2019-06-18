#pragma once
#include"Node.h"
class PT{
public:
	int pagNum;//页号
	int romNum;//物理块号
	bool state;//状态
	pagNode*pN;//LFU中，节点指针，页表作哈希表用
	int time;//待了多久
	int visit;//访问位
	PT();
	PT(int rn, int pn);
	void remove();
	void insert(int rn);
};

