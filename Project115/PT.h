#pragma once
#include"Node.h"
class PT{
public:
	int pagNum;//ҳ��
	int romNum;//������
	bool state;//״̬
	pagNode*pN;//LFU�У��ڵ�ָ�룬ҳ������ϣ����
	int time;//���˶��
	int visit;//����λ
	PT();
	PT(int rn, int pn);
	void remove();
	void insert(int rn);
};

