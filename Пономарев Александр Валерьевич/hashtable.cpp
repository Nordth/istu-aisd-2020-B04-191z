#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>

using  namespace std;

struct item
{
    int value;
    string key;
    item *next;
};
struct hashtable
{
    item* array;
    int elem = 0;
    int size = 0;


    bool created(int buf)
    {
        if(buf <= 2) //если меньше чем 2
        {
            return false;
        }
        if(array) //если массив уже определен 
        {
            return false;
        }
        size = buf;
        array = new item[size];
        return true;
    }

    //created Item table
    bool createdItem(string key, int value)
    {
        item* listItem = new item();
        listItem -> value = value;
        listItem -> key = key;
    }
    //создаем ячейку в таблицу с ключем и значением
    bool add(item* listItem)
    {
        int h = hh(listItem -> key);
        if (array[h].key = "")
        {
            array[h].key = *listItem;
            elem++;
            if(elem > size / 2)
            {
                //
            }
        }
    }
};

int hh(string k)
{
    return 0;
}
int main() {
    
    return 0;
}

 