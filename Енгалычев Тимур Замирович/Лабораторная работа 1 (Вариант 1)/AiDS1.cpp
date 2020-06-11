#include <iostream>
#include <functional>

enum type {less, greater};

template <typename T, type e>
void bubbleSort(T arr[], int n)
{
    int passages = 0;
    bool swapped = false;
    std::function<bool(T, T)> predicate;

    
    switch (e)
    {
    case greater:
        predicate = [](T x, T y) { return x>y?true:false; };
        break;
    case less:
        predicate = [](T x, T y) { return x<y? true:false; };
        break;
    }
    for (int i = 0; i < n-1; i++)
    {
        swapped = false;
        passages++;
        for (int j = 0; j < n - 1; j++)
        {
            if (predicate(arr[j], arr[j + 1]))
            {
                T temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
                swapped = true;
                passages++;
            }
        }
        if (!swapped) break;
    }
    
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << ", ";
    }

    std::cout << "(" << passages << ")" << std::endl;
}

int main()
{
    {
        int arr[] = { 69, 16, 29, 66, 41, 10, 11};
        bubbleSort<int, less>(arr, 7);
    }
    {
        int arr[] = { 5, 28, 21, 15, 17, 10, 26};
        bubbleSort<int, greater>(arr, 7);
    }
}
