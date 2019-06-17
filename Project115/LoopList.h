#pragma once
#include <iostream>
#include <stdlib.h>
#include<queue>	
using namespace std;
template <class T>
class LoopList
{
public:
	LinkNode<T> *head;
	LoopList()
	{
		head = new LinkNode<T>;
		head->next = head;
	} //¹¹Ôìº¯Êý
	LoopList(int n)
	{
		int nn=n-1;
		head = new LinkNode<T>;
		LinkNode<T> *p = head;
		while (nn--)
		{
			p->next = new LinkNode<T>;
			p = p->next;
		}
		p->next = head;
	}
	LinkNode<T> *getHead() const { return head;}
	void display()
	{

	}
};
