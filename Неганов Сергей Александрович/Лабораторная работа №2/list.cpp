
#include <iostream>
using namespace std;

struct Element {
public:
    int value;
    Element* nextElement;
    Element* prevElement;
};

class bidirectionalList {
private:
    int length = 0;
    Element* FirstElement;
    Element* LastElement;
public:

    ~bidirectionalList() {
        DelElements();
    }
    void DelElements() {
        while (length != 0) {
            DelElement(1);
        }
    }

    void AddFirstElement(int n) {
        Element* temp = new Element;
        temp->prevElement = 0;
        temp->value = n;
        temp->nextElement = FirstElement;
        if (FirstElement != 0) {
            FirstElement->prevElement = temp;
        }
        if (length == 0) {
            FirstElement = LastElement = temp;
        }
        else {
            FirstElement = temp;
        }
        length++;
    }

    void AddLastElement(int n) {
        Element* temp = new Element;
        temp->nextElement = 0;
        temp->value = n;
        temp->prevElement = LastElement;

        if (LastElement != 0) {
            LastElement->nextElement = temp;
        }
        if (length == 0) {
            FirstElement = LastElement = temp;
        }
        else {
            LastElement = temp;
        }
        length++;
    }

    void PrintElements() {
        if (length != 0) {
            Element* temp = FirstElement;
            while (temp->nextElement != 0) {
                cout << temp->value << " ";
                temp = temp->nextElement;
            }
            cout << temp->value << endl;
        }
    }

    void InsertElement(int pos, int n) {

        if (pos < 1 || pos > length + 1) {
            cout << "Element with this position does not exist";
            return;
        }

        if (pos == length + 1) {
            AddLastElement(n);
            return;
        }
        else if (pos == 1) {
            AddFirstElement(n);
            return;
        }

        int i = 1;
        Element* Insert = FirstElement;

        while (i < pos) {
            Insert = Insert->nextElement;
            i++;
        }

        Element* PrevInsert = Insert->prevElement;
        Element* temp = new Element;
        temp->value = n;

        if (PrevInsert != 0 && length != 1) {
            PrevInsert->nextElement = temp;
        }
        temp->nextElement = Insert;
        temp->prevElement = PrevInsert;
        Insert->prevElement = temp;

        length++;
    }

    void PrintElement(int pos) {
        if (pos < 1 || pos > length) {
            cout << "Element with this position does not exist";
            return;
        }

        Element* temp;

        if (pos <= length / 2) {
            temp = FirstElement;
            int i = 1;
            while (i < pos) {
                temp = temp->nextElement;
                i++;
            }
        }
        else {
            temp = LastElement;
            int i = 1;
            while (i <= length - pos) {
                temp = temp->prevElement;
                i++;
            }
        }
        cout << temp->value << endl;
    }

    void DelElement(int pos) {
        if (pos < 1 || pos > length) {
            cout << "Element with this position does not exist";
            return;
        }
        int i = 1;
        Element* DelElement = FirstElement;
        while (i < pos) {
            DelElement = DelElement->nextElement;
            i++;
        }

        Element* PrevDel = DelElement->prevElement;
        Element* AfterDel = DelElement->nextElement;

        if (PrevDel != 0 && length != 1) {
            PrevDel->nextElement = AfterDel;
        }
        if (AfterDel != 0 && length != 1) {
            AfterDel->prevElement = PrevDel;
        }


        if (pos == 1)
            FirstElement = AfterDel;
        if (pos == length)
            LastElement = PrevDel;

        delete DelElement;
        length--;
    }
};

int main(void)
{

    bidirectionalList list1;
    list1.AddLastElement(5); list1.AddLastElement(6); list1.AddLastElement(7);
    list1.PrintElements();
    list1.InsertElement(1, 4);
    list1.PrintElements();
    list1.DelElement(2);
    list1.PrintElements();
    list1.PrintElement(2);
}