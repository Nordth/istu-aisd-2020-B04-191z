#include <iostream>
#include <string>

using namespace std;


// Создаем структуру, которая является звеном списка
struct Node
{
	Node* next=NULL, *prev=NULL;
	int value;
};


//Функция добавления элемента в список
//Передается указатель на первый элемент списка и значение нового элемента

Node* Add(Node* first, int val)
{
	if (first == NULL)
	{
		// Создание нового списка
		first = new Node;
		first->value = val;
	}
	else
	{
		// Поиск свободного места в списке и добавление элемента после него
		Node* n = first;
		while (n->next != NULL)
		{
			n = n->next;
		}
		Node* newNode = new Node;
		n->next = newNode;
		newNode->value = val;
		newNode->prev = n;
	}
	return first;
}

// Функция печати всего списка
// Передается ссылка на первый элемент

Node* print(Node* first)
{
	if (first == NULL)
		cout << "Список пуст" << endl;
	else
	{
		Node* n = first;
		while (n != NULL)
		{
			cout << "[" << n->value << "]" << "\t";
			n = n->next;
		}
	}
	cout << endl;
	return first;
}

// Функция поиска элемента  в списке
// Передается ссылка на первый элемент, значение для поиска и переменная "Флаг"

Node* find(Node* first, int val, bool* flag)
{
	Node* n = first;
	if (first == NULL)
		cout << "Список пуст" << endl;
	else
	{
		while (n != NULL)
		{
			if (n->value == val)
			{
				*flag = true;
				break;
			}
			else
			{
				*flag = false;
				n = n->next;
			}
			
		}		
	}
	
	return n;
}

// Функция вывода предыдущего и следующего элементов найденного значения списка
// Передается ссылка на найденный элемент
Node* printFind(Node* findElement)
{
	if (findElement->prev == NULL)
		cout << "Предыдущего значения нет" << endl;
	else
		cout << "Предыдущее значение: " << findElement->prev->value << endl;
	if (findElement->next == NULL)
		cout << "Следующего значения нет." << endl;
	else
		cout << "Следующее значение: " << findElement->next->value << endl;
	return findElement;
}


// Функция вставки элемента после найденного элемента списка
// передается ссылка на найденный элемент и значение нового элемента
Node* pasteNode(Node* findElement, int val)
{
	Node* newNode = new Node;
	newNode->value = val;
	//  если найденный элемент не последний, предыдущий элемент следующего элемента - новый элемент
	if(findElement->next!=NULL)
		findElement->next->prev = newNode; 
	// если последний, следующего элемента нет
	newNode->next = findElement->next; 
	// следующий элемент найденного - новый элемент
	findElement->next = newNode; 
	// предыдущий элемент нового - найденный элемент
	newNode->prev = findElement; 
	return findElement;
}

// Функция удаления списка
// передается ссылка на первый элемент списка
Node* deleteNode(Node* first)
{
	// сохранение ссылки на следующий элемент
	Node* n = first->next;
	// удалять, пока есть элементы
	while (first)
	{
		n = first->next;
		delete first;
		first = n;
	}
	return first;
}

// Функция удаления выбранного элемента из списка
// передается ссылка на найденный элемент и ссылка на первый элемент
Node* remove(Node* findElement,Node*first)
{
	//найденный элемент первый или последний
	if ((findElement->next == NULL) || (findElement->prev == NULL))
	{
		// в списке всего 1 элемент
		if ((findElement->next == NULL) && (findElement->prev == NULL))
			first = NULL;
		else
		{
			if (findElement == first)
			{
				first = findElement->next;
			}
			else
			{
				if (findElement->next == NULL)
				{
					findElement->prev->next = NULL;
				}
			}
		}
	}
	// найденный элемент не первый, не последний и  не единственный в списке
	else
	{
		findElement->next->prev = findElement->prev;
		findElement->prev->next = findElement->next;
	}
	delete findElement;
	return first;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	Node* first = NULL;
	string choose;
	int val;
	Node* findElement = NULL;
	bool flag = false;
	bool* flagPtr = &flag;
	cout << "Введите help, чтобы показать список команд" << endl;

	while (cin >> choose)
	{
		cout << endl;
		if (choose == "help")
		{
			cout << "add - добавить элемент в список\nprint - показать элементы списка\nfind - поиск элемента списка\n paste - вставить новый элемент списка после выбранного\n delete - удалить список, закончить программу" << endl;

		}

		if (choose == "add")
		{
			cout << "Введите значение" << endl;
			cin >> val;
			first = Add(first,val);
			cout << "Успешно" << endl;
		}

		if (choose == "print")
		{
			first=print(first);
		}

		if (choose == "find")
		{
			cout << "Введите значение для поиска: ";
			cin >> val;
			cout << endl;
			findElement = find(first, val, flagPtr);
			if (*flagPtr == true)
			{
				cout << "Значение " << val << " найдено" << endl;
				findElement = printFind(findElement);
			}
			else
			{
				cout << "Значение не найдено." << endl;
			}
		}

		if (choose == "paste")
		{
			cout << "Введите значение после которого необходимо осуществить вставку: ";
			cin >> val;
			cout << endl;
			findElement = find(first, val, flagPtr);
			if (*flagPtr == true)
			{
				cout << "Введите вставляемое значение" << endl;
				cin >> val;
				findElement = pasteNode(findElement, val);
				cout << "Успешно" << endl;
			}
			else
			{
				cout << "Значение не найдено." << endl;
			}
		}

		if (choose == "delete")
		{
			first = deleteNode(first);
		}

		if (choose == "remove")
		{
			cout << "Введите удаляемое значение: ";
			cin >> val;
			cout << endl;
			findElement = find(first, val,flagPtr);
			if (*flagPtr == true)
			{
				first = remove(findElement,first);

			}
			else
			{
				cout << "Значение не найдено. Удаление невозможно." << endl;
			}

		}
	}
}