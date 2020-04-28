#include <cstdio>
#include <utility>

using namespace std;

void privateQuickSort(int arr[], int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    };

    if (left < j)
        privateQuickSort(arr, left, j);
    if (i < right)
        privateQuickSort(arr, i, right);
}

void quickSort(int arr[], int size){
    privateQuickSort(arr,0,size);
}

int main() {
    int size = 5;
    int array[] = {2,6,19,-5,0};
    quickSort(array,size);
    for (int i = 0; i < size; ++i) {
        printf("%d ",array[i]);

    }
}