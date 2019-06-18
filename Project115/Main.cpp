#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include<iomanip>
#include<Windows.h>
#include "Pross.h"
#include "LFU.h"
#include "Clock.h"
#include "FIFO.h"
#include "Quick_LRU.h"
#include "LRU.h"
#include "F_test.cpp"
using namespace std;
int BS = 1024;
//O(n)
void test();
int main()
{
	int k = 0;
	while (1) {
		system("cls");
		cout << "1.FIFO" << endl;
		cout << "2.LRU" << endl;
		cout << "3.Quick_LRU" << endl;
		cout << "4.LFU" << endl;
		cout << "5.Clock" << endl;
		cout << "6.Test" << endl;
		int k;
		cin >> k;
		Pross *a = NULL;
		switch (k)
		{
		case 1: {
			a = new FIFO(200000, 5);
			break;
		}
		case 2: {
			a = new LRU(99300, 5);
			break;
		}
		case 3: {
			a = new Quick_LRU(99300, 5);
			break;
		}
		case 4: {
			a = new LFU(99300, 5);
			break;
		}
		case 5: {
			a = new Clock(99300, 5);
			break;
		}
		case 6: {
			test();
			break;
		}
		default:
			break;
		}
		if (k == 6)
			continue;
		int add;
		while (cin >> add, add != -1)
		{
			a->Visit(add);
			a->Display();
		}
		cout << a->res();
		getchar();
		getchar();
	}
}

int k = 0;
int a[40000];
void tt(string path, Pross *p) {
	FILE *fp = fopen(path, "a");
	for (int i = 3; i < 300; i += 10) {
		for (int j = 0; j < 4800; j++)
		{
			p->Visit(a[j]);
		}
		double res = p->res();
		cout << i << ":" << res << endl;
		fprintf(fp, "%lf\n", res);
	}
	fclose(fp);
}
void test()
{
	FILE *fp = fopen("E:\\OS\\data.txt", "r");
	FILE *fifo = fopen("E:\\OS\\fifo.txt", "a");
	while (k<4800)
	{
		int t;
		fscanf(fp, "%d", &t);
		a[k++] = t;
		//cout <<k<<"  "<< t << endl;
	}
	fclose(fp);
	//////////////////////////////////////////
}