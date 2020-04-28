#include<iostream>
#include<ctime>
#include <stdlib.h>
#include<time.h>
using namespace std;

class List
{
public:
	List();
	~List();
	void dobavlenie(int data);
	int&operator[](const int index);
	int SizeN();
	void ochistka();
	void dobav_po_index(int value, int index);
	void udal_po_index(int index);

private:
	class Node
	{
	public:
		Node* Next;
		int data;
		Node(int data, Node* Next = 0)
		{
			this->data = data;
			this->Next = Next;
		}
	};
	Node* head;
	int N;
};

List::List()
{
	N = 0;
	head = 0;

}
List::~List()
{

}

void List::dobavlenie(int data)
{
	if (head == 0)
	{
		head = new Node(data);
	}
	else
	{
		Node* a = this->head;
		while (a->Next != 0)
		{
			a = a->Next;
		}
		a->Next = new Node(data);
	}
	N++;
}

int& List::operator[](const int index)
{
	int b = 0;
	Node* aHead = this->head;
	while (aHead!= 0)
	{
		if (b == index)
		{
			return aHead->data;
		}
		aHead = aHead->Next;
		b++;
	}
}


int List::SizeN()
{
	return N;
}

void List::ochistka()
{
	while (N != 0)
	{
		Node* bHead = head;
		head = head->Next;
		delete bHead;
		N--;
	}
}

void List::dobav_po_index(int data, int index)
{ 
	Node* cHead = this -> head;
	for (int i = 0; i <index - 1; i++)
	{
		cHead = cHead->Next;
	}
	Node* dHead = new Node(data, cHead->Next);
	cHead->Next = dHead;
	N++;
}

void List::udal_po_index(int index)
{
		Node* cHead = this->head;
		for (int i = 0; i <index - 1; i++)
		{
			cHead = cHead->Next;
		}
		Node* eHead = cHead->Next;
		cHead->Next = eHead -> Next;
		N--;
		delete eHead;
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	List lst;
	for (int i = 0; i < 5; i++)
	{
		lst.dobavlenie(rand() % 100);
	}
	cout<<"Заполненный список:"<< endl;
	for (int i = 0; i < lst.SizeN(); i++)
	{
		cout << lst[i]<<" ";
	}
	cout << endl;
	cout<<"Добавляем число 5 в конец списка:"<<endl;
	lst.dobavlenie(5);
	cout<<"Число с индексом 3: "<<lst[3]<<endl;
	cout<<"Добавляем число 77 в индекс 2:"<<endl;
	lst.dobav_po_index(77, 2);
	cout<<"Удаляем число c индексом 4:"<<endl;
	lst.udal_po_index(4);
	cout<<"Список:"<< endl;
	for (int i = 0;  i < lst.SizeN();  i++)
	{
		cout << lst[i]<<" ";
	}
	lst.ochistka();
	return 0;
}

