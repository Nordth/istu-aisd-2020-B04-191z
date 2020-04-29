#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

struct node // структура для представления узлов дерева
{
	int keyy;
	int val;
	int height;
	node* left;
	node* right;
	node(int k) { val = k;
	keyy = k % 222 + k % 33 + k % 55; 
	left = right = 0; 
	height = 1; }
	node() {}
};

int height(node* p)
{
	return p ? p->height : 0;
}

int bfactor(node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}


node* insert(node* p, int k) // вставка значения в дерево с корнем p
{
	if (!p) return new node(k);
	int u = k % 222 + k % 33 + k % 55;
	if (u < p->keyy)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findmin(p->left) : p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->keyy)
		p->left = remove(p->left, k);
	else if (k > p->keyy)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

bool findVal(node* w, int key, int &val) {
	if (!w)
		return false;
	else if (key == w->keyy) {
		val = w->val;
		return true;
	}
	else if (key < w->keyy) 
		return findVal(w->left, key, val);
	else if (key > w->keyy) 
		return findVal(w->right, key, val);
}

void printTree(node *node) {
	string probel = "       ";
	if (!node) return;
	printTree(node->left);
	int i = node->height-1;
	while (i!=0)
	{
		cout << probel;
		i--;
	}
	printf("%d %d\n", node->val, node->keyy);
	printTree(node->right);
}

int main() {
	
	node *a=nullptr;
	int zn;
	cout << "There are two numbers in a line, first is value, second is key\n";
	a = insert(a, 12);
	a = insert(a, 23);
	a = insert(a, 3);
	a = insert(a, 78);
	a = insert(a, 15);
	printTree(a);
	cout << endl<<endl;
	cout << "finde valio with key =113\n";
	findVal(a, 113, zn)? cout<<zn:cout<<"key not exists";
	cout << endl << endl;
	cout << "delete valio with key =113\n";
	a = remove(a, 113);
	printTree(a);
	cout << endl << endl;
	cout << "add another three elements\n";
	a = insert(a, 40);
	a = insert(a, 18);
	a = insert(a, 97);
	printTree(a);
	cout << endl << endl;
	cout << "finde valio with key =87\n";
	findVal(a, 87, zn) ? cout << zn : cout << "key not exists";
	cout << endl << endl;
	cout << "delete valio with key =87\n";
	a = remove(a, 87);
	printTree(a);
	cout << endl << endl;
	a = remove(a, 77);
	cout << "delete valio with key =77\n";
	printTree(a);
	cout << endl << endl;
}