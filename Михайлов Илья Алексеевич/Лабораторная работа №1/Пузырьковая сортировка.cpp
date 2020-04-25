#include<iostream>
#include <time.h>
#include <stdlib.h>
#include<ctime>
using namespace std;

void Sortirovka(int* att, int A)
{
	for (int i = 0; i<A; i++)
	{
		for (int j = 0; j <A - 1; j++)
		{
			if (att[j] >att[j + 1])
			{
				int b = att[j];
				att[j] = att[j + 1];
				att[j + 1] = b;
			}
		}
	}

}

int main()
{
	setlocale(LC_ALL, "Rus");
	const int N = 15;
	srand(time(NULL));
	int arr[N];
	for (int i = 0; i< N; i++)
	{
		arr[i] = rand() % 100;
	}
	cout<<"Начальный массив"<<endl;
	for (int i = 0; i< N; i++)
	{
		cout<<arr[i] <<" ";
	}
	cout<<endl;
	Sortirovka(arr, N);
	cout<<"Отсортированный массив"<<endl;
	for (int i = 0; i< N; i++)
	{
		cout<<arr[i] <<" ";
	}
	return 0;
}

