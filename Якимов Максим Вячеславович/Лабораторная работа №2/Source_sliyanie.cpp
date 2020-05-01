#include <iostream>
#include <stdio.h>

using namespace std;

int random(int N) {
	return (rand() % N) + 1;
}

int* proc_merge(int *a, int *b, int left, int begin, int end) {
	int right = end + 1;
	int ai = begin;
	int aj = left;
	int bi = ai;
	
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

int* recurs_div(int *a, int begin, int end, int *b) {
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
		a = recurs_div(a, begin, half, b);
		a = recurs_div(a, half + 1, end, b);
		a = proc_merge(a, b, half+1, begin, end);
		
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
	A = recurs_div(A, 0, N-1, B);

	for (int i = 0; i < N; i++) {
		cout << A[i] << ' ';
	}
	delete[] A;
	delete[] B;
}