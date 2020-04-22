/*Реализовать хэш - таблицус закрытым хешированием
Ключом хэш - таблицы является целочисленное значение
При заполнении хеш - таблицы более, чем на половину, должен увеличиваться внутренний буфер(в два раза) и производится операция перехэширования
Ключом должна быть строка
Хэш - таблица должна поддерживать следующие операции :
1) Инициализация
2) Вставка элемента(целочисленный ключ + значение)
3) Получение значения элемента по ключу
4) Удаление элемента по ключу
5) Освобождение памяти от структуры данных*/

#include <iostream> 
#include <vector>
#include <string>

using namespace std;

template<typename K, typename V>

class HashNode
{
public:
    V value;
    K key;
  
    HashNode(K key, V value)
    {
        this->value = value;
        this->key = key;
    }
};

template<typename K, typename V>

class HashMap
{
    HashNode<K, V>** arr;
    int capacity;
    int size;
    HashNode<K, V>* dummy;

public:
    HashMap()
    {
        capacity = 5;
        size = 0;
        arr = new HashNode<K, V> * [capacity];
        for (int i = 0; i < capacity; i++)
            arr[i] = NULL;
        dummy = new HashNode<K, V>(-1, -1);
    }
    int hashCode(K key)
    {
        return key % capacity;
    }

    void insertNode(K key, V value)
    {
        HashNode<K, V>* temp = new HashNode<K, V>(key, value);
        int hashIndex = hashCode(key);
 
        while (arr[hashIndex] != NULL && arr[hashIndex]->key != key && arr[hashIndex]->key != -1 && arr[hashIndex]->key == key && size != capacity)
        {
            hashIndex++;
            hashIndex %= capacity;
        }

        if (arr[hashIndex] == NULL || arr[hashIndex]->key == -1)
            size++;

        arr[hashIndex] = temp;
    }

    V deleteNode(int key)
    {
        int hashIndex = hashCode(key);

        while (arr[hashIndex] != NULL)
        {
            if (arr[hashIndex]->key == key)
            {
                HashNode<K, V>* temp = arr[hashIndex]; 
                arr[hashIndex] = dummy;
                size--;
                return temp->value;
            }
            hashIndex++;
            hashIndex %= capacity;
        }
        return NULL;
    }
    V get(int key)
    { 
        int hashIndex = hashCode(key);
        int counter = 0;   
        while (arr[hashIndex] != NULL)

        {
            int counter = 0;
            if (counter++ > capacity)   
                return NULL;

            if (arr[hashIndex]->key == key)
                return arr[hashIndex]->value;

            hashIndex++;
            hashIndex %= capacity;
        } 
        return NULL;
    }

    int maxsizeofMap()
    {
        return capacity;
    }

    int sizeofMap()
    {
        return size;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void display()
    {
        for (int i = 0; i < capacity; i++)
        {
            if (arr[i] != NULL && arr[i]->key != -1)
                cout << "key = " << arr[i]->key
                << "  value = " << arr[i]->value << endl;
        }
    }
};


int main()
{
    setlocale(LC_ALL, "Rus");
    int num, val, key;
    HashMap<int, int>* h = new HashMap<int, int>;

    while (1) {
        system("cls");
        cout << "1.Вставить элемент в таблицу(ключ, значение)" << endl;
        cout << "2.Найти элемент по ключу" << endl;
        cout << "3.Удалить элемент по ключу" << endl;
        cout << "4.Вывести содержимое таблицы" << endl;
        cout << "5.Exit" << endl;
        cout << "Выберите номер меню: ";
        cin >> num;
        switch (num) {
        case 1:
            cout << "Текущее количество элементов в таблице: " << h->sizeofMap() << endl;
            cout << "Введите интересующий вас элемент : ";
            cin >> val;
            cout << "Введите ключ, на котором элемент должен быть вставлен : ";
            cin >> key;
            h->insertNode(key, val);
            break;
            system("cls");
        case 2:
            cout << "Введите ключ элемента для поиска: ";
            cin >> key;
            if (h->get(key) == -1) {
                cout << "Элемент не найден в ключе " << key << endl;
                continue;
            }
            else {
                cout << "Элемент в ключе " << key << ": ";
                cout << h->get(key) << endl;
            }
            system("pause");
            break;
            system("cls");
        case 3:
            cout << "Введите ключ удаляемого элемента: ";
            cin >> key;
            cout << "Значение " << h->get(key) << " в ключе " << key << " удалено!";
            h->deleteNode(key);
            cout << endl;
            system("pause");
            break;
            system("cls");
        case 4:
            cout << "Элементы хеш-таблицы:" << endl;
            if (h->isEmpty())
            {
                cout << "Таблица пуста" << endl;
            }
            else
            {
                h->display();
            }
            cout << endl;
            system("pause");
            break;
            system("cls");
        case 5:
            exit(1);
        default:
            cout << "\nВведите корректный номер меню!\n";
        }
    }

    return 0;
}