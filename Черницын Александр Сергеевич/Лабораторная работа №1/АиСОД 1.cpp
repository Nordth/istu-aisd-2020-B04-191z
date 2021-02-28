#include <iostream>

using namespace std;

void rand_Arr(int *Arr_Q, int *Arr_S, int N) // Ввод массива случайных чисел
{
	for (int i = 0; i < N; i++)
	{
		Arr_Q[i] = rand() % 100;	// записать число в диапазоне от 0 до 99
		Arr_S[i] = Arr_Q[i];		// копировать во второй массив
	}
}

void Out(int *Arr_Q, int N)	//Вывод исходного массива
{
	for (int i = 0; i < N; i++)		// цикл по всем элементам
	{
		cout << Arr_Q[i] << " ";	// вывести массив
	}
	cout << "\n";				
}

void OutQuick(int *Arr_Q, int N)	//Вывод массива отсортированного быстрой сортировкой
{
	cout << "\nБыстрая сортировка:\n";
	for (int i = 0; i < N; i++)		// массив по всем элементам
	{
		cout << Arr_Q[i] << " ";	//вывести массив
	}
}

void OutSel(int *Arr_S, int N)		// Вывод массива сортировки выбором
{
	cout << "\nСортировка выбором:\n";
	for (int i = 0; i < N; i++)
	{
		cout << Arr_S[i] << " ";
	}
}

void QuickSort(int *Arr_Q, int from, int to)	// функция быстрой сортировки
{
	int x, temp;	// вспомогательные переменные
	if (from >= to) return;		// если прошел по всему массиву, возврат в программу
	int i = from;				
	int j = to;
	x = Arr_Q[(from + to) / 2];	// начальная точка сортировки - середина
	while (i <= j)				// цикл выполняется, пока не закончился массив
	{
		while (Arr_Q[i] < x) i++;	
		while (Arr_Q[j] > x) j--;
		if (i <= j)
		{
			temp = Arr_Q[i]; Arr_Q[i] = Arr_Q[j]; Arr_Q[j] = temp;		// если не с той стороны, поменять местами
			i++;
			j--;
		}
	}
	QuickSort(Arr_Q, from, j);	// рекурсия правой стороны	
	QuickSort(Arr_Q, i, to);	// рекурсия левой стороны
}

void selectionSort(int *Arr_S, int N)
{
	int min, temp; // для поиска минимального элемента и для обмена
	for (int i = 0; i < N - 1; i++)
	{
		min = i; // запоминаем индекс текущего элемента
		// ищем минимальный элемент чтобы поместить на место i-ого
		for (int j = i + 1; j < N; j++)  // для остальных элементов после i-ого
		{
			if (Arr_S[j] < Arr_S[min]) // если элемент меньше минимального,
				min = j;       // запоминаем его индекс в min
		}
		temp = Arr_S[i];      // меняем местами i-ый и минимальный элементы
		Arr_S[i] = Arr_S[min];
		Arr_S[min] = temp;
	}
}

int main()
{
	int *Arr_Q, *Arr_S;		// объявление указателей на массив
	int N;			

	setlocale(LC_ALL, "Russian");		// кириллица в командной строке
	cout << "Введите размер массива\n";	
	cin >> N;
	Arr_Q = new int[N];		// создание массива на N элементов
	Arr_S = new int[N];

	rand_Arr(Arr_Q, Arr_S, N);	// вызов функции ввода массива
	Out(Arr_Q, N);				// вызов функции вывода исходного массива

	selectionSort(Arr_S, N);	// вызов сортировки выбором
	OutSel(Arr_S, N);			// вывод массива
	
	QuickSort(Arr_Q, 0, N - 1);	//вызов быстрой сортировки
	OutQuick(Arr_Q, N);			// вывод массива
	
}