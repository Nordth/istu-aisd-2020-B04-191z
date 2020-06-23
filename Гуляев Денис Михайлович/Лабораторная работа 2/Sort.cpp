#include "stdio.h"
#include <cstdlib>
#include <ctime>

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
	arrayRight = new int[(unsigned int) (size - size / 2)];
	for (int i = 0; i < size / 2; i++) {
		arrayLeft[i] = array[i];
	}
	int j = 0;
	for (int i = size/2; i < size; i++) {
		arrayRight[j] = array[i];
		j++;
	}
	array = merge(mergeSort(arrayLeft, size / 2), size/2, mergeSort(arrayRight, size - size / 2), size-size/2);
	delete[] arrayLeft;
	delete[] arrayRight;
	return array;
}

int* merge(int* array, int size1, int*array2, int size2) {
	int i = 0;
	int j = 0;
	int pos = 0;
	int* merged = new int[(unsigned int) size1 + size2];
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

int main() {

	printf("################ Insertion sort:\n");
	int N = 19;
	int* a = new int[N];
	srand(time(NULL));

	for (int i = 0; i < N; i++) {
		a[i] = rand() % 50;
	}

	for (int i = 0; i < N; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	insertSort(a, N);
	for (int i = 0; i < N; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	printf("################ end of insertion sort 19 elements.\n");

	int SIZE = 9000000;
	int RANGE = 500000;
	printf("########## CREATE ARRAY WITH %d ELEMENTS (values = random of 0-%d)\n", SIZE, RANGE);
	int* array2 = new int[SIZE];

	for (int i = 0; i < SIZE; i++) {
		array2[i] =  rand() % RANGE - RANGE/2;
	}
	printf("########## CREATED. Sort...\n");
	unsigned int start = time(NULL);
	array2 = mergeSort(array2, SIZE);
	unsigned int end = time(NULL);
	printf("########## Check sorted or not. (if a[i]>a[i+1] = Not sorted.)...\n");
	for (int i = 0; i < SIZE - 1; i++) {
		if (array2[i] > array2[i + 1]) {
			printf("Not Sorted.\n");
			break;
		}
	}
	printf("Array was sorted in %d seconds.", end - start);

	// PRINT ARR
	/*for (int i = 0; i < SIZE; i++) {
		printf("%d ", array2[i]);
	}*/
}