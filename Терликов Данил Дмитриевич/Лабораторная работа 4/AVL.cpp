#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

struct AVL {
	AVL* left = NULL;
	AVL* right = NULL;
	int key = 0;
	int value = 0;
	int height = 1;
};

struct AVLWorker {
private:
	void print(AVL* root, int height, char c) {
		if (!root) return;
		print(root->left, height-1, '\\');
		for (int i = 1; i < height; i++) {
			cout << "      ";
		}
		cout << "[" << root->key << "]" << c << endl;
		print(root->right, height-1, '/');
	}

	int getMax(int a, int b) {
		if (a > b) return a;
		else return b;
	}

	int getHeight(AVL* root) {
		if (!root) return 0;
		else {
			return root->height;
		}
	}

	int getBalance(AVL* root) {
		if (!root) return 0;
		int heightLeft = getHeight(root->left);
		int heightRight = getHeight(root->right);
		return heightLeft - heightRight;
	}

	AVL* rebalance(AVL* root) {
		int balance = getBalance(root);
		if (balance >= 2) {
			if (getBalance(root->left) < 0) {
				root->left = leftRotate(root->left);
			}
			return rightRotate(root);
		}
		if (getBalance(root->right) > 0) {
			root->right = rightRotate(root->right);
		}
		return leftRotate(root);
	}

	AVL* leftRotate(AVL* root) {
		AVL* t = root->right;
		root->right = t->left;
		t->left = root;
		root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
		t->height = getMax(getHeight(t->left), getHeight(t->right)) + 1;
		return t;
	}

	AVL* rightRotate(AVL* root) {
		AVL* t = root->left;
		root->left = t->right;
		t->right = root;
		root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
		t->height = getMax(getHeight(t->left), getHeight(t->right)) + 1;
		return t;
	}

	AVL* findMin(AVL* root) {
		if (!root) return NULL;
		if (!root->left) return root;
		return findMin(root->left);
	}

	AVL* findMax(AVL* root) {
		if (!root) return NULL;
		if (!root->right) return root;
		return findMax(root->right);
	}

public:
	AVL* add(AVL* root, int key, int value) {
		if (!root) {
			AVL* data = new AVL();
			data->key = key;
			data->value = value;
			return data;
		}
		if (key < root->key) {
			root->left = add(root->left, key, value);
		}
		else if (key > root->key) {
			root->right = add(root->right, key, value);
		}
		else if (key == root->key) {
			root->value = value;
			return root;
		}
		root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
		int balance = getBalance(root);
		if (abs(balance) >= 2) {
			root = rebalance(root);
		}
		return root;
	}

	AVL* get(AVL* root, int key) {
		if (!root) {
			cout << "-----NO ELEMENT WITH key=" << key << endl;
			return NULL;
		}
		else if (key == root->key) {
			return root;
		}
		else if (key < root->key) {
			return get(root->left, key);
		}
		return get(root->right, key);
	}

	AVL* remove(AVL* root, int key) {
		if (!root) {
			cout << "-------Can't find element with key=" << key << endl;
			return NULL;
		}
		if (key == root->key) {
			if (!root->right) {
				AVL* t = root->left;
				delete root;
				return t;
			}
			else if (!root->left) {
				AVL* t = root->right;
				delete root;
				return t;
			}
			else {
				AVL* tMin = findMin(root->right);
				AVL* tMax = findMax(root->left);
				if (tMin) {
					root->key = tMin->key;
					root->value = tMin->value;
					root->right = remove(root->right, tMin->key);
				}
				else if (tMax) {
					root->key = tMax->key;
					root->value = tMax->value;
					root->left = remove(root->left, tMax->key);
				}
			}
		}
		else if (key < root->key) {
			root->left = remove(root->left, key);
		}
		else if (key > root->key) {
			root->right = remove(root->right, key);
		}
		root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
		int balance = getBalance(root);
		if (abs(balance) >= 2) {
			root = rebalance(root);
		}
		return root;
	}

	void print(AVL* root) {
		cout << "------------------ PRINT TREE ----------------------" << endl;
		print(root, getHeight(root), 0);
		cout << "------------------ __________ ----------------------" << endl;
	}
};

int main() {
	srand(time(NULL));
	AVLWorker tree;
	AVL* root = NULL;
	for (int i = 0; i <= 7; i++) {
		root = tree.add(root, i, i);
	}
	tree.print(root);
	root = tree.remove(root, 0);
	root = tree.remove(root, 1);
	root = tree.remove(root, 2);
	tree.print(root);
	for (int i = 13; i <= 20; i++) {
		root = tree.add(root, i, i);
	}
	tree.print(root);
	root = tree.remove(root, 18);
	root = tree.remove(root, 19);
	tree.print(root);
	return 0;
}