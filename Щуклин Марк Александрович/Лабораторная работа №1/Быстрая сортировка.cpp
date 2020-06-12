#include <iostream>
#include <vector>


int partition(int l, int r, std::vector<int>& elements)
{
	int v = elements[(l + r) / 2];
	int i = l;
	int j = r;
	while (i <= j)
	{
		while (elements[i] < v)
		{
			i = i + 1;
		}
		while (elements[j] > v)
		{
			j = j - 1;
		}
		if (i >= j)
		{
			break;
		}
		std::swap(elements[i++], elements[j--]);
	}
	return j;
}

void QuickSort(int begin, int end, std::vector<int>& elements)
{
	if (begin >= end)
	{
		return;
	}
	int pos = partition(begin, end, elements);
	QuickSort(begin, pos, elements);
	QuickSort(pos + 1, end, elements);
}


int main()
{
	std::cout << "Number of elements:" << std::endl;
	int n;
	std::cin >> n;
	std::cout << "Elements:" << std::endl;
	std::vector<int> elements;
	for (int i = 0; i < n; i++)
	{
		int element;
		std::cin >> element;
		elements.push_back(element);
	}
	QuickSort(0, n - 1, elements);
	std::cout << "Result:" << std::endl;
	for (int i = 0; i < n - 1; i++)
	{
		std::cout << elements[i] << ' ';
	}
	std::cout << elements[n - 1];
	//system("PAUSE");
	return 0;
}