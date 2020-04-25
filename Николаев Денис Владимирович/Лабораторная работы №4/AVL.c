/****************************************************/
/***************** 14 вариант ***********************/
/************* Сбалансированное AVL-дерево **********/
/****************************************************/

#include <stdio.h>
#include <stdlib.h>

//AVL tree
typedef struct Node {
	int key;
	int value;
	int height;
	struct Node *left;
	struct Node *right;
} Node;

void createNode(Node **node, int key, int value);
void addElement(Node **node, int key, int value);
void deleteElement(Node **node, int key);
Node* search(Node *node, int key);
void displayTree(Node *node, size_t level);
void freeMemory(Node **node);

int treeHeight(Node **node);
void treeRightRotate(Node **node);
void treeLeftRotate(Node **node);
void treeRightLeftRotate(Node **node);
void treeLeftRightRotate(Node **node);
int maxHeight(int first, int second);
Node* findMin(Node *node);
Node* removeMin(Node *node);

void test(void);

int main(void) {
	test();

	return EXIT_SUCCESS;
}

void addElement(Node **node, int key, int value) {
	if (*node == NULL) {
		createNode(node, key, value);
	} else {
		if (key < (*node)->key) { //left brach
			addElement(&(*node)->left, key, value);
			if (treeHeight(&(*node)->left) - treeHeight(&(*node)->right) == 2) {
				//tree is unbalanced
				if (key < (*node)->left->key) {
					treeRightRotate(node);
				} else {
					treeLeftRightRotate(node);
				}
			}
		} else if (key > (*node)->key) { //right branch
			addElement(&(*node)->right, key, value);
			if (treeHeight(&(*node)->right) - treeHeight(&(*node)->left) == 2) {
				//tree is unbalanced
				if (key > (*node)->right->key) {
					treeLeftRotate(node);
				} else {
					treeRightLeftRotate(node);
				}
			}
		}
	}
	(*node)->height = maxHeight(treeHeight(&(*node)->left), treeHeight(&(*node)->right)) + 1;
}

/*  findMin и removeMin вспомогательные функции, которые ищут минимальный элемент в 
* дереве, чтобы отбалансировать дерево после удаления какого-либо элемента
*/
Node* findMin(Node *node) {
	if (node->left != NULL) {
		return findMin(node->left);
	} else {
		return node;
	}
}

Node* removeMin(Node *node) {
	if (node->left == NULL) {
		return node->left;
	} else {
		node->left = removeMin(node->left);
		if (treeHeight(&(node)->left) - treeHeight(&(node)->right) == 2) {
			//tree is unbalanced
			if ((node)->right->key < (node)->left->key) {
				treeRightRotate(&node);
			} else {
				treeLeftRightRotate(&node);
			}
		}
		if (treeHeight(&(node)->right) - treeHeight(&(node)->left) == 2) {
			//tree is unbalanced
			if ((node)->left->key > (node)->right->key) {
				treeLeftRotate(&node);
			} else {
				treeRightLeftRotate(&node);
			}
		}
		return node;
	}
}

void deleteElement(Node **node, int key) {
	Node *min = NULL;
	if (*node == NULL) return;
	if ((*node)->key == key) {
		Node *l = (*node)->left;
		Node *r = (*node)->right;
		Node *temp = NULL;
		temp = (*node);
		if (r == NULL) {
			(*node) = l;
			free(temp);
			temp = NULL;
			return;
		} else {
			min = findMin(r);
			min->right = removeMin(r);
			min->left = l;
			if (treeHeight(&(min)->left) - treeHeight(&(min)->right) == 2) {
				//tree is unbalanced
				if ((min)->key < (min)->left->key) {
					treeRightRotate(&min);
				} else {
					treeLeftRightRotate(&min);
				}
			}
			if (treeHeight(&(min)->right) - treeHeight(&(min)->left) == 2) {
				//tree is unbalanced
				if ((min)->key > (min)->right->key) {
					treeLeftRotate(&min);
				} else {
					treeRightLeftRotate(&min);
				}
			}
			(*node) = min;
			free(temp);
		}

	} else {
		if (key < (*node)->key) { //left brach
			deleteElement(&(*node)->left, key);
		} else if (key > (*node)->key) { //right branch
			deleteElement(&(*node)->right, key);
		}
	}

	if (treeHeight(&(*node)->left) - treeHeight(&(*node)->right) == 2) {
		//tree is unbalanced
		if ((*node)->right->key < (*node)->left->key) {
			treeRightRotate(node);
		} else {
			treeLeftRightRotate(node);
		}
	}

	if (treeHeight(&(*node)->right) - treeHeight(&(*node)->left) == 2) {
		//tree is unbalanced
		if ((*node)->left->key > (*node)->right->key) {
			treeLeftRotate(node);
		} else {
			treeRightLeftRotate(node);
		}
	}
}

Node* search(Node *node, int key) {
	while (node != NULL) {
		if (key == node->key) {
			return node;
		} else if (key < node->key) {
			node = node->left;
		} else {
			node = node->right;
		}
	}
	return NULL;
}

void displayTree(Node *node, size_t level) {
	if (node == NULL) {
		for (size_t i = 0; i < level; ++i) {
			printf("\t");
		}
		printf("*\n");
		return;
	}
	displayTree(node->right, level + 1);
	for (size_t i = 0; i < level; ++i) {
		printf("\t");
	}
	printf("%d\n", node->key);
	displayTree(node->left, level + 1);
}

void createNode(Node **node, int key, int value) {
	*node = (Node*)malloc(sizeof(Node));
	if (*node == NULL) {
		printf("\nMemory for a tree node is not allocated.\n");
		exit(0);
	}
	(*node)->key = key;
	(*node)->value = value;
	(*node)->height = 0;
	(*node)->left = NULL;
	(*node)->right = NULL;
}

int treeHeight(Node **node) {
	if (*node != NULL) {
		return (*node)->height;
	}
	return -1;
}

void treeRightRotate(Node **node) {
	Node *ptr = NULL;
	ptr = (*node)->left;
	(*node)->left = ptr->right;
	ptr->right = *node;

	(*node)->height = maxHeight(treeHeight(&(*node)->left), treeHeight(&(*node)->right)) + 1;
	ptr->height = maxHeight(treeHeight(&ptr->left), (*node)->height) + 1;

	*node = ptr;
}

void treeLeftRotate(Node **node) {
	Node *ptr = NULL;
	ptr = (*node)->right;
	(*node)->right = ptr->left;
	ptr->left = *node;

	(*node)->height = maxHeight(treeHeight(&(*node)->left), treeHeight(&(*node)->right)) + 1;
	ptr->height = maxHeight(treeHeight(&ptr->right), (*node)->height) + 1;

	*node = ptr;
}

void treeRightLeftRotate(Node **node) {
	treeRightRotate(&(*node)->right);
	treeLeftRotate(node);
}

void treeLeftRightRotate(Node **node) {
	treeLeftRotate(&(*node)->left);
	treeRightRotate(node);
}

int maxHeight(int first, int second) {
	if (first >= second) {
		return first;
	}
	return second;
}

void freeMemory(Node **node) {
	if (*node != NULL) {
		freeMemory(&(*node)->left);
		(*node)->left = NULL;
		freeMemory(&(*node)->right);
		(*node)->right = NULL;
		free(*node);
		*node = NULL;
	}
}

void test(void) {
	Node *tree = NULL;
	Node* foundElement = NULL;
	int key = 3;
	printf("-------------------------------------------------\n");
	printf("Adding elements:\n");
    printf("-------------------------------------------------\n");
	addElement(&tree, 10, 10);
	addElement(&tree, 5, 5);
	addElement(&tree, 3, 10);

	displayTree(tree, 0);
	printf("-------------------------------------------------\n");

	addElement(&tree, 11, 11);
	addElement(&tree, 12, 12);

	displayTree(tree, 0);
	printf("-------------------------------------------------\n");
	addElement(&tree, 15, 11);
	addElement(&tree, 4, 2);

	displayTree(tree, 0);

	printf("-------------------------------------------------\n");
	addElement(&tree, 17, 11);
	addElement(&tree, 20, 2);

	displayTree(tree, 0);
	printf("-------------------------------------------------\n");
    
    
    printf("Looking for the element #3:\n");
    printf("-------------------------------------------------\n");

	foundElement = search(tree, key);

	if (foundElement != NULL) {
		printf("\nFound value (key = %d): %d\n", key, foundElement->value);
	} else {
		printf("\nThere is not such element (%d).\n", key);
	}
	printf("-------------------------------------------------\n");
		
	printf("Deleting elements:\n");
	printf("-------------------------------------------------\n");
	deleteElement(&tree, 5);
	displayTree(tree, 0);
	printf("-------------------------------------------------\n");
	deleteElement(&tree, 10);
	displayTree(tree, 0);
	printf("-------------------------------------------------\n");
	deleteElement(&tree, 1);
	displayTree(tree, 0);

	freeMemory(&tree);
}
