#include <iostream>
using namespace std;

template<class T>
class Stack {
    struct node {
        T d;
        node* next;
        node(void) : next(NULL) {}
    };
private:
    node* ptr;
public:
    Stack(void) : ptr(NULL) {}
    ~Stack() {
        this->clear();
    }

    
    void  push(T d) {
        node* n = new node();
        n->next = ptr;
        n->d = d;
        ptr = n;
    }
    T& top(void) { return ptr->d; }

    
    void pop(void) {
        node* tmp = ptr;
        ptr = ptr->next;
        delete tmp;
        tmp = NULL;
    }
    bool empty(void) const { return (!ptr); }

   
    void clear(void) {
        node* tmp;
        while (ptr != NULL) {
            tmp = ptr;
            ptr = ptr->next;
            delete tmp;
            tmp = NULL;
        }
    }
};

int  main(void) {
    Stack<int> st;
    
    for (int i = 100; i <= 200; st.push(i++));

    
    while (!st.empty()) {
        cout << st.top() << ", ";
        st.pop();
    }
    cin.get();
    return 0;
}