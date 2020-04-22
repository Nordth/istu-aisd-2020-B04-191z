#include <cstdlib>
#include <iostream>

namespace AVL {
	using namespace std;
	struct AVLTree {
		AVLTree* left = NULL;
		AVLTree* right = NULL;
		int value = 0;
		int key = 0;
		int height = 0;
	};
	namespace Tree {
		int count = 0;
	}

	AVLTree* add(AVLTree*, int, int);
	int getHeight(AVLTree*);
	int getMax(int, int);
	void print(AVLTree*);
	int getBalance(AVLTree* root);
	AVLTree* rightRotate(AVLTree*);
	AVLTree* leftRotate(AVLTree*);
	void print(AVLTree*, int, char);
	AVLTree* get(AVLTree*, int);
	AVLTree* remove(AVLTree*, int);
	AVLTree* findMin(AVLTree*);
	AVLTree* findMax(AVLTree*);
	AVLTree* checkBalance(AVLTree*);

	AVLTree* add(AVLTree* root, int key, int value) {
		if (!root) {
			root = new AVLTree();
			root->value = value;
			root->key = key;
			root->height = 1;
			Tree::count++;
			return root;
		}
		else {
			if (key < root->key) {
				root->left = add(root->left, key, value);
				root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
				root = checkBalance(root);
				return root;
			}
			else if (key > root->key) {
				root->right = add(root->right, key, value);
				root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
				root = checkBalance(root);
				return root;
			}
			else return root;
		}
	}

	AVLTree* get(AVLTree* root, int key) {
		if (!root) return NULL;
		if (root->key == key) return root;
		if (root->key < key) return get(root->right, key);
		else return get(root->left, key);
	}

	AVLTree* remove(AVLTree* root, int key) {
		if (!root) return NULL;
		if (key > root->key) {
			root->right = remove(root->right, key);
			root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
			root = checkBalance(root);
			return root;
		}
		else if (key < root->key) {
			root->left = remove(root->left, key);
			root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
			root = checkBalance(root);
			return root;
		}
		else {
			bool isRight = false;
			AVLTree* replace;
			int balance = getBalance(root);
			if (balance <= -1) {
				replace = findMin(root->right);
				isRight = true;
			}
			else {
				replace = findMax(root->left);
			}
			if (replace && isRight) {
				root->key = replace->key;
				root->value = replace->value;
				root->right = remove(root->right, replace->key);
				root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
				root = checkBalance(root);
				return root;
			}
			else {
				if (replace && !isRight) {
					root->key = replace->key;
					root->value = replace->value;
					root->left = remove(root->left, replace->key);
					root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
					root = checkBalance(root);
					return root;
				}
				else {
					delete root;
					Tree::count--;
					return NULL;
				}
			}
		}

	}

	AVLTree* findMin(AVLTree* root) {
		if (!root) return root;
		if (!root->left) return root;
		else {
			return findMin(root->left);
		}
	}

	AVLTree* findMax(AVLTree* root) {
		if (!root) return root;
		if (!root->right) return root;
		else {
			return findMin(root->right);
		}
	}

	int getHeight(AVLTree* tree) {
		if (!tree) return 0;
		else return tree->height;
	}

	int getMax(int a, int b) {
		return a > b ? a : b;
	}

	int getBalance(AVLTree* root) {
		int hleft = getHeight(root->left);
		int hright = getHeight(root->right);
		return hleft - hright;
	}

	AVLTree* leftRotate(AVLTree* root) {
		AVLTree* t1 = root->right;
		root->right = t1->left;
		t1->left = root;
		root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
		t1->height = getMax(getHeight(t1->left), getHeight(t1->right)) + 1;
		return t1;
	}

	AVLTree* rightRotate(AVLTree* root) {
		AVLTree* t1 = root->left;
		root->left = t1->right;
		t1->right = root;
		root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
		t1->height = getMax(getHeight(t1->left), getHeight(t1->right)) + 1;
		return t1;
	}

	AVLTree* checkBalance(AVLTree* root) {
		int balance = getBalance(root);
		if (balance >= 2) {
			int leftBalance = getBalance(root->left);
			if (leftBalance < 0) {
				root->left = leftRotate(root->left);
			}
			root = rightRotate(root);

		}
		else if (balance <= -2) {
			int rightBalance = getBalance(root->right);
			if (rightBalance > 0) {
				root->right = rightRotate(root->right);
			}
			root = leftRotate(root);
		}
		return root;
	}

	void print(AVLTree* root) {
		cout << "----------PRINT TREE--------" << Tree::count << "-Size------" << endl;
		print(root, getHeight(root), 0);
		cout << "----------END OF TREE--------------" << endl;
	}

	void print(AVLTree* root, int height, char c) {
		if (!root) return;
		print(root->left, height - 1, '\\');
		for (int i = 1; i < height; i++) {
			cout << "     ";
		}
		//cout << "[" << root->value << ":" << root->height << "]" << c << " ";
		printf("[K=%d]%c ", root->key, c);
		cout << endl;
		print(root->right, height - 1, '/');
	}
}

using namespace std;

void testAVLTree() {
	cout << "------ TEST AVL TREE ------" << endl;
	cout << "Add 0-31 keys:" << endl;
	AVL::AVLTree* tree = NULL;
	for (int i = 0; i <= 31; i++) {
		tree = AVL::add(tree, i, i);
	}
	AVL::print(tree);
	cout << "Delete 4 6 7 12 keys" << endl;
	tree = AVL::remove(tree, 4);
	tree = AVL::remove(tree, 6);
	tree = AVL::remove(tree, 7);
	tree = AVL::remove(tree, 15);
	AVL::print(tree);
	cout << "------- END OF TEST AVL TREE -------" << endl;
}

int main() {
	testAVLTree();
	return 0;
}