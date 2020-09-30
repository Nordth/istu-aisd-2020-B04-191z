#include <iostream>
using namespace std;
struct Node
{
	int value;
	Node* next = NULL;
};

Node* add(Node* root_, int val) {
	if (root_ == NULL) {
		Node* newElem = new Node();
		newElem->value = val;
		return newElem;
	}
	else {
		
		Node* head = root_;
		while (root_->next) { 
			root_ = root_->next;
		}

		Node* newElem = new Node();
		newElem->value = val;

		root_->next = newElem; 
		return head;  
	}
}

bool addAfter(Node* after, int val) {
	if (after == NULL) return false;
	if (after->next == NULL) { 
		Node* newElem = new Node(); 
		newElem->value = val;
		after->next = newElem;
		return true;
	}
	else {
		Node* next = after->next;
		Node* newElem = new Node(); 
		newElem->value = val;
		after->next = newElem;
		newElem->next = next;
	}
}

Node* find_elem(Node* root, int val) {
	while (root->value != val) {
		root = root->next;
		if (!root) return NULL;
	}
	return root;
}

void printList(Node* root) {
	while (root) {
		cout << root->value << " -> ";
		root = root->next;
	}
	cout << "NULL" << endl;
}


bool Delete(Node** Head, Node* root, int val) {


	Node* forDelete = find_elem(root, val); 
	if (forDelete == NULL)
	{
		return false;
	}

	else
	{
		if (forDelete == root) 
		{
			*Head = root->next;
			delete forDelete;
			return true;
		}
		while (root->next != forDelete)
		{
			root = root->next; 
		}
		root->next = forDelete->next;
		delete forDelete;
		return true;
	}
}

Node* erase(Node* root) {
	Node* next;
	while (root) {
		next = root;
		root = root->next;
		delete next;
	}
	return NULL;
}


int main()
{
	Node* root = 0;
	root = add(root, 1);
	root = add(root, 2);
	root = add(root, 3);
	root = add(root, 4);


	printList(root);
	Node* f = find_elem(root, 2);
	addAfter(f, 13);
	printList(root);

	Delete(&root, root, 4);

	printList(root);
	root = erase(root);
	printList(root);
}