#include <iostream>


int main()
{
	std::cout << "Number of elements:" << std::endl;
	int n;
	std::cin >> n;
	std::cout << "Elements:" << std::endl;
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		std::cin >> arr[i];
	}
	if (n == 1)
	{
		std::cout << arr[0];
	}
	else
	{
		for (int i = 1; i < n; i++)
		{
			int j = i - 1;
			int cur = arr[i];
			while (j >= 0 && arr[j] > cur)
			{
				arr[j + 1] = arr[j];
				arr[j] = cur;
				j = j - 1;
			}
		}
	}
	std::cout << "Result:" << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << arr[i] << ' ';
	}
	delete[] arr;
	//system("PAUSE");
	return 0;
}