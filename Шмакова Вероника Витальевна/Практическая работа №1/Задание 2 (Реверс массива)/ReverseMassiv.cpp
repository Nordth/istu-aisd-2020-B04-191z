#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");

    int n;

    cout << "введите количество элементов массива:" << "\t";
    cin >> n;

    int* arr = new int[n];
    int t;

    cout << "введите элементы массива:" << endl;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < n / 2; i++)
    {
        t = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = t;
    }

    cout << "Reverse:" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << "\t";
    }

	return 0;
}
