#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <time.h>

using namespace std;

class STACK
{
public:
    STACK();

    STACK(const STACK &origStack);

    ~STACK();

    int getStackSize();

    void push(int value);

    pair<bool, int> getElement();

    void print();

private:
    int *stack;
    int stackSize;
    int N;
};

STACK::STACK(const STACK &origStack)
{
    stack = new int[origStack.N];
    stackSize = origStack.stackSize;
    N = origStack.N;
    for (int i = 0; i < N; i++)
    {
        stack[i] = origStack.stack[i];
    }
}

STACK::~STACK()
{
    delete[] stack;
}

void STACK::push(int value)
{
    N++;
    if (N > stackSize)
    {
        int *tmp;
        tmp = stack;
        stack = new int[N * 2];
        stackSize = stackSize * 2;
        for (int i = 0; i < N - 1; i++)
        {
            stack[i] = tmp[i];
        }
        delete[] tmp;
    }
    stack[N - 1] = value;
}

pair<bool, int> STACK::getElement()
{
    pair<bool, int> a = {};
    if (N == 0)
    {
        a = {false, -1};
        return a;
    }
    N--;
    a = {true, stack[N]};
    return a;
}

void STACK::print()
{
    if (N == 0)
    {
        cout << "EMPTY STACK" << endl;
        return;
    }
    for (int i = 0; i < N; i++)
    {
        cout << "element " << i << ": = " << stack[i] << endl;
    }
    cout << endl;
}

int STACK::getStackSize()
{
    return stackSize;
}

STACK::STACK()
{
    N = 0;
    stackSize = 1;
    stack = new int[stackSize];
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    STACK *stack1 = new STACK;
    cout << "Текущий размер буфера стека №1: ";
    cout << stack1->getStackSize() << endl;
    cout << "Добавление в стек №1 зачения 2" << endl;
    stack1->push(2);
    cout << "Добавление в стек №1 зачения 2" << endl;
    stack1->push(2);
    cout << "Добавление в стек №1 зачения 2" << endl;
    stack1->push(2);
    cout << "Добавление в стек №1 зачения 3" << endl;
    stack1->push(3);
    cout << "Текущий размер буфера стека №1: ";
    cout << stack1->getStackSize() << endl;
    cout << "Стек1:" << endl;
    stack1->print();
    pair<bool, int> element = stack1->getElement();
    cout << "Получение елемента стека (успех операции, значение): ";
    cout << element.first << " " << element.second << endl;
    element = stack1->getElement();
    cout << "Получение елемента стека (успех операции, значение): ";
    cout << element.first << " " << element.second << endl;
    element = stack1->getElement();
    cout << "Получение елемента стека (успех операции, значение): ";
    cout << element.first << " " << element.second << endl;
    element = stack1->getElement();
    cout << "Получение елемента стека (успех операции, значение): ";
    cout << element.first << " " << element.second << endl;
    element = stack1->getElement();
    cout << "Получение елемента стека (успех операции, значение): ";
    cout << element.first << " " << element.second << endl;
    cout << "Стек1:" << endl;
    stack1->print();
    cout << "Добавление в стек №1 зачения 2" << endl;
    stack1->push(2);
    cout << "Стек1:" << endl;
    stack1->print();
    STACK *stack2 = new STACK(*stack1);
    cout << "Текущий размер буфера стека №2: ";
    cout << stack2->getStackSize() << endl;
    cout << "Добавление в стек №2 зачения 2" << endl;
    stack2->push(2);
    cout << "Добавление в стек №2 зачения 10" << endl;
    stack2->push(10);
    cout << "Добавление в стек №2 зачения 20" << endl;
    stack2->push(20);
    cout << "Текущий размер буфера стека №2: ";
    cout << stack2->getStackSize() << endl;
    cout << "Стек1:" << endl;
    stack1->print();
    cout << "Стек2:" << endl;
    stack2->print();
    delete stack1;
    delete stack2;
    return 0;
}
