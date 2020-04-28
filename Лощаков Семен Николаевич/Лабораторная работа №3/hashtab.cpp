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

using namespace std;

template<typename Key, typename Val>
class Node
{
public:
    Val value;
    Key key;
    Node(Key key, Val value) { this->value = value; this->key = key; }
};

template<typename Key, typename Val>
class HTable
{
    int capacity, SIZE;
    Node<Key, Val>** arr;
    Node<Key, Val>* xF;

public:
    HTable()
    {
        capacity = 5;
        SIZE = 0;
        arr = new Node<Key, Val> * [capacity];
        for (int i = 0; i < capacity; i++) arr[i] = NULL;
        xF = new Node<Key, Val>(-1, -1);
    }

    int HFunc(Key key) { return key % capacity; }

    void AddToTable(Key key, Val value)
    {
        Node<Key, Val>* temp = new Node<Key, Val>(key, value);
        int i = HFunc(key);

        while (arr[i] != NULL && arr[i]->key != key && arr[i]->key != -1 && arr[i]->key == key && SIZE != capacity)
        {
            i++;
            i %= capacity;
        }

        if (arr[i] == NULL || arr[i]->key == -1) SIZE++;
        arr[i] = temp;
    }

    Val Delete(int key)
    {
        int i = HFunc(key);

        while (arr[i] != NULL)
        {
            if (arr[i]->key == key)
            {
                Node<Key, Val>* temp = arr[i];
                arr[i] = xF;
                SIZE--;
                return temp->value;
            }
            i++;
            i %= capacity;
        }
        return NULL;
    }
    Val FoundToKey(int key)
    {
        int i = HFunc(key);
        int counter = 0;
        while (arr[i] != NULL)
        {
            int counter = 0;
            if (counter++ > capacity) return NULL;
            if (arr[i]->key == key) return arr[i]->value;
            i++;
            i %= capacity;
        }
        return NULL;
    }

    int maxsizeofMap() { return capacity; }
    int sizeofMap() { return SIZE; }
    bool isEmpty() { return SIZE == 0; }

    void Display()
    {
        for (int i = 0; i < capacity; i++)
        {
            if (arr[i] != NULL && arr[i]->key != -1)
            {
                cout << "Ключ = " << arr[i]->key << "  Значение = " << arr[i]->value << endl;
            }

        }
    }
};


int main()
{
    setlocale(LC_ALL, "Rus");
    int num, val, key;
    HTable<int, int>* h = new HTable<int, int>;

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
            cout << "Введите интересующий вас элемент : "; cin >> val;
            cout << "Введите ключ, на котором элемент должен быть вставлен : "; cin >> key;
            h->AddToTable(key, val);
            break;
            system("cls");
        case 2:
            cout << "Введите ключ элемента для поиска: "; cin >> key;
            if (h->FoundToKey(key) == -1)
            {
                cout << "Элемент не найден в ключе " << key << endl;
                continue;
            }
            else
            {
                cout << "Элемент в ключе " << key << ": " << h->FoundToKey(key) << endl;
            }
            system("pause");
            break;
            system("cls");
        case 3:
            cout << "Введите ключ удаляемого элемента: "; cin >> key;
            cout << "Значение " << h->FoundToKey(key) << " в ключе " << key << " удалено!"; h->Delete(key);
            cout << endl;
            system("pause");
            break;
            system("cls");
        case 4:
            cout << "Элементы хеш-таблицы:" << endl;
            if (h->isEmpty()) { cout << "Таблица пуста" << endl; }
            else { h->Display(); }
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