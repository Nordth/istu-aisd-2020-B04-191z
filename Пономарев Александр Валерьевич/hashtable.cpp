#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>

using  namespace std;

int hh(string str); //hash

struct listHash
{
    int value;
    string word;
    listHash *next;
};
struct tablehash {
	listHash* array;
	int size = 0; //количество записей в списке
	int elements = 0; //сколько всего элементов в списке

    bool createdTable(int rate)
    {
    if(rate < 3)//если меньше 3 то таблица не создается
    {
        return false; //если меньше то не создаем возращаем false
    }
    if(array)
    {
        return false;
    }
    size = rate;
    array = new listHash[size];
    // tablehash::size = rate;
	// tablehash::array = new listHash[tablehash::size];
		return true;
    }

    //insert item listhash key,value
    bool insert(string word,int value)
    {
        listHash* hashtab = new listHash();
        hashtab -> word = word;
        hashtab -> value = value;
        return add(hashtab);
    }
    //добавление в самой таблице
    bool add(listHash* table)
    {
        int h = hh(table -> word);
        if (array[h].word == "")
        {
            array[h] = *table;
			elements++;
			if (elements > size / 2) {
				return true;
			}
			return true;
            
        }
        
    }
};
//created table

int main() {
    
    return 0;
}

 