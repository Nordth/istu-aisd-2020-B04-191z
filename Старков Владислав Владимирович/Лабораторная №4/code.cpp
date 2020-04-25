#include <iostream>
using namespace std;

struct Node
{
    int value = 0;
    int key = 0;
    int height = 0;
    Node *left = NULL;
    Node *right = NULL;
};

int GetHeight(Node *unit)
{
    if (unit) return unit->height;
    else return 0;
};

int GetBalance(Node *unit)
{
    return GetHeight(unit->right) - GetHeight(unit->left);
};

Node *RightRotation(Node *x)
{
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
};

Node *LeftRotation(Node *y)
{
    Node *x = y->right;
    y->right = x->left;
    x->left = y;
    return x;
};

Node *Balance(Node *x)
{
    if (GetBalance(x) == 2)
    {
        if (GetBalance(x->right) < 0)
            x->right = RightRotation(x->right);
        return LeftRotation(x);
    }
    if (GetBalance(x) == -2)
    {
        if (GetBalance(x->left) > 0) x->left = LeftRotation(x->left);
        return RightRotation(x);
    }
    return x;
};

Node *Append(Node *x, int key, int value)
{
    if (!x)
    {
        Node *new_node = new Node();
        new_node->key = key;
        new_node->value = value;
        new_node->left = nullptr;
        new_node->right = nullptr;
        return new_node;
    }
    if (key < x->key) x->left = Append(x->left, key, value);
    else x->right = Append(x->right, key, value);
    return Balance(x);
};

Node *GetNode(Node *root, int key)
{
    if (!root) return NULL;
    if (root->key == key) return root;
    if (root->key < key) return GetNode(root->right, key);
    else return GetNode(root->left, key);
}

Node *SearchMinimal(Node *x)
{
    if (x->left) return SearchMinimal(x->left);
    else return x;
};

Node *DeleteMinimal(Node *x)
{
    if (x->left == 0) return x->right;
    x->left = DeleteMinimal(x->left);
    return Balance(x);
};

Node *Delete(Node *x, int key)
{
    if (!x) return 0;
    if (key < x->key)
        x->left = Delete(x->left, key);
    else if
        (key > x->key) x->right = Delete(x->right, key);
    else
    {
        Node *y = x->left;
        Node *z = x->right;
        delete x;
        if (!z) return y;
        Node* min = SearchMinimal(z);
        min->right = DeleteMinimal(z);
        min->left = y;
        return Balance(min);
    }
    return Balance(x);
};

void Display(Node *node)
{
	if (!node) return;
	Display(node->left);
	cout << node->key << "|";
	Display(node->right);
}

int main()
{
	Node *tree = nullptr;
    Node *ForRemoveAndGet = nullptr;
    for( int i = 1; i <= 16; i++)
        tree = Append(tree, i, i);
	Display(tree);
    ForRemoveAndGet = GetNode(tree, 7);
	cout << "\n";
    cout << ForRemoveAndGet->key << " " << ForRemoveAndGet->value;
	cout << "\n";
    ForRemoveAndGet = tree;
	ForRemoveAndGet = Delete(tree, 2);
	Display(tree);
    return 0;
}