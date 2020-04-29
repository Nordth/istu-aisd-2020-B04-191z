// AVL tree implementation in C++
//... 
#include <iostream>
using namespace std;

struct Node{
  int key;
  int value;
  Node *left;
  Node *right;
  int height;
};

int max(int a, int b);

int height(Node *N){
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b){
  return (a > b) ? a : b;
}

Node *newNode(int key, int value){
  Node *node = new Node();
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->value = value;
  node->height = 1;
  return (node);
}

Node *rightRotate(Node *y){
  Node *x = y->left;
  Node *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left),
          height(y->right)) +
        1;
  x->height = max(height(x->left),
          height(x->right)) +
        1;
  return x;
}

Node *leftRotate(Node *x){
  Node *y = x->right;
  Node *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left),
          height(x->right)) +
        1;
  y->height = max(height(y->left),
          height(y->right)) +
        1;
  return y;
}

int getBalanceFactor(Node *N){
  if (N == NULL)
    return 0;
  return height(N->left) -
       height(N->right);
}

Node *insertNode(Node *node, int key, int value){
  if (node == NULL)
    return (newNode(key, value));
  if (key < node->key)
    node->left = insertNode(node->left, key, value);
  else if (key > node->key)
    node->right = insertNode(node->right, key, value);
  else
    return node;
  node->height = 1 + max(height(node->left),
               height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1)
  {
    if (key < node->left->key)
    {
      return rightRotate(node);
    }
    else if (key > node->left->key)
    {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1)
  {
    if (key > node->right->key)
    {
      return leftRotate(node);
    }
    else if (key < node->right->key)
    {
      node->left = rightRotate(node->left);
      return leftRotate(node);
    }
  }
  return node;
}

Node *nodeWithMimumValue(Node *node){
  Node *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

Node *deleteNode(Node *root, int key){
  if (root == NULL)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else
  {
    if ((root->left == NULL) ||
      (root->right == NULL))
    {
      Node *temp = root->left ? root->left : root->right;
      if (temp == NULL)
      {
        temp = root;
        root = NULL;
      }
      else
        *root = *temp;
      delete temp;
    }
    else
    {
      Node *temp = nodeWithMimumValue(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right,
                   temp->key);
    }
  }
  if (root == NULL)
    return root;
  root->height = 1 + max(height(root->left),
               height(root->right));
  int balanceFactor = getBalanceFactor(root);
  if (balanceFactor > 1)
  {
    if (getBalanceFactor(root->left) >= 0)
    {
      return rightRotate(root);
    }
    else
    {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1)
  {
    if (getBalanceFactor(root->right) <= 0)
    {
      return leftRotate(root);
    }
    else
    {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}

int getNode(Node* node, int key){
	if (node==NULL) return -1;
	if (node->key == key) return node->value;
	if (key < node->key) return getNode(node->left, key);
	if (key > node->key) return getNode(node->right, key);
}

void printTree(Node *root){
  if (root != NULL)
  {
    printTree(root->left);
    cout << root->key << " ";
    printTree(root->right);
  }
}

int main(){
  Node *root = NULL;
  root = insertNode(root, 33, 1);
  root = insertNode(root, 13, 1);
  root = insertNode(root, 53, 1);
  root = insertNode(root, 9, 1);
  root = insertNode(root, 21, 1);
  root = insertNode(root, 61, 51);
  root = insertNode(root, 8, 1);
  root = insertNode(root, 11, 1);
  printTree(root);
  root = deleteNode(root, 13);
  cout << endl << "After deleting " << endl;
  cout << "Get Node(value) with key = 61 : value = " << getNode(root, 61)<< endl;
  printTree(root);
}
