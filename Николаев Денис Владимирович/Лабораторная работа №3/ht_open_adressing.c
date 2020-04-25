/*******************************************************/
/************    14 вариант    *************************/
/************ Хэш-таблица с закрытым хэшированием ******/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h> // for abs function if key less than zero
//hash table with open addressing (closed hashing)


typedef struct Data {
	int key;
	int value;
	int deleted;
} Data;

typedef struct HashTable {
	Data **arrData;
	size_t size;
	double loadFactor;
	size_t capacity;
} HashTable;

void initializeData(Data **data);
void createHashTable(HashTable **hashTable);
void initializeHashTable(HashTable **hashTable);
size_t hashFunction(HashTable **hashTable, int key);
void rehash(HashTable **hashTable);
void addElement(HashTable **hashTable, int key, int value);
Data* search(HashTable *hashTable, int key);
bool deleteElement(HashTable **hashTable, int key, int value);
void display(HashTable *hashTable);
void freeMemory(HashTable **hashTable);

void test(void);

int main(void)
{
	test();

	return EXIT_SUCCESS;
}

void freeMemory(HashTable **hashTable) {
	if ((*hashTable)->arrData != NULL) {
		for (size_t i = 0; i < (*hashTable)->size; ++i) {
			free((*hashTable)->arrData[i]);
			(*hashTable)->arrData[i] = NULL;
		}
	}
	free((*hashTable)->arrData);
	(*hashTable)->arrData = NULL;
	free(*hashTable);
	*hashTable = NULL;
}

void initializeData(Data **data) {
	*data = (Data*)malloc(sizeof(Data));
	if (*data == NULL) {
		printf("Memory for data is not allocated.\n");
		exit(0);
	}
	(*data)->key = -1;
	(*data)->value = -1;
	(*data)->deleted = 0;
}

void createHashTable(HashTable **hashTable) {
	*hashTable = (HashTable*)malloc(sizeof(HashTable));
	if (*hashTable == NULL) {
		printf("Memory for hash table is not allocated.\n");
		exit(0);
	}
	(*hashTable)->arrData = NULL;
	(*hashTable)->size = 1;
	(*hashTable)->loadFactor = 0.5;
	(*hashTable)->capacity = 1;
}

void initializeHashTable(HashTable **hashTable) {
	if (*hashTable == NULL) {
		createHashTable(hashTable);
	}
	(*hashTable)->arrData = (Data**)malloc(sizeof(Data*) * (*hashTable)->size);
	if ((*hashTable)->arrData == NULL) {
		printf("Memory for data array is not allocated.\n");
		freeMemory(hashTable);
		exit(0);
	}
	for (size_t i = 0; i < (*hashTable)->size; ++i) {
		(*hashTable)->arrData[i] = NULL;
	}
}

size_t hashFunction(HashTable **hashTable, int key) {
	return (size_t)abs(key) % (*hashTable)->size;
}

void addElement(HashTable **hashTable, int key, int value) {
	size_t index = 0;
	Data *newElement = NULL;
	initializeData(&newElement);
	newElement->key = key;
	newElement->value = value;

	index = hashFunction(hashTable, newElement->key);
	while ((*hashTable)->arrData[index] != NULL &&
			(*hashTable)->arrData[index]->deleted == 0) {
		++index;
		index %= (*hashTable)->size; //loop for hashtable
	}
	if ((*hashTable)->arrData[index] == NULL) {
		(*hashTable)->arrData[index] = newElement;
		++(*hashTable)->capacity;
	} else {
		(*hashTable)->arrData[index]->key = newElement->key;
		(*hashTable)->arrData[index]->value = newElement->value;
		(*hashTable)->arrData[index]->deleted = 0;
		free(newElement);
	}

	if ((*hashTable)->loadFactor <
		(double)((*hashTable)->capacity) / (double)((*hashTable)->size)) {
		rehash(hashTable);
	}
}

void rehash(HashTable **hashTable) {
	HashTable *newTable = NULL;
	createHashTable(&newTable);
	newTable->capacity = (*hashTable)->capacity;
	newTable->size = (*hashTable)->size * 2;
	initializeHashTable(&newTable);

	size_t index = 0;
	for (size_t i = 0; i < (*hashTable)->size; ++i) {
		if ((*hashTable)->arrData[i] != NULL &&
			(*hashTable)->arrData[i]->deleted == 0) {
			index = hashFunction(&newTable, (*hashTable)->arrData[i]->key);
			while (newTable->arrData[index] != NULL) {
				++index;
				index %= newTable->size; //loop for hashtable
			}
			newTable->arrData[index] = (*hashTable)->arrData[i];
		}
	}

	free((*hashTable)->arrData);
	(*hashTable)->arrData = NULL;
	free(*hashTable);
	*hashTable = newTable;

	newTable = NULL;
}

Data* search(HashTable *hashTable, int key) {
	size_t index = 0;
	index = hashFunction(&hashTable, key);
	while (hashTable->arrData[index] != NULL) {
		if (hashTable->arrData[index]->key == key &&
			hashTable->arrData[index]->deleted == 0) {
			return hashTable->arrData[index];
		}
		++index;
		index %= hashTable->size;
	}
	return NULL;
}
/* При удаление элемента он помечается как удаленный
    и изменения структуры хэш-таблицы не происходит*/
bool deleteElement(HashTable **hashTable, int key, int value) {
	Data *element = NULL;
	element = search(*hashTable, key);
	if (element == NULL) {
		return false;
	}
	size_t index = 0;
	index = hashFunction(hashTable, element->key);
	while ((*hashTable)->arrData[index] != NULL) {
		if ((*hashTable)->arrData[index]->key == key &&
			(*hashTable)->arrData[index]->value == value &&
			(*hashTable)->arrData[index]->deleted == 0) {
			(*hashTable)->arrData[index]->deleted = 1;
			return true;
		}
		++index;
		index %= (*hashTable)->size;
	}
	return false;
}

void display(HashTable *hashTable) {
	printf("\n\tPosition| Key\t| Value\n");
	for (size_t i = 0; i < hashTable->size; ++i) {

		if (hashTable->arrData[i] != NULL && hashTable->arrData[i]->deleted == 0) {
			printf("\t%ld\t| %d\t| %d\n", i, hashTable->arrData[i]->key, hashTable->arrData[i]->value);
		}
		else {
			printf("\t%ld\t| \t| \n ", i);
		}
	}
	printf("\n");
}

void test(void) {
	HashTable *hashTable = NULL;
	int key = 0,
		value = 0;

	initializeHashTable(&hashTable);

	addElement(&hashTable, 50, 100);
	display(hashTable);
	addElement(&hashTable, 65, 10);
	display(hashTable);
	addElement(&hashTable, 75, 1);
	display(hashTable);
	addElement(&hashTable, 5, 10);
	display(hashTable);
	addElement(&hashTable, 5, 10);
	display(hashTable);
	addElement(&hashTable, 6, 11);
	display(hashTable);
	addElement(&hashTable, 7, 210);
	display(hashTable);

	key = 5;
	Data *data = NULL;
	initializeData(&data);
	*data = *search(hashTable, 5);

	if (data != NULL) {
		printf("Element found: %d\n", data->value);
	}
	else {
		printf("Element not found\n");
	}
	display(hashTable);

	if (deleteElement(&hashTable, 5, 10) == true) {
		printf("\nElement (5, 10) is deleted.\n");
	}
	else {
		printf("\nThere's no such element to delete.\n");
	}

	display(hashTable);

	if (deleteElement(&hashTable, 5, 10) == true) {
		printf("\nElement (5, 10) is deleted.\n");
	}
	else {
		printf("\nThere's no such element to delete.\n");
	}

	display(hashTable);

	addElement(&hashTable, 5, 10);
	display(hashTable);

	freeMemory(&hashTable);
	hashTable = NULL;
	free(data);
	
}
