#include<iostream>
#include<ctime>
#include <stdlib.h>
#include<time.h>
using namespace std;

class STACK
{
public:
	STACK();
	~STACK();
	void dobavlenie(int zx);
	int Vershina();
	int Nsize();
	void Vivod();
	void Udalenie();
private:
	int* stack;
	int N;
};

STACK::STACK()
{
	N = 0;
}

STACK::~STACK()
{
	
}
void STACK::dobavlenie(int zx)
{
	int* tmp;
	tmp = stack;
	stack = new int[N + 1];
	N++;
	for (int i = 0; i < N - 1; i++)
	{
		stack[i] = tmp[i];
	}
	stack[N - 1] = zx;
	if (N > 1)
	{
		delete[] tmp;
	}
}
int STACK::Vershina()
{
	if (N == 0)
	{
		return 0;
	}
	N--;
	return stack[N];
}
int STACK::Nsize()
{
	return N;
}
void STACK::Vivod()
{
	int* p;
	p = stack;
	for (int i = 0; i < N; i++)
	{
		cout <<"№["<< i <<"] = "<< *p << endl;
		p++;
	}
	cout << endl;
}

void STACK::Udalenie()
{
	if (N > 0)
	{
		delete[] stack;
	}
}

int main()
{	
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	STACK st1;
	int aN;
	cout<<"Укажитеразмерстека: ";
	cin >> aN;
	for (int i = 0; i < aN; i++)
	{
		st1.dobavlenie(rand() % 100);
	}
	cout<<"Заполненный стек st1:"<< endl;
	st1.Vivod();
	cout<<"Добавить значение 100 на вершину."<<endl;
	st1.dobavlenie(100);
	st1.Vivod();
	STACK st2;
	st2 = st1;
	cout<<"Вершина стека: "<< st1.Vershina() << endl;
	st1.Vivod();
	cout<<"Стек st2:"<< endl;
	st2.Vivod();
	st1.Udalenie();
}

