#include <iostream>

using namespace std;

struct wood
{
    int value;
   wood *left;
   wood *right; 
};

wood *add(wood* tree, int val)
{
    if(!tree)//если нет то задаем 1 элемент
    {
        wood *tree = new wood(); //экземляр класс дерева
        tree -> value = val;
        tree -> left = nullptr;
        tree -> right = nullptr;
        return tree;
    }
    else if (val < tree->value) 
    {
		tree->left = add(tree->left, val); //если элемент больше чем value записываем с права
	}
	else
    {
		tree->right = add(tree->right, val); //если элемент меньше чем value записываем с слева
	}
	return tree;    
}
//---------------поиск----------------------------
//поиск ------------------------------------------
wood* findItem(wood* tree,int f)
{
    if (tree -> value == f)
    {
        return tree;
    }
    else
    {
        findItem(tree->right,f);
    }       
}
//поиск -----------------------------------------
//min and max -----------------------------------
wood **findMaxNode(wood** wood) {
	if (!(*wood)->right) return wood;
	else return findMaxNode(&(*wood)->right);
}

wood **findMinNode(wood** wood) {
	if (!(*wood)->left) return wood;
	else return findMinNode(&(*wood)->left);
}
//------------------удаления---------------------
//rm---------------------------------------------
wood *rm(wood* tree, int val) {
	if (!tree)
    {
         return nullptr; // if no parametr return 0
    }
	else if (val < tree -> value)
    {
		tree->left = rm(tree->left, val);
	}else if (val > tree->value) {
		tree->right = rm(tree->right, val);
	}
	else {
		if (!tree->left && !tree->right) {
			delete tree;
			return nullptr;
		}
		else if (tree->left) {
			wood **max_node = findMaxNode(&tree->left);
			tree->value = (*max_node)->value;
			*max_node = rm((*max_node), (*max_node)->value);
		}
		else {
			wood **min_node = findMinNode(&tree->right);
			tree->value = (*min_node)->value;
			*min_node = rm((*min_node), (*min_node)->value);
		}
	}
	return tree;
}
//rm---------------------------------------------
//-----------------------"печать"------------------
//print------------------------------------------

void printlist(wood *tree) {
	if (!tree)return;
	printlist(tree->left);
	printf("%d ", tree->value);
	printlist(tree->right);
}
//print------------------------------------------

int main()
{
        wood* tree = nullptr;
        tree = add(tree,23);
        tree = add(tree,2);
        tree = add(tree,10);
        tree = add(tree,40);
        tree = add(tree,32);
        tree = add(tree,15);
        tree = add(tree,1); //7
        //=================
        tree = rm(tree,23);
        printlist(tree);
}