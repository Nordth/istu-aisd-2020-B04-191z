#include <iostream>
#include <stdio.h>

using namespace std;

int random(int N) {
	return (rand() % N) + 1;
}

int* merge(int *a, int begin, int end, int *b) {
	int buff;
	int size = end - begin + 1;
	if (size == 1) {
		return a;
	}
	else if (size == 2) {
		if (a[begin] > a[end]) {
			buff = a[begin];
			a[begin] = a[end];
			a[end] = buff;
		}
		return a;
	}
	else {
		int half = (end - begin) / 2 + begin;
		a = merge(a, begin, half, b);
		a = merge(a, half + 1, end, b);
		
		int left = half + 1;
		int right = end + 1;
		int ai = begin;
		int aj = half + 1;
		int bi = begin;

		while (ai < left&&aj < right) {
			if (a[ai] < a[aj]) {
				b[bi] = a[ai];
				ai++;
			}
			else {
				b[bi] = a[aj];
				aj++;
			}
			bi++;
		}
		while (ai < left) {
			b[bi] = a[ai];
			bi++;
			ai++;
		}
		while (aj < right) {
			b[bi] = a[aj];
			bi++;
			aj++;
		}
		for (int i = begin; i < end + 1; i++) {
			a[i] = b[i];
		}
		return a;
	}
}

int main() {
	const int N = 20;
	int *A, *B;
	A = new int[N];
	B = new int[N];
	
	for (int z = 0; z < N; z++) {
		A[z] = random(100);
	}
		
	for (int i = 0; i < N; i++) {
		cout << A[i]<<' ';
	}
	cout << '\n';
	A = merge(A, 0, N-1, B);

	for (int i = 0; i < N; i++) {
		cout << A[i] << ' ';
	}
	delete[] A;
	delete[] B;
}