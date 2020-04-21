#include <string>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

class KeyValue {
public:
    int key;
    string value;

    KeyValue(int k, string &v) {
        this->key = k;
        this->value = v;
    }
};

class HashTable {
private:
    int capacity, size;
    vector<list<KeyValue *>> array;

    void add(KeyValue *keyValue) {
        int hash = this->get_hash(keyValue->key);
        this->array[hash].push_back(keyValue);
        this->size++;

    }

public:
    HashTable(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        this->array = vector<list<KeyValue *>>(this->capacity);
    }

    int get_hash(int key) {
        return key % this->capacity;
    }

    void resize(int new_capacity) {
        vector<list<KeyValue *>> old_array = this->array;
        int old_capacity = this->capacity;
        this->array = vector<list<KeyValue *>>(new_capacity);
        this->capacity = new_capacity;
        for (int i = 0; i < old_capacity; ++i) {
            auto it = old_array[i].begin();
            while (it != old_array[i].end()) {
                this->add(*it);
                it++;
            }
        }
        old_array.clear();

    }

    void add(int key, string &value) {
        auto *insert_pair = new KeyValue(key, value);
        this->add(insert_pair);
        if (this->size > this->capacity / 2) {
            this->resize(this->capacity * 2);
        };

    }

    void delete_by_key(int key) {
        int hash = this->get_hash(key);
        list<KeyValue *> *pairs = &this->array[hash];
        auto it = pairs->begin();
        while (it != pairs->end()) {
            KeyValue *keyValue = *it;
            if (keyValue->key == key) {
                delete keyValue;
                it = pairs->erase(it);
                this->size--;
                return;
            }
            it++;
        }

    }

    int get_capacity() {//Посмотреть вместимость
        return this->capacity;
    }

    void print() {
        cout << "Capacity: " << this->capacity << endl;
        for (int i = 0; i < this->capacity; ++i) {
            auto it = this->array[i].begin();
            while (it != array[i].end()) {
                KeyValue *pair = *it;
                cout << pair->key << ": " << pair->value << "\n";
                it++;
            }

        }
    }

    void remove() {
        for (int i = 0; i < this->capacity; ++i) {
            auto it = this->array[i].begin();
            while (it != array[i].end()) {
                KeyValue *pair = *it;
                delete pair;
                it++;
            }
        }
    }


};


int main() {
    HashTable table = HashTable(10);//Проверяем работу программы, вводим данные, получаем связанные коды
    table.add(3, "asa");
    table.add(5, "QWE");
    table.add(1, "as");
    table.add(11, "aqs");
    table.print();
    table.add(31, "aqs");
    table.add(21, "aqs");
    table.print();
    table.delete_by_key(1);
    table.print();
    table.remove();
}
