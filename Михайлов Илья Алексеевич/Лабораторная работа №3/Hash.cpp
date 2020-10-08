#include <iostream>
#include <string>
using namespace std;

int size_hash;
int element = 0;
bool boo = false;

struct HASH_ELL
{
	int value;
	string key;
	HASH_ELL* next = NULL;
};

void Prin(HASH_ELL*);
void Output(HASH_ELL*, string);
void Delet_HASH_ELL(HASH_ELL*);
HASH_ELL* Siz(HASH_ELL*);
HASH_ELL* New_Hash(HASH_ELL*);
HASH_ELL* ADD(HASH_ELL*, int, string);
HASH_ELL* Delet_znach(HASH_ELL*, string);

HASH_ELL* Siz(HASH_ELL* hash)
{
	if (size_hash == 0)
	{
		return hash;
	}
	else
	{
		hash = new HASH_ELL[size_hash];
		return hash;
	}
}

HASH_ELL* New_Hash(HASH_ELL* hash)
{
	HASH_ELL* old_hash = hash;
	size_hash = size_hash * 2;
	hash = Siz(hash);
	element = 0;
	for (int i = 0; i < size_hash / 2; i++)
	{
		if (old_hash[i].key != "")
		{
			HASH_ELL* arr = new HASH_ELL();
			arr->key = old_hash[i].key;
			arr->value = old_hash[i].value;
			arr->next = old_hash[i].next;
			while (arr)
			{
				hash = ADD(hash, arr->value, arr->key);
				arr = arr->next;
			}
		}
	}
	return hash;
	delete[] old_hash;
}

HASH_ELL* Delet_znach(HASH_ELL* hash, string key)
{
	int size_int = key.length() % size_hash;
	if (hash[size_int].key != "")
	{
		if (hash[size_int].key == key)
		{
			if (!hash[size_int].next)
			{
				boo = true;
				hash[size_int].key = "";
				element--;
				return hash;
			}
			else
			{
				boo = true;
				HASH_ELL* att = hash[size_int].next;
				hash[size_int].key = att->key;
				hash[size_int].value = att->value;
				hash[size_int].next = att->next;
				element--;
				delete att;
				return hash;
			}
		}
		else
		{
			HASH_ELL* arr = hash + size_int;
			while (arr)
			{
				if (arr->next->key == key)
				{
					boo = true;
					HASH_ELL* att = arr->next;
					arr->next = att->next;
					delete att;
					return hash;
				}
				else
				{
					arr = arr->next;
				}
			}
		}
	}
	return hash;
}

HASH_ELL* ADD(HASH_ELL* hash, int value, string key)
{
	HASH_ELL* ell = new HASH_ELL();
	ell->key = key;
	ell->value = value;
	int size_int = key.length() % size_hash;
	if (hash[size_int].key == "")
	{
		element++;
		hash[size_int] = *ell;
	}
	else
	{
		HASH_ELL* arr = hash + size_int;
		while (arr)
		{
			if (!arr->next)
			{
				arr->next = ell;
				return hash;
			}
			arr = arr->next;
		}
	}
	if (element > (size_hash / 2))
	{
		hash = New_Hash(hash);
	}
	return hash;
}

void Prin(HASH_ELL* hash)
{
	for (int i = 0; i < size_hash; i++)
	{
		cout << i << " = ";
		if (hash[i].key != "")
		{
			HASH_ELL* arr = hash + i;
			while (arr)
			{
				cout << arr->key << "[" << arr->value << "], ";
				arr = arr->next;
			}
		}
		else
		{
			cout << "(Пусто)";
		}
		cout << endl;
	}
	cout << endl;
}

void Output(HASH_ELL* hash, string key)
{
	int size_int = key.length() % size_hash;
	if (hash[size_int].key != "")
	{
		HASH_ELL* arr = hash + size_int;
		while (arr)
		{
			if (arr->key == key)
			{
				boo = true;
				cout << "Значение по ключу: " << arr->key << "[" << arr->value << "]" << endl;
				return;
			}
			else
			{
				arr = arr->next;
			}
		}
	}
	return;
}

void Delet_HASH_ELL(HASH_ELL* hash)
{
	for (int i = 0; i < size_hash; i++)
	{
		if (hash[i].key != "")
		{
			HASH_ELL* arr = hash[i].next;
			while (arr)
			{
				HASH_ELL* att = arr;
				arr = arr->next;
				delete att;
			}
		}
	}
	delete[] hash;
}

int main()
{
	setlocale(LC_ALL, "rus");
	HASH_ELL* hash = new HASH_ELL();
	int value;
	string key;
	int menu;
	cout << "Введите первоначайльный размер хэш-таблицы: ";
	cin >> size_hash;
	hash = Siz(hash);
	do
	{
		cout << "1.Добавить значение и ключ." << endl;
		cout << "2.Вывести хэш-таблицу." << endl;
		cout << "3.Удалить ключ." << endl;
		cout << "4.Вывести значение по ключу." << endl;
		cout << "5.Выход." << endl;
		cin >> menu;
		switch (menu)
		{
		case 1:
			cout << "Введите значение: ";
			cin >> value;
			cout << "Введите ключ: ";
			cin >> key;
			hash = ADD(hash, value, key);
			break;
		case 2:
			cout << "-------------------- Хэш-таблица --------------------" << endl;
			Prin(hash);
			cout << "-----------------------------------------------------" << endl;
			break;
		case 3:
			cout << "Какой ключ удалить: ";
			cin >> key;
			hash = Delet_znach(hash, key);
			if (boo == false)
			{
				cout << "Значение с таким ключом не найдино! " << endl;
			}
			boo = false;
			break;
		case 4:
			cout << "Какое значение по ключу вывести. ";
			cin >> key;
			Output(hash, key);
			if (boo == false)
			{
				cout << "Значение с таким ключом не найдино! " << endl;
			}
			boo = false;
			break;
		case 5:
			Delet_HASH_ELL(hash);
			break;
		}
	} while (menu != 5);
	return 0;
}


