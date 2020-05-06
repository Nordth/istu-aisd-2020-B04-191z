// insertion sort
// quick sort

#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

void insertionSort(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i; j > 0; j--) {
			if (arr[j] < arr[j - 1]) {
				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
			else break;
		}
	}
}

void quickSort(int* arr, int head, int tail) {
	if (head == tail) return;
	int point = head;

	for (int i = head; i <= tail; i++) {
		if (arr[i] < arr[point]) {
			int temp = arr[point];
			arr[point] = arr[i];
			arr[i] = arr[point + 1];
			arr[point + 1] = temp;
			point++;
		}
	}
	if (head <= point - 1) quickSort(arr, head, point - 1);
	if (tail >= point + 1) quickSort(arr, point + 1, tail);

}

void print(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		if (i > 0 && i % 5 == 0) cout << endl;
		cout << "[" << i << "]" << arr[i] << " ";
	}
	cout << endl << "- - - - - - - - - -" << endl;
}

void fillArray(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 15000;
	}
}

int main() {
	cout << "Insertion sort: " << endl;
	int size = 15;
	srand(time(NULL));
	int* arr = new int[size];
	fillArray(arr, size);
	print(arr, size);
	insertionSort(arr, size);
	print(arr, size);

	cout << "------------------------------------------" << endl << endl;
	int size2 = 900000;
	int* arr2 = new int[size2];
	cout << "Quick sort " << size2 << " elements:" << endl;
	fillArray(arr2, size2);

	unsigned int start = clock();
	quickSort(arr2, 0, size2 - 1);
	unsigned int end = clock();


	cout << "Check is sorted... (array[i]<array[i+1] ? " << "true : false) | (i=0..." << size2-1 << "):" << endl;
	bool isTrue = true;
	for (int i = 0; i < size2-1; i++) {
		if (arr2[i] > arr2[i + 1]) {
			isTrue = false;
			break;
		}
	}
	cout << (isTrue ? "True" : "False") << endl;
	cout << "Quick sort for " << end-start << " ms." << endl;
}