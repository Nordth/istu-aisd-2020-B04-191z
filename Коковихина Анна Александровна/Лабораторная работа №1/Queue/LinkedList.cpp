#include <cstdio>
#include <string>

using namespace std;

class Node {
public:
    Node(int value) {
        this->next = nullptr;
        this->value = value;
    }

    Node *next = nullptr;
    int value;
};

class LinkedList {
private:
    Node *first, *last;  // указатели на первый и последний элемент списка
public:
    LinkedList() {
        this->last = nullptr;
        this->first = nullptr;
    }

    void add(int value) { // добавление элемента в конец
        // Создаем узел с переданным значением, устанавливаем его как следующий элемент у текущего последнего и делаем его последним
        Node *node = new Node(value);
        if (not this->first) {
            // если еще нет ссылки на первый элемент, то делаем переданный элемент первым
            this->first = node;
            this->last = node;
            return;
        }
        this->last->next = node;
        this->last = node;
    }

    void add_at_start(int value) {
        // Создаем узел с переданным значением, устанавливаем его как первый элемент, а текущий первый делаем его следующим
        Node *node = new Node(value);
        if (not this->first) {
            // если еще нет ссылки на первый элемент, то делаем переданный элемент первым
            this->first = node;
            this->last = node;
            return;
        }
        node->next = this->first;
        this->first = node;
    }

    Node *find(int value) {// возвращает первый узел, значение которого совпадает с value. Если не найден, то nullptr
        Node *current = this->first;
        while (current) {
            // пока текущий элемент не нулевой указатель(пока список не закончился) сравниваем его значение с заданым
            // если совпадает, то возвращаем его, если нет, то переходм к следующему
            if (current->value == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void add(int value, Node *previous) { // Добавляет элемент, после указанного, если nullptr, то в начало
        if (not previous) {
            add_at_start(value);
            return;
        }
        Node *node = new Node(value);
        node->next = previous->next;
        previous->next = node;

    }

    bool delete_by_value(int value) { // удаляет первый узел, занчение котрого совпадает с value
        Node *current = this->first;
        if (not current) { //Если нет первого элемента - выходим
            return false;
        }
        if (current->value == value) {// отдельно обрабатываем первый элемент, потому что нужно обновить указатель first
            Node *to_delete = current;
            this->first = to_delete->next;
            if (to_delete ==
                this->last) { // если удаляемый элемент - последний обновляем указатель на последний элемент
                this->last = current;
            }
            delete to_delete;
            return true;
        }
        while (current->next) {
            // пока у текущего узла есть следующий - проверяем СЛЕДУЮЩИЙ узел на совпадение занчения
            // Если оно совпадает, то задаем текущему узлу следующий как узел, через один от текущего
            if (current->next->value == value) {
                Node *to_delete = current->next;
                current->next = to_delete->next;
                if (to_delete == this->last) {
                    // если удаляемый элемент - последний, то обновляем указатель на последний элемент
                    this->last = current;
                }

                delete to_delete;
                return true;
            }
            current = current->next;
        }
        return false;

    }

    void clear() { // удаляет все элементы в коллекции
        Node *current = this->first;
        while (current) { // пока текущий элемент не nullptr удаляем его и переходим к следующему
            Node *to_delete = current;
            current = to_delete->next;
            delete to_delete;
        }
        this->first = nullptr;
        this->last = nullptr;

    }

    void print() {
        Node *current = this->first;
        while (current) {
            printf("%d ", current->value);
            current = current->next;
        }
        printf("\n");
    }


};

int main() {
    LinkedList list = *new LinkedList();
    list.print();
    list.add(1);
    list.print();
    list.delete_by_value(1);
    list.print();
    list.add(1);
    list.add(2);
    list.add(3);
    list.print();
    list.add_at_start(4);
    list.print();
    Node *node_2 = list.find(2);
    printf("%d\n", node_2->value);
    list.add(5, node_2);
    list.print();
    list.add(6, nullptr);
    list.print();
    list.add(7, node_2);
    list.print();
    list.delete_by_value(7);
    list.print();
    list.delete_by_value(3);
    list.add(10);
    list.print();
    list.clear();
    list.print();
    list.add(1);
    list.print();
}
