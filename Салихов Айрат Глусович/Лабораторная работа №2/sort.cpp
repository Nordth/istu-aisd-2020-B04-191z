#include "stdio.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int* merge(int* array, int size1, int* array2, int size2);
void insertSort(int* array, int size) {
	if (size < 2) return;

	for (int i = 1; i < size; i++) {
		if (array[i] < array[i - 1]) {
			for (int j = i; j >= 1; j--) {
				if (array[j] > array[j - 1]) break;
				int temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
			}
		}
	}
}

int* mergeSort(int* array, int size) {
	if (size == 1) return array;
	int* arrayLeft;
	int* arrayRight;
	arrayLeft = new int[size / 2];
	arrayRight = new int[(unsigned int)(size - size / 2)];
	for (int i = 0; i < size / 2; i++) {
		arrayLeft[i] = array[i];
	}
	int j = 0;
	for (int i = size / 2; i < size; i++) {
		arrayRight[j] = array[i];
		j++;
	}
	array = merge(mergeSort(arrayLeft, size / 2), size / 2, mergeSort(arrayRight, size - size / 2), size - size / 2);
	delete[] arrayLeft;
	delete[] arrayRight;
	return array;
}

int* merge(int* array, int size1, int* array2, int size2) {
	int i = 0;
	int j = 0;
	int pos = 0;
	int* merged = new int[(unsigned int)size1 + size2];
	while (i < size1 && j < size2) {
		if (array[i] < array2[j]) {
			merged[pos] = array[i];
			i++;
		}
		else {
			merged[pos] = array2[j];
			j++;
		}
		pos++;
	}
	while (i < size1) {
		merged[pos] = array[i];
		i++;
		pos++;
	}
	while (j < size2) {
		merged[pos] = array2[j];
		j++;
		pos++;
	}
	return merged;
}
void input(int* array, int& size)
{

	cout << "vvedite kolichestvo elements massiva: ";
	cin >> size;
	for (int i = 0; i < size; i++)
	{
		cout << "array[" << i << "] = ";
		cin >> array[i];
	}
	cout << endl;
}
void print(int* array, int size)
{

	for (int i = 0; i < size; i++)
	{
		cout << "array[" << i << "] = " << array[i] << endl;
	}
}
int main() {
	int n, m;
	int* array1 = new int[100];
	int* array2 = new int[100];

	input(array1, n);
	insertSort(array1, n);
	print(array1, n);

	input(array2, m);
	array2 = mergeSort(array2, m);
	print(array2, m);
}