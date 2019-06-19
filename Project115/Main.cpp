#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include<iomanip>
#include<Windows.h>
#include<time.h>
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
			a = new FIFO(200000, 3);
			break;
		}
		case 2: {
			a = new LRU(1000000, 3);
			break;
		}
		case 3: {
			a = new Quick_LRU(99300, 3);
			break;
		}
		case 4: {
			a = new LFU(99300, 3);
			break;
		}
		case 5: {
			a = new Clock(99300, 3);
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
		system("cls");
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
int a[1000000];
void tt(string path, Pross *p) {
	//FILE *fp = fopen(path.data(), "a");
		for (int j = 0; j < 5900; j++)
		{
			p->Visit(a[j]);
		}
		double res = p->res();
		//fprintf(fp, "%lf\n", res);
	//fclose(fp);
}
void test()
{
	FILE *fp = fopen("E:\\OS\\data.txt", "r");
	while (k<5900)
	{
		int t;
		fscanf(fp, "%d", &t);
		a[k++] = t;
	}
	fclose(fp);
	//////////////////////////////////////////
	clock_t start = clock();
	for (int i = 1; i < 500; i++)
		tt("E:\\OS\\fifo.txt", new FIFO(1000000,i));
	cout << "*";
	double tim = double(clock() - start) / CLK_TCK;
	cout << "FIFO:"<<tim<<endl;
	start = clock();
	for (int i = 1; i < 500; i++)
		tt("E:\\OS\\lru.txt", new LRU(1000000,i));
	cout << "*";
	tim = double(clock() - start) / CLK_TCK;
	cout << "LRU:"<<tim<<endl;
	start = clock();
	for (int i = 1; i < 500; i++)
		tt("E:\\OS\\lfu.txt", new LFU(1000000,i));
	cout << "*";
	tim = double(clock() - start) / CLK_TCK;
	cout << "LFU:"<<tim<<endl;
	start = clock();
	for (int i = 1; i < 500; i++)
		tt("E:\\OS\\clock.txt", new Clock(1000000, i));
	tim = double(clock() - start) / CLK_TCK;
	cout << '*';
	cout << "Clock:"<<tim<<endl;
	start = clock();
	for (int i = 1; i < 500; i++)
		tt("E:\\OS\\Q_LRU.txt", new Quick_LRU(1000000, i));
	tim = double(clock() - start) / CLK_TCK;
	cout << '*';
	cout << "Q_LRU:"<<tim;
	getchar(); getchar(); getchar();
}