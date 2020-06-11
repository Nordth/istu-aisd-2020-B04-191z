#include <iostream>

long long int arr[100005];

int partition(int l, int r)
{
	int v = arr[(l + r) / 2];
	int i = l;
	int j = r;
	while (i <= j)
	{
		while (arr[i] < v)
		{
			i = i + 1;
		}
		while (arr[j] > v)
		{
			j = j - 1;
		}
		if (i >= j)
		{
			break;
		}
		std::swap(arr[i++], arr[j--]);
	}
	return j;
}

void QuickSort(int begin, int end)
{
	if (begin >= end)
	{
		return;
	}
	int pos = partition(begin, end);
	QuickSort(begin, pos);
	QuickSort(pos + 1, end);
}


int main()
{
	std::cout << "Number of elements:" << std::endl;
	int n;
	std::cin >> n;
	std::cout << "Elements:" << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cin >> arr[i];
	}
	QuickSort(0, n - 1);
	std::cout << "Result:" << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << arr[i] << ' ';
	}
	//system("PAUSE");
	return 0;
}