#include<iostream>
#include<ctime>
#include <stdlib.h>
#include<time.h>
using namespace std;

void Sortirovka(int* att, int l, int r)
{
	int a; 
	int z = l; 
	int x = r; 
	a = att[l];
	while (l<r) 
	{
		while ((att[r] >= a) && (l<r))
		{
			r--; 
		}
		if (l != r) 
		{
			att[l] = att[r];
			l++; 
		}
		while ((att[l] <= a) && (l<r))
		{
			l++; 
		}
		if (l != r)
		{
			att[r] = att[l]; 
			r--; 
		}
	}
	att[l] = a;
	a = l;
	l = z;
	r = x;
	if (l< a)
	{
		Sortirovka(att, l, a - 1);
	}
	if (r> a)
	{
		Sortirovka(att, a + 1, r);
	}
}
int main()
{
	setlocale(LC_ALL, "Rus");
	const int N = 100000;
	srand(time(NULL));
	int arr[N];
	for (int i = 0; i< N; i++)
		arr[i] = rand() % 2000-100;
	clock_t start = clock();
	Sortirovka(arr, 0, N - 1);
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	cout<<"Массив из 100000 элементов отсортирован за "<<seconds<<" s"<<endl;
	return 0;
}

