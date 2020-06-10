#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *next, *prev;
};

class List
{
    Node *Head, *Tail;
    int Count;

public:
    List();

    ~List();

    void delAll();

    void delByIndex(int pos);

    bool delByValue(int value);

    void addTail(int n);

    void print();

    int printByPosition(int pos);

    void addHead(int n);

    void insertByPosition(int pos, int value);

    int getCount();

    Node getHead();
};

List::List()
{
    Head = Tail = NULL;
    Count = 0;
}

List::~List()
{
    delAll();
}

void List::addTail(int n)
{
    Node *temp = new Node;
    temp->next = 0;
    temp->data = n;
    temp->prev = Tail;
    if (Tail != 0)
        Tail->next = temp;

    if (Count == 0)
        Head = Tail = temp;
    else
        Tail = temp;

    Count++;
}

Node List::getHead()
{
    return *Head;
}

int List::getCount()
{
    return Count;
}

void List::addHead(int n)
{
    Node *temp = new Node;

    temp->prev = 0;
    temp->data = n;
    temp->next = Head;

    if (Head != 0)
        Head->prev = temp;
    if (Count == 0)
        Head = Tail = temp;
    else
        Head = temp;

    Count++;
}

void List::insertByPosition(int pos, int value)
{
    if (pos == Count + 1)
    {
        addTail(value);
        return;
    }
    else if (pos == 1)
    {
        addHead(value);
        return;
    }
    int i = 1;
    Node *Ins = Head;

    while (i < pos)
    {
        Ins = Ins->next;
        i++;
    }

    Node *PrevIns = Ins->prev;
    Node *temp = new Node;

    temp->data = value;

    if (PrevIns != 0 && Count != 1)
        PrevIns->next = temp;

    temp->next = Ins;
    temp->prev = PrevIns;
    Ins->prev = temp;

    Count++;
}

void List::delByIndex(int pos)
{
    if (pos == 0)
    {
        cout << "Input position: ";
        cin >> pos;
    }
    if (pos < 1 || pos > Count)
    {
        cout << "Incorrect position !!!\n";
        return;
    }

    int i = 1;

    Node *Del = Head;

    while (i < pos)
    {
        Del = Del->next;
        i++;
    }

    Node *PrevDel = Del->prev;
    Node *AfterDel = Del->next;

    if (PrevDel != 0 && Count != 1)
        PrevDel->next = AfterDel;
    if (AfterDel != 0 && Count != 1)
        AfterDel->prev = PrevDel;

    if (pos == 1)
        Head = AfterDel;
    if (pos == Count)
        Tail = PrevDel;
    delete Del;

    Count--;
}

bool List::delByValue(int value)
{

    Node *Del = Head;
    int i = 1;
    while (Del->data != value)
    {
        Del = Del->next;
        i++;
        if (Del->next == 0)
        {
            return false;
        }
    }

    Node *PrevDel = Del->prev;
    Node *AfterDel = Del->next;

    if (PrevDel != 0 && Count != 1)
        PrevDel->next = AfterDel;
    if (AfterDel != 0 && Count != 1)
        AfterDel->prev = PrevDel;

    if (i == 1)
        Head = AfterDel;
    if (i == Count)
        Tail = PrevDel;

    delete Del;

    Count--;
    return true;
}

int List::printByPosition(int pos)
{

    Node *temp;

    temp = Head;
    int i = 1;

    while (i < pos)
    {
        temp = temp->next;
        i++;
    }
    return temp->data;
}

void List::print()
{
    if (Count != 0)
    {
        Node *temp = Head;
        cout << "( ";
        while (temp->next != 0)
        {
            cout << temp->data << ", ";
            temp = temp->next;
        }
        cout << temp->data << " )\n";
    }
}

void List::delAll()
{
    while (Count != 0)
        delByIndex(1);
}

void splitList(List &a, List &b, List &splittedList)
{
    if (a.getCount() == 0 && b.getCount() == 0)
    {
        return;
    }
    else if (a.getCount() == 0)
    {
        splittedList = b;
    }
    else if (b.getCount() == 0)
    {
        splittedList = a;
    }

    Node curA = a.getHead();
    Node curB = b.getHead();
    splittedList.addTail(curA.data);
    splittedList.addTail(curB.data);
    while (curA.next != 0 && curB.next != 0)
    {
        curA = *curA.next;
        curB = *curB.next;
        splittedList.addTail(curA.data);
        splittedList.addTail(curB.data);
    }

    while (curB.next != 0)
    {
        curB = *curB.next;
        splittedList.addTail(curB.data);
    };

    while (curA.next != 0)
    {
        curA = *curA.next;
        splittedList.addTail(curA.data);
    };
};

int main()
{
    setlocale(LC_ALL, "Russian");
    List A, B, splittedList;

    const int n = 10;
    int a[n] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int b[7] = {90, 80, 70, 60, 50, 40, 30};

    for (int i : a)
        A.addTail(i);

    for (int i : b)
        B.addTail(i);

    cout << "Текущий лист:" << endl;
    A.print();
    A.insertByPosition(2, 299);
    cout << "Лист после вставки 299 перед 2 элементом:" << endl;
    A.print();
    cout << "Второй элемент списка:" << A.printByPosition(2) << endl;
    cout << "Третий элемент списка:" << A.printByPosition(3) << endl;
    cout << A.delByValue(6) << endl;
    cout << A.delByValue(7) << endl;
    cout << "Лист после удаления значения 6 и 7" << endl;
    cout << A.delByValue(100) << endl;
    A.print();

    cout << "Список А: " << endl;
    A.print();
    cout << "Список B: " << endl;
    B.print();
    cout << "Объединенный список А и B: " << endl;
    //splitList(A, B);
    splitList(A, B, splittedList);
    splittedList.print();
    return 0;
}