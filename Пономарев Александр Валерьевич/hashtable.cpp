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
};
int main() {
    
    return 0;
}

 