#include "stdio.h"
#include <string>     
#include <iostream>
#include <cstdlib> 
#include <ctime>
using namespace std;

struct Item {
	int value;
	string key = "";
	Item* next = NULL;
};

struct HashTable {
	int size = 0;
	int allCount = 0;
	int count = 0;
	Item* array;

	void init(int arrSize) {
		size = arrSize;
		array = new Item[arrSize];
	}

	int getHash(string key) {
		int hash = 0;
		for (int i = 0; i < key.length(); i++) {
			hash += (int)key[i];
		}
		hash = hash % size;
		return hash;
	}

	void add(string key, int value) { //READY
		if (!checkKey(key)) return;
		int hash = getHash(key);
		Item* item = new Item;
		item->key = key;
		item->value = value;

		add(item, hash, array);

		checkSize();

		allCount++;
	}

	void add(Item* item, int hash, Item* arr) {
		if ("" == arr[hash].key) {
			count++;
			arr[hash] = *item;
		}
		else {
			Item* nextItem = (arr + hash);
			while (nextItem->next) {
				nextItem = nextItem->next;
			}
			nextItem->next = item;
		}
	}

	bool checkSize() {
		if (count + 1 < size / 2) return true;
		else {
			int oldCount = count;
			int oldSize = size;
			int hash;
			size = size * 2;
			count = 0;
			Item* oldArray = array;
			Item* newArray = new Item[size];
			for (int i = 0; i < oldSize; i++) {
				if ("" != array[i].key) {
					hash = getHash(array[i].key);
					add((array + i), hash, newArray);
				}
			}
			array = newArray;
			delete[] oldArray;
			return false;
		}
	}

	bool checkKey(string key) {
		int hash = getHash(key);
		if ("" == key) return true;
		if ("" == array[hash].key) return true;
		Item* item = array + hash;
		while (item) {
			if (item->key == key) return false;
			item = item->next;
		}
		return true;
	}

	void remove(string key) { //REMOVE ELEMENT WITH KEY = key
		int hash = getHash(key);
		Item* item = get(key);
		if (item) {
			allCount--;
			if (array[hash].key == item->key) {
				if (item->next) {
					array[hash] = *item->next;
				}
				else {
					array[hash].key = "";
					count--;
				}
			}
			else {
				Item* nextItem = array + hash;
				while (nextItem && nextItem->next) {
					if (nextItem->next->key == key) {
						Item* deleteItem = nextItem->next;
						nextItem->next = deleteItem->next;
						delete deleteItem;
					}
					else {
						nextItem = nextItem->next;
					}
				}
			}
		}
	}

	Item* get(string key) {
		int hash = getHash(key);
		if ("" == key) return NULL;
		if ("" == array[hash].key) return NULL;
		Item* item = array + hash;
		while (item) {
			if (item->key == key) {
				return item;
			}
			item = item->next;
		}
		return NULL;
	}

	void erase() { // CLEAR MEMORY
		Item* nextItem;
		Item* deleteItem;
		for (int i = 0; i < size; i++) {
			if ("" != array[i].key) {
				nextItem = array[i].next;
				array[i].key = "";
				while (nextItem) {
					deleteItem = nextItem;
					nextItem = nextItem->next;
					delete deleteItem;
				}
				array[i].next = NULL;
			}
		}
		count = 0;
		allCount = 0;
		delete[] array;
		array = new Item[10];
		size = 10;
	}

	void printAll() {
		cout << " - - - - - - Elements on HASHTABLE - - - - - - " << endl;
		cout << "Count Elements = " << allCount << " Count of Hashes = " << count << "\n";
		for (int i = 0; i < size; i++) {
			Item* item;
			if ("" != array[i].key) {
				item = array + i;
				while (item) {
					//cout << "i = " << i << " Key = " << item->key << " Value = " << item->value << "\n";
					item = item->next;
				}
			}
		}
		cout << "Count Elements = " << allCount << " Count of Hashes = " << count << "\n";
		cout << " - - - - - - End of HASHTABLE - - - - - - " << endl;
	}
};

int main() {
	HashTable table;
	table.init(5);
	string str = "";
	cout << "PRESS ENTER TO ADD 150k ELEMENtS" << endl;
	getchar();
	str = "Key";
	for (int i = 0; i < 150000; i++) {
		table.add(str + (char)(rand() % 200 + 5) + str + (char)(rand() % 200 + 5) + str + (char)(rand() % 200 + 5) + (char)(rand() % 200 + 5), i);
	}
	table.printAll();
	printf("Press ENTER to ERASE.\n");
	getchar();
	table.erase();
	cout << "DONE" << endl;
	table.printAll();
	printf("Press ENTER to EXIT.\n");
	getchar();
}
