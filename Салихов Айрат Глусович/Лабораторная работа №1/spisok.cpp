#include <iostream> using namespace std; struct Node 
{
int value;  	Node* next = NULL;
};

Node* add(Node* root_, int val) {
	if (root_ == NULL) {
		Node* newElem = new Node();  	 	newElem->value = val;  	 	return newElem;
	}
	else {
		//TODO: Esli znachenie uzhe est  	 	Node* head = root_; 
		while (root_->next) { // Нахождение последнего элемента в списке 
			root_ = root_->next;
		}

		Node* newElem = new Node(); // Создание нового элемента  	 	newElem->value = val; 

		root_->next = newElem; // Последний элемент списка указывает на новый созданный  	 	return head;  // возвращаем голову списка 
	}
}

bool addAfter(Node* after, int val) {
	if (after == NULL) return false;// если узла нет то false  	if (after->next == NULL) { //если элемент последний 
	Node* newElem = new Node(); // Создание нового элемента  	 	newElem->value = val; 
	after->next = newElem;//текущий элемент указывает на новый  	 	return true;//возвращает true 
}
else {
Node* next = after->next;// присваеваем next след значение 
Node* newElem = new Node(); // Создание нового элемента  	newElem->value = val; 
after->next = newElem;//присваеваем текущему элементу указатель на новый 
элемент  	 	newElem->next = next;//присваеваем к новому элементу на указатель предыдущего 
	}
}

Node* find_elem(Node* root, int val) {
	while (root->value != val) {// пока  значение текущего не равно значению которое мы ищем  	 	root = root->next;// переход к след элементу  	 	if (!root) return NULL;//если не нышла -> выходим 
	}
	return root;
}

void printList(Node* root) {
	while (root) {
		cout << root->value << " -> ";  	 	root = root->next;
	}
	cout << "NULL" << endl;
}

bool Delete(Node** Head, Node* root, int val) {


	Node* forDelete = find_elem(root, val); //присваеаем forDelete найденный элемент  	if (forDelete == NULL)// пройдется по листу и если нет этого элемента вернет NULL 
	{
		return false;//вернет ложь 
	}

	else
	{
	if (forDelete == root) // если forDelete первый  
	{
		*Head = root->next;//присваеваем голове указатель на след элемент  	 	delete forDelete;  	 	return true; 
	}
	while (root->next != forDelete)
	{
		root = root->next; //находим предыдущий элемент удаляемого 
	}
	root->next = forDelete->next;// связываем предыдущий и следующий элемент удаляемого 
	delete forDelete;  	 	return true;
	}
}

Node* erase(Node* root) {
	Node* next;  	while (root) {
		next = root;// присваиваем next указатель на текущий элемент  	 	root = root->next; //присваиваем root значение следующего 
		delete next;
	}
	return NULL;
}

int main()
{
	Node* root = 0;  	root = add(root, 1);  	root = add(root, 2);  	root = add(root, 3);  	root = add(root, 4);

	printList(root);
	Node* f = find_elem(root, 2);  	addAfter(f, 13);  	printList(root);
	Delete(&root, root, 4);
	printList(root); root = erase(root);
	printList(root);
}
