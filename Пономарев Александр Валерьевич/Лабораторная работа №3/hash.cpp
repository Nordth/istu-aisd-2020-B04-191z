#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct List_1
{
    string key;
    int value;
    List_1* next;
};
struct Table
{
    List_1* array;
    int size = 0;
    int general = 0;

    //инициализаця, передаем заданное число для определения будующей таблици
    bool gen(int item)
    {
        if (item < 3 || array)
        {
            cout << "Простите Hash Table не создана. \n\n" << "Введите еще раз значение: ";
            cin >> item;
            gen(item);
            return false; // если меньше то не чего не делаем
        }
        //число ячеек в массиве
        size = item;
        array = new List_1[item];//создаем новый List_1 как массив    
        cout << "Отлично, Hash Table создана в ней " << item << " items.\n\n\n";
        return true;
    }

    bool add(string key, int value)
    {
        List_1* ls = new List_1();
        ls->key = key;
        ls->value = value;
        return add(ls);
    }
    bool add(List_1* Ldata)
    {
        int hashTable = h(Ldata->key);
        if (array[hashTable].key == "")
        {
            array[hashTable] = *Ldata;
            general++;
            if (general > size / 2)
            {
                hash_2();
            }
            return true;
        }
        else
        {
            List_1* ls = array + hashTable;
            while (ls)
            {
                if (ls->key == Ldata->key)
                {
                    return false;
                }
                if (!ls->next)
                {
                    ls->next = Ldata;
                    return true;
                }
                ls = ls->next;//переход на другой лист заного проверка
            }
            return false;
        }
        return false;
    }

    int h(string key) {
        int hash = 0;
        for (int i = 0; i < key.size(); i++) {
            hash = hash + ((int)key[i]);
        }
        hash = hash % size;
        return hash;
    }
    void hash_2()
    {
        List_1* old = array;
        array = new List_1[size * 2];
        int oldS = size;
        size = size * 2;
        general = 0;

        for (int i = 0; i < oldS; i++)
        {
            if (old[i].key != " ")
            {
                List_1* NewList_1 = new List_1();
                NewList_1->key = old[i].key;
                NewList_1->value = old[i].value;
                NewList_1->next = old[i].next;
                old[i].value = NULL;
                while (NewList_1)
                {
                    add(NewList_1->key, NewList_1->value);
                    NewList_1 = NewList_1->next;
                }
            }
        }
        delete[] old;
    }
    bool rm(string key)
    {
        //находим hash
        int hesh = h(key);
        if (array[hesh].key == key)
        {
            if (!array[hesh].next)
            {
                array[hesh].key = "";
                general--;
                return true;
            }
            else
            {
                List_1* rem = array[hesh].next;
                array[hesh].key = rem->key;
                array[hesh].value = rem->value;
                array[hesh].next = rem->next;
                delete rem;
                return true;
            }
        }
        else
        {
            List_1* next = array + hesh;
            while (next && next->next) {
                if (next->next->key == key) {
                    List_1* toRemove = next->next;
                    next->next = toRemove->next;
                    delete toRemove;
                    return true;
                }
                next = next->next;
            }
            return false;
        }
        return false;
    }
    int search(string key)
    {
        int hesh = h(key);
        int val;
        if (array[hesh].key == "")
        {
            return 0;
        }
        else
        {
            List_1* sr = array + hesh;
            while (sr)
            {
                if (sr->key == key)
                {
                    val = sr->value;
                    return val;
                }
                else
                {
                    sr = sr->next;
                }
            }
            return 0;
        }
    }
    bool DeleteALL()
    {
        for (int i = 0; i < size; i++)
        {
            if (array[i].key != "") {
                List_1* rm = array + i;
                if (rm->next) {
                    rm = rm->next;
                    List_1* REM;
                    while (rm) {
                        REM = rm;
                        rm = rm->next;
                        delete REM;
                    }
                }
            }
        }
        List_1* REM = array;
        array = new List_1[1];
        size = 1;
        general = 0;
        delete[] REM;
        return true;
    }
    void printAll() {  // Печать всех элементов
        if (size == 0) {
            cout << "Таблица пуста" << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            if (array[i].key != "") {
                List_1* next = array + i;
                while (next) {
                    cout << i << "=[" << next->key << ":" << next->value << "] ";
                    next = next->next;
                }
            }
        }
        cout << endl;
    }

};


int main()
{
    SetConsoleOutputCP(1251);
    int a, el(3);
    string st;
    cout << "Создание HashTable введите число для табилцы больше 3 или 3\n\n";
    cin >> el;

    Table* ht = new Table();
    ht->gen(el);
    for (;;) {
        cout << "1)Вставка элемента\n";
        cout << "2)Поиск\n";
        cout << "3)Удаление\n";
        cout << "4)Конец\n";
        cout << "5)Печать таблици\n";
        cin >> a;

        switch (a)
        {
        case 1:
            cout << "Вставка элемента: ";
            cin >> st;
            cout << "Значение элемента: ";
            cin >> a;
            ht->add(st, a);
            break;
        case 2:
            cout << "Введите ключ: ";
            cin >> st;
            a = ht->search(st);
            cout << "Значение = " << st << " = " << a << "\n";
            break;
        case 3:
            cout << "Введите ключ";
            cin >> st;
            ht->rm(st);
            break;
        case 4:
            ht->DeleteALL();
            cout << "Память очищена";
            break;
        case 5:
            ht->printAll();
        default:
            break;
        }
        if (a == 4) {
            break;
        }
    }

    return 0;
}