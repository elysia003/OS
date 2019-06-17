#include<iostream>
#include<cmath>
#include "List.h"
#include "LoopList.h"
using namespace std;
int BS = 1024;
int rB[31] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30 };
class rateNode;
class pagNode;
class rateNode {
public:
	rateNode() :next(NULL), last(NULL), pN(NULL) {};
	int rate;
	rateNode *next;
	rateNode *last;
	pagNode *pN;
};
class pagNode {
public:
	pagNode(int pn, int rn) :pagNum(pn), romNum(rn), next(NULL), last(NULL) {};
	int pagNum;
	int romNum;
	pagNode *next;
	pagNode *last;
	rateNode *rN;
};
class PT {
public:
	int pagNum;//ҳ��
	int romNum;//������
	bool state;//״̬
	pagNode *pN;//LFU�У��ڵ�ָ�룬ҳ������ϣ����
	int time;//���˶��
	int visit;//����λ
	PT() :time(99999), pagNum(-1), visit(0), state(false), romNum(-1) {};
	PT(int rn, int pn) :romNum(rn), pagNum(pn), time(9999), state(false), visit(0) {}
	void remove() { state = false; romNum = -1; pN = NULL; time = -1; visit = -1; }
	void insert(int rn) { romNum = rn; state = true; }
};
class PF {
public:
	int pagNum;
	int romNum;
	PF(int rn, int pn) :romNum(rn), pagNum(pn) {}
	PF() { pagNum = -1; romNum = -1; }
};
class Pross
{
public:
	int PFNUM;
	int num;
	int zd;
	int size;
	PT *pagTable;
	double res() { return zd*1.0 / num*1.0; }
	void displayTable()
	{
		cout << "ҳ��    " << "������    " << "״̬λ    " << endl;
		for (int i = 0; i < size; i++)
		{
			cout << pagTable[i].pagNum << "        " << pagTable[i].romNum << "            " << pagTable[i].state << endl;
		}
	}
	Pross(int ps) :size(ps / 1024) {
		pagTable = new PT[size];
		for (int i = 0; i < size; i++)
		{
			pagTable[i].pagNum = i;
		}
	}
};
//O(1)
class LFU :public Pross
{
public:
	int nf;
	int k;
	rateNode *head;
	LFU(int ps, int PN) :Pross(ps) { PFNUM = PN; head = new rateNode; nf = 1; k = 0; }
	void Display()
	{
		rateNode *p = head->next;
		while (p != NULL)
		{
			pagNode *q = p->pN;
			while (q != NULL)
			{
				cout << "ROM" << q->romNum << ": " << q->pagNum << "rate: " << p->rate << endl;
				q = q->next;
			}
			p = p->next;
		}
	}
	void removeRate(rateNode *p)
	{
		p->last->next = p->next;
		if (p->next != NULL)
			p->next->last = p->last;
		delete p;
	}
	//�����ڴ棬���ʴ���Ϊ1
	void Insert(int pag, int num)
	{
		if (head->next == NULL || head->next->rate != 1)//������rate��1��
		{
			cout << "*";
			//�½�rate(1���ڵ�
			rateNode *p = new rateNode;
			p->rate = 1;
			if (head->next != NULL)
				head->next->last = p;
			p->next = head->next;
			p->last = head;
			head->next = p;
		}
		//�½�ҳ�ڵ㣬����rate1�ڵ���
		pagNode *q = new pagNode(pag, num);
		q->next = head->next->pN;
		q->last = NULL;
		q->rN = head->next;
		if (head->next->pN != NULL)
			head->next->pN->last = q;
		head->next->pN = q;
		pagTable[pag].pN = q;
		pagTable[pag].state = true;
		pagTable[pag].romNum = q->romNum;
	}
	//���ڴ棬���ʴ���++
	void Updata(pagNode *p)
	{
		//���ӵ���ǰrate+1�ڵ�
		if (p->rN->next == NULL || (p->rN->next->rate) != (p->rN->rate) + 1)
		{
			//û������ڵ㣬�½�
			rateNode *q = new rateNode;
			q->rate = (p->rN->rate) + 1;
			if (p->rN->next != NULL)
				p->rN->next->last = q;
			q->next = p->rN->next;
			q->last = p->rN;
			p->rN->next = q;
		}
		//��ҳ��ڵ���ɾ��
		if (p->last != NULL)
		{
			//���ǵ�һ���ڵ�
			p->last->next = p->next;
			if (p->next != NULL)
				p->next->last = p->last;
		}
		else
		{
			//��һ���ڵ�
			if (p->next != NULL)
				p->next->last = p->last;
			p->rN->pN = p->next;
		}
		//���뵽��һ��rate�ڵ�
		rateNode *t = p->rN->next;
		if (t->pN != NULL)
			t->pN->last = p;
		p->next = t->pN;
		t->pN = p;
		p->last = NULL;
		p->rN = t;
		if (t->last->pN == NULL) {//�ڵ��
			removeRate(t->last);
		}
	}
	void Visit(int add)
	{
		int pag = add / 1024;
		num++;
		if (pagTable[pag].state == false)
		{
			zd++;
			if (nf) {
				Insert(pag, rB[k++]);
				if (k == PFNUM)
					nf = 0;
			}
			else
			{
				cout << '#';
				pagNode *p = head->next->pN;
				cout << head->next->rate;
				while (p->next != NULL)
				{
					p = p->next;
				}
				if (p->last == NULL)
				{
					//��Ӧ��rate��û�������ڵ㣬ɾ��rate
					removeRate(head->next);
				}
				else
					p->last->next = NULL;//ɾ���ýڵ�
				int romNum = p->romNum;
				pagTable[p->pagNum].remove();
				Insert(pag, romNum);//�½ڵ����rate��1����ͷ
				pagTable[pag].romNum = romNum;
				pagTable[pag].state = true;
				delete p;
			}
		}
		else//���ڴ�
		{
			Updata(pagTable[pag].pN);
		}
	}
};
//O(n)
class Clock :public Pross
{
public:
	int k;
	LoopList<PF> *pagFrame;//ѭ������
	LinkNode<PF> *now;//��ָ̭��
	void Display()
	{
		int t = 0;
		LinkNode<PF> *p = pagFrame->head;
		while (p->next != pagFrame->head)
		{
			if (p->data.pagNum != -1)
				cout << "Rom" << (p->data).romNum << ": " << (p->data).pagNum << "  visit:" << pagTable[(p->data).pagNum].visit;
			else
				cout << "Rom" << t << ": " << '*' << "  visit:" << 0;
			if (now == p)
				cout << "<--";
			p = p->next;
			t++;
			cout << endl;
		}
		if (p->data.pagNum != -1)
			cout << "Rom" << (p->data).romNum << " :" << (p->data).pagNum << "  visit:" << pagTable[(p->data).pagNum].visit;
		else
			cout << "Rom" << t << ": " << '*' << "  visit:" << 0;
		if (now == p)
			cout << "<--";
		cout << endl;
	}
	Clock(int ps, int PN) :Pross(ps)
	{
		PFNUM = PN;
		k = 0;
		pagFrame = new LoopList<PF>(PFNUM);
		now = pagFrame->getHead();
	};
	void Visit(int add)
	{
		num++;
		int pag = add / 1024;
		if (pagTable[pag].state == false)
		{
			zd++;
			while (true)
			{
				if (pagTable[now->data.pagNum].visit == 1)
					pagTable[now->data.pagNum].visit = 0;
				else
				{
					if (now->data.pagNum != -1)//�����ݣ��Ƴ�
					{
						pagTable[now->data.pagNum].remove();
					}
					pagTable[pag].visit = 1;
					now->data.pagNum = pag;//����ҳ��
					if (now->data.romNum == -1)
						now->data.romNum = rB[k++];
					pagTable[pag].romNum = now->data.romNum;
					pagTable[pag].state = true;
					now = now->next;
					break;
				}
				now = now->next;//�滻��ɣ�ָ�����
			}
		}
		else
		{
			LinkNode<PF>*p = now;
			while (true)
			{
				if (p->data.pagNum == pag)
				{
					pagTable[p->data.pagNum].visit = 1;//����,visit��1��ָ�벻��
					break;
				}
				p = p->next;
			}
		}
	}
};
//O(n)
class LRU :public Pross
{
public:
	PF* pagFrame;
	int full;
	LRU(int ps, int PN) :Pross(ps)
	{
		PFNUM = PN;
		pagFrame = new PF[PFNUM];
		for (int i = 0; i < PFNUM; i++)
			pagFrame[i].romNum = rB[i];
		num = 0; zd = 0; full = 0;
	}
	void Display()
	{
		for (int i = 0; i < PFNUM; i++)
		{
			if (pagFrame[i].pagNum != -1)
				cout << "Rom" << pagFrame[i].romNum << ": " << pagFrame[i].pagNum << " time:" << pagTable[pagFrame[i].pagNum].time << endl;
		}
		cout << endl;
	}
	void Visit(int add)
	{
		num++;
		int pag = add / 1024;
		if (pagTable[pag].state == false) {
			zd++;
			int max = -1;
			int maxIndex = 0;
			for (int i = 0; i < PFNUM; i++)//����time���������̭
			{
				if (pagFrame[i].pagNum != -1)
					pagTable[pagFrame[i].pagNum].time++;
				if ((pagTable[pagFrame[i].pagNum].time) > max)
				{
					max = pagTable[pagFrame[i].pagNum].time;
					maxIndex = i;
				}
			}
			if (pagFrame[maxIndex].pagNum != -1)
				pagTable[pagFrame[maxIndex].pagNum].remove();//����ҳ��
			//����ҳ��
			pagFrame[maxIndex].pagNum = pag;
			pagTable[pagFrame[maxIndex].pagNum].time = 0;
			pagTable[pag].insert(pagFrame[maxIndex].romNum);
		}
		else
		{
			for (int i = 0; i < PFNUM; i++)//����time
			{
				if (pagFrame[i].pagNum != -1)
					pagTable[pagFrame[i].pagNum].time++;
				if (pagFrame[i].pagNum == pag)
					pagTable[pagFrame[i].pagNum].time = 0;//���ʣ�time����
			}
		}
	}
};
//O(1)
class FIFO :public Pross
{
public:
	List<PF>pagFrame;
	int k;
	FIFO(int ps, int PN) : Pross(ps)
	{
		PFNUM = PN;
		num = 0; zd = 0; k = 0;
	};
	void Display()
	{
		pagFrame.display();
	}
	void Visit(int add)
	{
		num++;
		int pag = add / 1024;
		if (pagTable[pag].state == false)
		{
			zd++;
			if (pagFrame.Length() < PFNUM)//�п���
			{
				pagTable[pag].romNum = rB[pagFrame.Length()];
				pagTable[pag].state = true;
				pagFrame.push(PF(rB[k++], pag));//���
			}
			else
			{
				//cout << (pagFrame.getData(1)).pagNum;
				pagTable[pagFrame.top().pagNum].remove();
				pagTable[pag].insert(pagFrame.top().romNum);
				pagFrame.push(PF(pagFrame.top().romNum, pag));//���
				pagFrame.pop();//������
			}
		}
	}
};
int main()
{
	cout << "1.FIFO" << endl;
	cout << "2.LRU" << endl;
	cout << "3.LFU" << endl;
	cout << "4.Clock" << endl;
	int k;
	cin >> k;
	Pross *a;
	switch (k)
	{
	case 1: {
		a = new FIFO(99300, 5), break;
	}
	case 2: {
		a = new LRU(99300, 5), break;
	}
	case 3: {
		a = new LFU(99300, 5), break;
	}
	case 4: {
		a = new Clock(99300, 5), break;
	}
	default:
		break;
	}
	int add;
	while (cin >> add, add != -1)
	{
		a.Visit(add);
		a.Display();
	}
	cout << "ȱҳ��" << a.res();
	getchar(); getchar(); getchar(); getchar(); getchar(); getchar(); getchar(); getchar(); getchar(); getchar();
}