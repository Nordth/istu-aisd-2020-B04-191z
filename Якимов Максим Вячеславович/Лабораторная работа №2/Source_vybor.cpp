#include <iostream>
#include <stdio.h>

using namespace std;

int random(int N) {
	return (rand() % N)+1;
}

int main() {
	const int N = 25;
	int A[N];
	int i = 0, m = 0, tmp=0, max=0, bol=0;
	for (int z = 0; z < N; z++) {
		A[z] = random(200)-100;
	}
	for (int x = 0; x < N; x++) {
		cout << A[x] << ' ';
	}
	cout << '\n';	
	for (int k = 0; k < N; k++) {
		max = A[k];
		m = k;
		for (int p = k; p < N; p++) {
			if (max < A[p]) {
				max = A[p];
				m = p;
			}
		}
		if (k != m) {
			tmp = A[k];
			A[k] = A[m];
			A[m] = tmp;
		}		
	}
	for (int x = 0; x < N; x++) {
		cout << A[x] << ' ';
	}
}
