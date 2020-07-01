#include <iostream>
#include <ctime>

using namespace std;

template <typename T>
class Data {
public:
	int key;
	T value;
	int height;
	Data<T>* right = NULL;
	Data<T>* left = NULL;

	Data() {
		this->height = 1;
	}

	Data(int key, T value) {
		this->key = key;
		this->value = value;
		this->height = 1;
	}

	void print() {
		cout << "Key = " << key << " Value = " << value << " Height =" << height << endl;
		cout << "Left = " << left << " Right = " << right << endl;
	}
};

template <typename T>
class Tree {
private:

	Data<T>* root = NULL;

public:
	void add(int key, T value) {
		root = add(root, key, value);
	}

	T get(int key) {
		return get(root, key);
	}

	void remove(int key) {
		root = remove(root, key);
	}

	void print() {
		print(root, getHeight(root), 0);
		cout << " ---------------------------------- " << endl;
	}
private:

	int getMaxValue(int a, int b) {
		if (a > b) return a;
		return b;
	}

	int getHeight(Data<T>* root) {
		if (!root) {
			return 0;
		}
		else return root->height;
	}

	int newHeight(Data<T>* root) {
		return getMaxValue(getHeight(root->left), getHeight(root->right)) + 1;
	}

	int getBalance(Data<T>* root) {
		int hLeft = getHeight(root->left);
		int hRight = getHeight(root->right);
		return hLeft - hRight;
	}

	Data<T>* leftRotate(Data<T>* root) {
		Data<T>* t = root->right;
		root->right = t->left;
		t->left = root;
		root->height = newHeight(root);
		t->height = newHeight(t);
		return t;
	}

	Data<T>* rightRotate(Data<T>* root) {
		Data<T>* t = root->left;
		root->left = t->right;
		t->right = root;
		root->height = newHeight(root);
		t->height = newHeight(t);
		return t;
	}

	Data<T>* checkBalance(Data<T>* root) {
		int balance = getBalance(root);
		if (balance <= -2) {
			if (getBalance(root->right) >= 1) {
				root->right = rightRotate(root->right);
			}
			return leftRotate(root);
		}
		else if (balance >= 2) {
			if (getBalance(root->left) <= -1) {
				root->left = leftRotate(root->left);
			}
			return rightRotate(root);
		}
		else return root;
	}

	Data<T>* getMin(Data<T>* root) {
		if (!root) return NULL;
		if (!root->left) return root;
		else return getMin(root->left);
	}

	Data<T>* add(Data<T>* root, int key, T value) {
		if (root == NULL) {
			return new Data<T>(key, value);
		}
		else {
			if (key < root->key) {
				root->left = add(root->left, key, value);
				root->height = newHeight(root);
				root = checkBalance(root);
				return root;
			}

			else if (key > root->key) {
				root->right = add(root->right, key, value);
				root->height = newHeight(root);
				root = checkBalance(root);
				return root;
			}
			else {
				root->value = value;
				return root;
			}
		}
	}

	T get(Data<T>* root, int key) {
		if (!root) return NULL;
		if (root->key < key) {
			return get(root->right, key);
		}
		else if (root->key > key) {
			return get(root->left, key);
		}
		else return root->value;
	}

	Data<T>* remove(Data<T>* root, int key) {
		if (!root) return root;
		else if (root->key == key) {
			if (!root->left && !root->right) {
				delete root;
				return NULL;
			}
			else if (root->left && !root->right) {
				Data<T>* t = root->left;
				delete root;
				return t;
			}
			else if (!root->left && root->right) {
				Data<T>* t = root->right;
				delete root;
				return t;
			}
			else {
				Data<T>* min = getMin(root->right);
				root->key = min->key;
				root->value = min->value;
				root->right = remove(root->right, min->key);
				root->height = newHeight(root);
				root = checkBalance(root);
				return root;
			}
		}
		else if (root->key > key) {
			root->left = remove(root->left, key);
			root->height = newHeight(root);
			root = checkBalance(root);
			return root;
		}
		else if (root->key < key) {
			root->right = remove(root->right, key);
			root->height = newHeight(root);
			root = checkBalance(root);
			return root;
		}
	}

	void print(Data<T>* root, int h, char c) {
		if (!root) return;
		print(root->left, h - 1, '\\');
		for (int i = 0; i < h; i++) {
			cout << "    ";
		}
		cout << "[" << root->key << "]" <<endl;
		print(root->right, h - 1, '/');
		return;
	}
};



int main() {
	srand(time(NULL));
	int size = 20;
	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 500 -250;
	}
	Tree<int>* t = new Tree<int>();

	for (int i = 0; i < size; i++) {
		t->add(arr[i], i);
	}
	t->print();
	for (int i = 0; i < size/2; i++) {
		t->remove(arr[rand()%size]);
	}
	t->print();

	for (int i = 0; i < size / 4; i++) {
		int key = arr[rand() % size];
		cout << t->get(key) << endl;
	}
}