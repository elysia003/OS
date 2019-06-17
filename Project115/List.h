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
	} //���캯��
	List(const T &x) { head = new LinkNode<T>(x); }
	List(List<T> &L);		 //���ƹ��캯��
	~List() { makeEmpty(); } //��������
	void makeEmpty();		 //��������Ϊ�ձ�
	int Length();			 //��������ĳ���
	LinkNode<T> *getHead() const { return head; }
	LinkNode<T> *Search(T x);   //������xԪ��
	LinkNode<T> *Locate(int i); //��λ��i��Ԫ��
	T& getData(int i);  //ȡ����iԪ��ֵ
	void setData(int i, T &x);  //���µ�iԪ��ֵ
	bool Insert(int i, T &x);   //�ڵ�iԪ�غ����
	bool Remove(int i);   //ɾ����i��Ԫ��
	bool IsEmpty() const		//�б��Ƿ�Ϊ��
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
	void inputFront(T endTag); //ǰ�彨������
	void inputRear(T endTag);  //��彨������
	void output();
	LinkNode<T> getHead() { return head; }
	List<T> &operator=(List<T> &L); //���ظ�ֵ�����
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
/*���ƹ���*/
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
/*��������Ϊ�ձ�*/
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
/*��������ĳ���*/
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
/*������xԪ��*/
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
/*��λ��i��Ԫ��*/
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
/*ȡ����iԪ��ֵ*/
template <class T>
T& List<T>::getData(int i)
{
	T x;
	LinkNode<T> *t = Locate(i);
	return t->data;
}
/*���µ�iԪ��ֵ*/
template <class T>
void List<T>::setData(int i, T &x)
{
	LinkNode<T> *t = Locate(i);
	if (t != NULL)
	{
		t->data = x;
	}
}
/*�ڵ�iԪ�غ����*/
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
/*ɾ����i��Ԫ��*/
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
/*ǰ�彨������*/
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
/*��彨������*/
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
/*���*/
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
/*���ظ�ֵ�����*/
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
