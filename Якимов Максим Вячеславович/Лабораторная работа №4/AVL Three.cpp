#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>

using namespace std;

struct uzel
{
	uzel *left;
	uzel *right;
	int higt;
	int higt_left;
	int higt_right;
	int key;
	int valio;
	uzel (int x) {
		valio = x;
		key = x % 222 + x % 33 + x % 55;
		left = nullptr;
		right = nullptr;
		higt = 1;
		higt_left = 0;
		higt_right = 0;
	}
	uzel() {};
};

uzel *check_high(uzel *a) {
	if (!a) return a;
	else if (a->left == nullptr&&a->right == nullptr) {
		a->higt_left = 0;
		a->higt_right = 0;
		a->higt = 1 +max (a->higt_left, a->higt_right);
		return a;
	}
	else if (!a->left&&a->right) {
		a->higt_left = 0;
		a->higt_right = a->right->higt;
		a->higt = 1 + max(a->higt_left, a->higt_right);
		return a;
	}
	else if (a->left && !a->right) {
		a->higt_right = 0;
		a->higt_left = a->left->higt;
		a->higt = 1 + max(a->higt_left, a->higt_right);
		return a;
	}
	else if (a->left&&a->right) {
		a->higt_right = a->right->higt;
		a->higt_left = a->left->higt;
		a->higt = 1 + max(a->higt_left, a->higt_right);
		return a;
	}
}

uzel *small_right(uzel *a) {
	uzel *buff = nullptr;
	buff = a;
	a = a->left;
	buff->left = a->right;
	a->right = buff;
	a->right = check_high(a->right);
	a = check_high(a);
	return a;
}

uzel *small_left(uzel *a) {
	uzel *buff = nullptr;
	buff = a;
	a = a->right;
	buff->right = a->left;
	a->left = buff;
	a->left = check_high(a->left);
	a = check_high(a);
	return a;
}

uzel *big_right(uzel *a) {
	a->left = small_left(a->left);
	a = small_right(a);
	return a;
}

uzel *big_left(uzel *a) {
	a->right = small_right(a);
	a = small_left(a);
	return a;
}

uzel *correction(uzel *a) {
	a = check_high(a);
	if (!a) return a;
	else if (abs(a->higt_left - a->higt_right) < 2) {
		return a;
	}
	else if (a->left > a->right) {
		if (a->left->higt_left >= a->left->higt_right) {
			a = small_right(a);
			return a;
		}
		else {
			a = big_right(a);
			return a;
		}
	}
	else if (a->left<a->right) {
		if (a->right->higt_left <= a->right->higt_right) {
			a = small_left(a);
			return a;
		}
		else {
			a = big_left(a);
			return a;
		}
	}
}

uzel *add(int val, uzel *uz) {
	if (!uz) {
		uz = new uzel(val);
		return uz;
	}
	int sravn= val  % 222 + val % 33 + val % 55;
	if (sravn < uz->key) {
		uz->left = add(val, uz->left);
	}
	else {
		uz->right = add(val, uz->right);
	}
	if (uz->left) {
		uz->higt_left = 1+ uz->left->higt;
	}
	if (uz->right) {
		uz->higt_right = 1+ uz->right->higt_right;
	}
	uz->higt = 1 + max(uz->higt_left, uz->higt_right);
	uz = correction(uz);
	return uz;
}

bool success(uzel *a, int k) {
	if (!a)return false;
	if (a->key == k) {
		return true;
	}
	else if (a->key < k) {
		return success(a->right, k);
	}
	else if (a->key > k) {
		return success(a->left, k);
	}
}

void print(uzel *a) {
	string probel{ "      " };
	if (!a) return;
	int numb = a->higt;
	print(a->left);
	while (numb > 0) {
		cout << probel;
		numb--;
	}
	cout << a->key << ' ' << a->valio << '\n';
	print(a->right);
}

int finde_val(uzel *u, int k) {
	if (success(u, k)) {
		if (u->key == k) {
			return u->valio;
		}
		else if (k < u->key) {
			return finde_val(u->left, k);
		}
		else if (k > u->key) {
			return finde_val(u->right, k);
		}
	}
	else return -999; //код не нахождения числа
}

uzel **finde_max (uzel *a) {
	uzel *buff=nullptr;
	if (a->right == 0) {
		return &a;
	}
	else return finde_max(a->right);
}

uzel **finde_min(uzel *a) {
	if (a->left == 0) {
		return &a;
	}
	else return finde_min(a->left);
}

uzel *delete_min(uzel *a) {
	if (a->left == 0) {
		uzel *buff = a;
		a = a->right;
		a = correction(a);
		delete buff;
		return a;
	}
	else {
		a->left = delete_min(a->left);
		a = correction(a);
		return a;
	}
}

uzel *delete_max(uzel *a) {
	if (a->right == 0) {
		uzel *buff = a;
		a = a->left;
		a = correction(a);
		delete buff;
		return a;
	}
	else {
		a->right = delete_max(a->right);
		a = correction(a);
		return a;
	}
}

uzel *remoove(uzel *a, int k) {
	if (!a||!success(a, k)) return a;
	else if (k == a->key&&a->left == nullptr&&a->right == nullptr) {
		delete a;
		return nullptr;
	}
	else if (k == a->key&&a->left && !a->right) {
		uzel *buff = a;
		a = a->left;
		delete buff;
		a = correction(a);
		return a;
	}
	else if (k == a->key && !a->left && a->right) {
		uzel *buff = a;
		a = a->right;
		delete buff;
		a = correction(a);
		return a;
	}
	else if (k == a->key&&a->left&&a->right) {
		uzel **ukaz = nullptr;
		ukaz = finde_max(a->left);
		a->key = (*ukaz)->key;
		a->valio = (*ukaz)->valio;
		a->left = delete_max(a->left);
		a = correction(a);
		return a;
	}
	else if (k > a->key) {
		a->right = remoove(a->right, k);
		a = correction(a);
		return a;
	}
	else if (k < a->key) {
		a->left = remoove(a->left, k);
		a = correction(a);
		return a;
	}
}

int main() {
	uzel *a = nullptr;
	cout << "there are two things on line a key and a valio \n feeling of tree\n";
	a = add(9, a);
	a = add(8, a);
	a = add(7, a);
	a = add(6, a);
	print(a); cout << endl;
	cout << "\n feeling of tree continue\n";
	a = add(5, a);
	a = add(4, a);
	a = add(3, a);
	a = add(2, a);
	print(a); cout << endl;
	cout << "\n remoove valio with key 12\n";
	a = remoove(a, 18);
	print(a); cout << endl;
	cout << "\n feeling of tree continue\n";
	a = add(1, a);
	a = add(10, a);
	a = add(12, a);
	a = add(13, a);
	a = add(14, a);
	a = add(15, a);
	a = add(16, a);
	print(a); cout << endl;
	cout << "\n remoove valio with key 30\n";
	a = remoove(a, 30);
	print(a); cout << endl;
	cout << "\n remoove valio with key 12\n";
	a = remoove(a, 12);
	print(a); cout << endl;
	cout << "\n remoove valio with key 15\n";
	a = remoove(a, 15);
	print(a); cout << endl;
	cout << "\n output of valios with keys 19, 24, 27, 3\n";
	cout << finde_val(a, 19) << '\n';
	cout << finde_val(a, 24) << '\n';
	cout << finde_val(a, 27) << '\n';
	cout << finde_val(a, 3) << '\n';
}