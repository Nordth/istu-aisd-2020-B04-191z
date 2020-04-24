#include <cstdio>
#include <stdexcept>

struct node // структура для представления узлов дерева
{
    int key;
    int value;
    int height;
    node *left;
    node *right;

    node(int k, int v) {
        key = k;
        left = right = nullptr;
        height = 1;
        value = v;
    }
};

int height(node *p) {
    return p ? p->height : 0;
}

int balance_factor(node *p) {
    return height(p->right) - height(p->left);
}

void fixheight(node *p) {
    unsigned char left_height = height(p->left);
    unsigned char right_height = height(p->right);
    p->height = (left_height > right_height ? left_height : right_height) + 1;
}

node *rotate_right(node *p) // правый поворот вокруг p
{
    node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node *rotate_left(node *q) // левый поворот вокруг q
{
    node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}


node *balance(node *p) // балансировка узла p
{
    fixheight(p);
    if (balance_factor(p) == 2) {
        if (balance_factor(p->right) < 0)
            p->right = rotate_right(p->right);
        return rotate_left(p);
    }
    if (balance_factor(p) == -2) {
        if (balance_factor(p->left) > 0)
            p->left = rotate_left(p->left);
        return rotate_right(p);
    }
    return p; // балансировка не нужна
}

node *insert(node *p, int key, int value) // вставка ключа key в дерево с корнем p
{
    if (!p) return new node(key, value);
    if (key < p->key)
        p->left = insert(p->left, key, value);
    else
        p->right = insert(p->right, key, value);
    return balance(p);
}

node *find_min(node *p) // поиск узла с минимальным ключом в дереве p
{
    return p->left ? find_min(p->left) : p;
}


node *remove_min(node *p) // удаление узла с минимальным ключом из дерева p
{
    if (!p->left)
        return p->right;
    p->left = remove_min(p->left);
    return balance(p);
}

node *remove(node *p, int k) // удаление ключа k из дерева p
{
    if (!p) return nullptr;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else //  k == p->key
    {
        node *q = p->left;
        node *r = p->right;
        delete p;
        if (!r) return q;
        node *min = find_min(r);
        min->right = remove_min(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void print_Tree(node *p, int level) {
    if (p) {
        print_Tree(p->left, level + 1);
        for (int i = 0; i < level; i++) {
            printf("     ");
        }
        printf("%d: %d\n", p->key, p->value);
        print_Tree(p->right, level + 1);
    }
}

node *find(node *p, int key) {
    if (!p) {
        throw std::runtime_error("Not found");
    }
    if (key > p->key) {
        return find(p->right, key);
    } else if (key < p->key) {
        return find(p->left, key);
    }
    return p;
}


int main() {
    node *tree = nullptr;
    print_Tree(tree, 0);
    tree = insert(tree, 10, 3);
    print_Tree(tree, 0);
    printf("\n");
    tree = insert(tree, 2, 2);
    print_Tree(tree, 0);
    printf("\n");
    tree = insert(tree, 7, 10);
    print_Tree(tree, 0);
    printf("\n");
    tree = insert(tree, 4, 12);
    print_Tree(tree, 0);
    printf("\n");
    tree = insert(tree, 16, 11);
    print_Tree(tree, 0);
    printf("\n");
    tree = insert(tree, 12, 11);
    print_Tree(tree, 0);
    printf("\n");


    tree = remove(tree, 2);
    print_Tree(tree, 0);
    printf("\n");

    tree = remove(tree, 7);
    print_Tree(tree, 0);
    printf("\n");


    printf("key: %d value: %d\n", 16, find(tree, 16)->value);
    printf("key: %d value: %d\n", 4, find(tree, 4)->value);
    try {
        find(tree, 1234567);
    }
    catch (std::runtime_error &error) {
        printf("%s", error.what());
    }

}