#include <iostream>
#include <string>


using namespace std;

// создаем структуру, которая будет являться очередью

struct Node
{
	int Start;
	int Finish;
	int *storage;

	Node()
	{
		Start = 0;
		Finish = 0;
	}

};

class List
{
public:
	void push(Node* queue, int n);
	int pop(Node* queue, int N);
	void del(Node* queue);

};

// функция добавления элемента в очередь с последующим увеличением индекса массива
void List::push(Node* queue, int n)
{
	queue->storage[queue->Finish] = n;
	queue->Finish++;
}

// функция извлечения элемента из очереди с последующим смещением элементов в начало массива для экономии памяти
int List::pop(Node* queue, int N)
{

	int a = queue->storage[queue->Start];
	for (int i = 0; i < 5; i++)
	{
		queue->storage[i] = queue->storage[i + 1];
	}
	queue->Finish--;
	return a;
}

//  освобождение памяти от структуры данных
void List::del(Node* queue)
{
	delete queue;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	List lst;
	string command;
	Node* queue = new Node;
	cout << "Введите размер очереди: ";
	int N;
	cin >> N;
	queue->storage = new int[N];

	while (cin >> command)
	{
		// добавление элемента
		if (command == "push")
		{
			if (queue->Finish == N)
			{
				cout << "Очередь переполнена!\n";
			}
			else
			{
				int n;
				cout << "\nВведите значение: ";
				cin >> n;
				lst.push(queue, n);
				cout << "Выполнено\n";
			}
			
		}

		// извлечение элемента
		else if (command == "pop")
		{
			if (queue->Finish == 0)
			{
				cout << "Очередь пуста!\n";
			}
			else
				cout << "Элемент " << lst.pop(queue, N) << " извлечен\n";
		}

		// удаление структуры с окончанием программы.
		else if (command == "del")
		{
			lst.del(queue);
			break;
		}


	}
}