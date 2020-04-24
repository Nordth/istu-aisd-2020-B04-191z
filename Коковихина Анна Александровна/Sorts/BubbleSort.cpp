
#include <utility>
#include <cstdio>

void bubbleSort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        bool was_swap = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                was_swap = true;
                std::swap(array[j], array[j + 1]);
            }
            printf("i: %d, j: %d\n", i, j);
            for (int i = 0; i < size; ++i) {
                printf("%d ", array[i]);
            }
            printf("\n");
        }
        if (!was_swap) { // если в массиве не было изменений, значит он отсортирован.
            break;
        }
    }

}

int main() {
    const int size = 6;
    printf("Not sorted\n");
    int array[size] = {100, 1, 2, 30, 4, 5};
    bubbleSort(array, size);
    printf("Sorted\n");
    int sorted_array[size] = {1,2,3,4,5,6};
    bubbleSort(sorted_array, size);
}