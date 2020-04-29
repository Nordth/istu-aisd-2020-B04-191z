
#include <cstdio>
#include <stdexcept>

using namespace std;

class Queue {
private:
    int size, capacity;
    int *array;

    void double_size() { // удваивает размер массива
        // делаем копию указателя на массив, затем создаем новый массив с удвоенным размером, и копируем в него значения
        int *old_array = this->array;
        int new_capacity = this->capacity * 2;
        this->array = new int[new_capacity];
        for (int i = 0; i < this->capacity; i++) {
            this->array[i] = old_array[i];
        }
        delete[] old_array;
        this->capacity = new_capacity;
    }

public:
    Queue(int capacity) {
        this->size = 0;
        this->capacity = capacity;
        this->array = new int[capacity];
    }

    void push(int value) {
        if (this->size == this->capacity) {
            this->double_size();
        }
        this->array[this->size] = value;
        this->size++;

    }

    int pop() {//Отдаем последний элемент, и удаляем его
        // (уменьшаем размер массива на 1 и "забываем" про последний элемент)
        if (this->size == 0) { // Если массив пустой - выбрасываем ошибку
            throw out_of_range("Queue is empty");
        }
        this->size--;
        return this->array[this->size];
    }

    int getCapacity() {
        return this->capacity;
    }

    int getSize() {
        return this->size;
    }

    void print() {
        printf("capacity: %d, size: %d\n values: ", this->capacity, this->size);
        for (int i = 0; i < this->size - 1; i++) {
            printf("%d ", this->array[i]);
        }
        printf("%d\n", this->array[this->size - 1]);


    }


};

int main() {
    Queue queue = Queue(2);
    queue.print();
    printf("test push\n");
    for (int i = 0; i <= 8; i++) {
        queue.push(i);
        queue.print();
    }
    printf("test pop\n");
    printf("pop: %d\n", queue.pop());
    queue.print();
    queue.push(9);
    queue.print();
    int size = queue.getSize();
    for (int i = 0; i < size; i++) {
        printf("pop: %d\n", queue.pop());
        queue.print();
    }
    printf("test empty pop\n");
    try {
        queue.pop();
    }
    catch (out_of_range &e) {
        printf("%s", e.what());
    }

}
