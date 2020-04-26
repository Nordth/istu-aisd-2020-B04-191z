/*Реализовать сбалансированное АВЛ - дерево
Дерево должно поддерживать следующие операции :
1) Вставка элемента(целочисленный ключ + значение)
2) Получение значения элемента по ключу
3) Удаление элемента по ключу
4) Печать всех элементов дерева
*/

#include <iostream>

using namespace std;

struct AVL {
    int key, height;
    AVL* left;
    AVL* right;
    AVL(int k) { key = k; left = right = 0; height = 1; }
};

int height(AVL* p) {
    if (p == NULL) return 0;
    return p->height;
}

int balfac(AVL* p) {
    return height(p->right) - height(p->left);
}

void fixedH(AVL* p) {
    int temp;
    int Hleft = height(p->left);
    int Hright = height(p->right);
    if (Hleft > Hright) temp = Hleft + 1;
    else temp = Hright + 1;
    p->height = temp;
}

AVL* rotR(AVL* p) {
    AVL* q = p->left;
    p->left = q->right;
    q->right = p;
    fixedH(p);
    fixedH(q);
    return q;
}

AVL* rotL(AVL* q) {
    AVL* p = q->right;
    q->right = p->left;
    p->left = q;
    fixedH(q);
    fixedH(p);
    return p;
}

AVL* BalanceTree(AVL* p) {
    fixedH(p);
    if (balfac(p) == 2)
    {

        if (balfac(p->right) < 0) p->right = rotR(p->right);
        return rotL(p);
    }
    if (balfac(p) == -2)
    {
        if (balfac(p->left) > 0) p->left = rotL(p->left);
        return rotR(p);
    }
    return p;
}

AVL* Add(AVL* p, int k) {
    if (!p) return new AVL(k);
    if (k < p->key) p->left = Add(p->left, k);
    else p->right = Add(p->right, k);
    return BalanceTree(p);
}

AVL* SRCmin(AVL* p)
{
    return p->left ? SRCmin(p->left) : p;
}

AVL* DELmin(AVL* p)
{

    if (p->left == 0) return p->right;
    p->left = DELmin(p->left);
    return BalanceTree(p);
}

AVL* DelKey(AVL* p, int k) // удаление ключа k из дерева p
{
    if (!p) return 0;
    if (k < p->key) p->left = DelKey(p->left, k);
    else if (k > p->key) p->right = DelKey(p->right, k);
    else
    {
        AVL* q = p->left;
        AVL* r = p->right;
        delete p;
        if (!r) return q;
        AVL* min = SRCmin(r);
        min->right = DELmin(r);
        min->left = q;
        return BalanceTree(min);
    }
    return BalanceTree(p);
}

void Display(AVL* p) {
    if (p != NULL)
    {
        cout << p->key << " ";
        Display(p->left);
        Display(p->right);
    }

}

AVL* FindForKey(int k, AVL* p) {
    if (p == NULL || k == p->key) return p;
    if (k < p->key) return FindForKey(k, p->left);
    if (k > p->key) return FindForKey(k, p->right);
}

int main()
{
    setlocale(LC_ALL, "Rus");
    AVL* NewTree = NULL;
    NewTree = Add(NewTree, 9);
    NewTree = Add(NewTree, 5);
    NewTree = Add(NewTree, 10);
    NewTree = Add(NewTree, 0);
    NewTree = Add(NewTree, 6);
    NewTree = Add(NewTree, 11);
    NewTree = Add(NewTree, -1);
    NewTree = Add(NewTree, 1);
    NewTree = Add(NewTree, 2);

    cout << "Исходное AVL дерево: ";
    Display(NewTree);
    cout << endl;

    NewTree = DelKey(NewTree, 10);
    cout << "AVL дерево после операции удаления: ";
    Display(NewTree);
    cout << endl;

    cout << "AVL дерево поиск по ключу 6: ";
    NewTree = FindForKey(6, NewTree);
    Display(NewTree);
}