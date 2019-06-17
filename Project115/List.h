#pragma once
#include <iostream>
#include <stdlib.h>
#include<queue>	
using namespace std;
template <class T>
struct LinkNode
{
	T data;
	LinkNode<T> *next;
	LinkNode<T>()
	{
		next = NULL;
	}
	LinkNode<T>(const T &item, LinkNode<T> *ptr = NULL)
	{
		data = item;
		next = ptr;
	}
};
template <class T>
class List
{
protected:
	LinkNode<T> *head;

public:
	List()
	{
		head = new LinkNode<T>;
		head->next = NULL;
	} //构造函数
	List(const T &x) { head = new LinkNode<T>(x); }
	List(List<T> &L);		 //复制构造函数
	~List() { makeEmpty(); } //析构函数
	void makeEmpty();		 //将链表置为空表
	int Length();			 //计算链表的长度
	LinkNode<T> *getHead() const { return head; }
	LinkNode<T> *Search(T x);   //搜索含x元素
	LinkNode<T> *Locate(int i); //定位第i个元素
	T& getData(int i);  //取出第i元素值
	void setData(int i, T &x);  //更新第i元素值
	bool Insert(int i, T &x);   //在第i元素后插入
	bool Remove(int i);   //删除第i个元素
	bool IsEmpty() const		//判表是否为空
	{
		return head->next == NULL ? true : false;
	}
	void push(T &x)
	{
		Insert(Length(), x);
	}
	void pop()
	{
		Remove(1);
	}
	T& top()
	{
		return head->next->data;
	}
	void inputFront(T endTag); //前插建立链表
	void inputRear(T endTag);  //后插建立链表
	void output();
	LinkNode<T> getHead() { return head; }
	List<T> &operator=(List<T> &L); //重载赋值运算符
	void display()
	{
		LinkNode<T> *p = head->next;
		while (p != NULL)
		{
			cout << "Rom "<<(p->data).romNum <<": ";
			cout<<(p->data).pagNum<<"   ";
			cout << endl;
			p = p->next;
		}
	}
};
/*复制构造*/
template <class T>
List<T>::List(List<T> &L)
{
	LinkNode<T> *src = L.getHead();
	LinkNode<T> *des = head = new LinkNode<T>;
	head->next = L.getHead();
	while (src->next != NULL)
	{
		src = src->next;
		des->next = new LinkNode<T>(src->data);
		des = des->next;
	}
	des->next = NULL;
}
/*将链表置为空表*/
template <class T>
void List<T>::makeEmpty()
{
	LinkNode<T> *temp = NULL;
	while (head->next != NULL)
	{
		temp = head->next;
		head->next = head->next->next;
		delete temp;
	}
}
/*计算链表的长度*/
template <class T>
int List<T>::Length()
{
	LinkNode<T> *t = head;
	int n = 0;
	while (t->next != 0)
	{
		n++;
		t = t->next;
	}
	return n;
}
/*搜索含x元素*/
template <class T>
LinkNode<T> *List<T>::Search(T x)
{
	LinkNode<T> *t = head->next;
	while (t != NULL)
	{
		if (t->data == x)
		{
			return t;
		}
		t = t->next;
	}
	return t;
}
/*定位第i个元素*/
template <class T>
LinkNode<T> *List<T>::Locate(int i)
{
	LinkNode<T> *t = head;
	while (t != NULL && i--)
	{
		t = t->next;
	}
	return t;
}
/*取出第i元素值*/
template <class T>
T& List<T>::getData(int i)
{
	T x;
	LinkNode<T> *t = Locate(i);
	return t->data;
}
/*更新第i元素值*/
template <class T>
void List<T>::setData(int i, T &x)
{
	LinkNode<T> *t = Locate(i);
	if (t != NULL)
	{
		t->data = x;
	}
}
/*在第i元素后插入*/
template <class T>
bool List<T>::Insert(int i, T &x)
{
	LinkNode<T> *t = Locate(i);
	if (t == NULL)
	{
		return false;
	}
	LinkNode<T> *p = new LinkNode<T>(x, t->next);
	if (p == NULL)
	{
		return false;
	}
	t->next = p;
	return true;
}
/*删除第i个元素*/
template <class T>
bool List<T>::Remove(int i)
{
	LinkNode<T> *t = Locate(i - 1);
	if (t == NULL || t->next == NULL)
	{
		return false;
	}
	LinkNode<T> *del = t->next;
	t->next = (t->next)->next;
	delete del;
	return true;
}
/*前插建立链表*/
template <class T>
void List<T>::inputFront(T endTag)
{
	T val;
	LinkNode<T> *t = NULL;
	cin >> val;
	while (val != endTag)
	{
		t = new LinkNode<T>(val, head->next);
		if (t == NULL)
		{
			exit(1);
		}
		head->next = t;
		cin >> val;
	}
}
/*后插建立链表*/
template <class T>
void List<T>::inputRear(T endTag)
{
	T val;
	LinkNode<T> *t = NULL, *tail = head;
	cin >> val;
	makeEmpty();
	while (val != endTag)
	{
		t = new LinkNode<T>(val);
		if (t == NULL)
		{
			exit(1);
		}
		tail->next = t;
		tail = t;
		cin >> val;
	}
}
/*输出*/
template <class T>
void List<T>::output()
{
	LinkNode<T> *t = head->next;
	while (t != NULL)
	{
		cout << (t->data);
		t = t->next;
		if (t != NULL)
		{
			cout << "-->";
		}
	}
}
/*重载赋值运算符*/
template <class T>
List<T> &List<T>::operator=(List<T> &L)
{
	if (&L != this)
	{
		makeEmpty();
		LinkNode<T> *src = L.getHead();
		LinkNode<T> *des = new LinkNode<T>;
		head = des;
		while (src->next != NULL)
		{
			src = src->next;
			des->next = new LinkNode<T>(src->data);
			des = des->next;
		}
		des->next = NULL;
	}
	return *this;
}
