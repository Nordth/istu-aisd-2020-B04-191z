#include <string>
#include <iostream>
#include <locale.h>
using namespace std;

//Хэш-таблица с открытым хешированием

struct DataItem {
	int value;
	string key;
	DataItem* next;
};

struct DataTable {
	DataItem* hashTable;
	int size = 0;
	int count_elements = 0;

	void init(int buf_size)
	{
		if (buf_size == 0) return;
		size = buf_size;
		hashTable = new DataItem[size];
	}

	int hashFunction(string key)
	{
		int hash = stoi(key) % size;
		return hash;
	}

	bool appendItem(string key, int value)
	{
		DataItem* item = new DataItem();
		item->key = key;
		item->value = value;
		int hashCode = hashFunction(item->key);
		if (hashTable[hashCode].key == "")
		{
			hashTable[hashCode] = *item;
			count_elements++;
			if (count_elements > size / 2) rehash();
			return true;
		}
		else {
			DataItem* next = hashTable + hashCode;
			while (next)
			{
				if (next->key == item->key) return false;
				if (!next->next)
				{
					next->next = item;
					return true;
				}
				next = next->next;
			}
			return false;
		}
		return false;
	}

	int SearchItem(string key)
	{
		int hashCode = hashFunction(key);
		int value;
		if (hashTable[hashCode].key == "")
		{
			return false;
		}
		else
		{
			DataItem* element = hashTable + hashCode;
			while (element)
			{
				if (element->key == key)
				{
					value = element->value;
					return value;
				}
				else
				{
					element = element->next;
				}
			}
		}
		return 0;
	}

	bool DeleteItem(string key)
	{
		int hashCode = hashFunction(key);
		if (hashTable[hashCode].key == key)
		{
			if (!hashTable[hashCode].next)
			{
				hashTable[hashCode].key = "";
				count_elements--;
				return true;
			}
			else
			{
				DataItem* ForRemove = hashTable[hashCode].next;
				hashTable[hashCode].key = ForRemove->key;
				hashTable[hashCode].value = ForRemove->value;
				hashTable[hashCode].next = ForRemove->next;
				delete ForRemove;
				return true;
			}
		}
		else {
			DataItem* next = hashTable + hashCode;
			while (next)
			{
				if (next->key == key)
				{
					DataItem* ForRemove = next->next;
					next->next = ForRemove->next;
					delete ForRemove;
					return true;
				}
				next = next->next;
			}
			return false;
		}
	}

	void DropTable()
	{
		for (int i = 0; i < size; i++)
		{
			if (hashTable[i].key != "")
			{
				DataItem* next = hashTable;
				if (next->next)
				{
					next = next->next;
					DataItem* toRemove;
					while (next)
					{
						toRemove = next;
						next = next->next;
						delete toRemove;
					}
				}
			}
		}
		DataItem* TableForRemove = hashTable;
		hashTable = new DataItem[1];
		size = 1;
		count_elements = 0;
		delete[] TableForRemove;
	}

	void rehash()
	{
		DataItem* oldTable = hashTable;
		hashTable = new DataItem[size * 2];
		int oldSize = size;
		size = size * 2;
		count_elements = 0;

		for (int i = 0; i < oldSize; i++) {
			if (oldTable[i].key != "") {
				DataItem* next = new DataItem();
				next->key = oldTable[i].key;
				next->value = oldTable[i].value;
				next->next = oldTable[i].next;
				oldTable[i].next = NULL;
				while (next) {
					appendItem(next->key, next->value);
					next = next->next;
				}
			}
		}

		delete[] oldTable;
	}

	void ReturnAll()
	{
		if (count_elements == 0) {
			cout << "Нет строк" << endl;
			return;
		}
		for (int i = 0; i < size; i++) {
			if (hashTable[i].key != "") {
				DataItem* next = hashTable + i;
				while (next)
				{
					cout << i << "->(" << next->key << ";" << next->value << ") ";
					next = next->next;
				}
			}
		}
		cout << endl;
	}
};

int main()
{
	setlocale(0,"");
	int number, val;
	string key;
	DataTable* table = new DataTable();
	table->init(3);
	do {
		cout << "1 - Добавить элемент\n";
		cout << "2 - Значение по ключу\n";
		cout << "3 - Удалени элемента\n";
		cout << "4 - Очистка\n";
		cout << "22 - Показать таблицу\n";
		cout << "ЧИСЛО: ";
		cin >> number;

		switch (number)
		{
		case 1:
			cout << "Ключ: ";
			cin >> key;
			cout << "Значение: ";
			cin >> val;
			table->appendItem(key, val);
			break;
		case 2:
			cout << "Ключ: ";
			cin >> key;
			val = table->SearchItem(key);
			cout << "Ключ/Значение: " << key << " = " << val << "\n";
			break;
		case 3:
			cout << "Ключ: ";
			cin >> key;
			table->DeleteItem(key);
			break;
		case 4:
			table->DropTable();
		case 22:
			table->ReturnAll();
		default:
			break;
		}
	}
	while (number != 4);
	return 0;
}