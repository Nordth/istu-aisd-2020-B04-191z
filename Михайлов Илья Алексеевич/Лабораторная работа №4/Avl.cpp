#include<iostream>
using namespace std;

bool boo = false;


struct AVL_TREE
{
    int value;
    int key;
    AVL_TREE* left;
    AVL_TREE* right;
};

int Max(int, int);
int Height(AVL_TREE*);
int Diff(AVL_TREE*);
void Output(AVL_TREE*, int);
void Prin(AVL_TREE*, char, int, int);
void Delet_AVL_TREE(AVL_TREE*);
AVL_TREE* Balance(AVL_TREE*);
AVL_TREE* Right(AVL_TREE*);
AVL_TREE* Left(AVL_TREE*);
AVL_TREE* Left_right(AVL_TREE*);
AVL_TREE* Right_left(AVL_TREE*);
AVL_TREE* Add(AVL_TREE*, int, int );
AVL_TREE* Balan(AVL_TREE*);
AVL_TREE* Delet_znach(AVL_TREE* , int);

AVL_TREE* Balan(AVL_TREE* avl)
{
    if (!avl)
    {
        return avl;
    }
    else
    {
        avl -> left = Balan(avl -> left);
        avl = Balance(avl);
        avl -> right = Balan(avl -> right);
    }
    return avl;
}

void Output(AVL_TREE* avl, int key)
{
    if (!avl)
    {
        return;
    }
    else
    {
        if (avl -> key == key)
        {
            boo = true;
            cout << avl -> key << "[" << avl -> value << "]" << endl;
        }
        else
        {
            if (key < avl -> key)
            {
                Output(avl -> left, key);
            }
            else if (key >= avl -> key)
            {
                Output(avl -> right, key);
            }
        }
    }
}

int Max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int Height(AVL_TREE* avl)
{
    int x = 0;
    if (avl)
    {
        int left_H = Height (avl->left);
        int right_H = Height (avl->right);
        int Max_H = Max (left_H, right_H);
        x = Max_H + 1;
    }
    return x;
}
 
int Diff(AVL_TREE* avl)
{
    int left_H = Height (avl->left);
    int right_H = Height (avl->right);
    int y = left_H - right_H;
    return y;
}
 
AVL_TREE* Right(AVL_TREE* avl)
{
    AVL_TREE* temp;
    temp = avl->right;
    avl->right = temp->left;
    temp->left = avl;
    return temp;
}

AVL_TREE* Left(AVL_TREE* avl)
{
    AVL_TREE* temp;
    temp = avl->left;
    avl->left = temp->right;
    temp->right = avl;
    return temp;
}
 
AVL_TREE* Left_right(AVL_TREE* avl)
{
    AVL_TREE* temp;
    temp = avl->left;
    avl->left = Right(temp);
    return Left(avl);
}
 
AVL_TREE* Right_left(AVL_TREE* avl)
{
    AVL_TREE* temp;
    temp = avl->right;
    avl->right = Left(temp);
    return Right(avl);
}
 
AVL_TREE* Balance(AVL_TREE* avl)
{
    int bll = Diff(avl);
    if (bll > 1)
    {
        if (Diff (avl->left) > 0)
        {
            avl = Left(avl);
        }
        else
        {
            avl = Left_right(avl);
        }
    }
    else if (bll < -1)
    {
        if (Diff (avl->right) > 0)
        {
            avl = Right_left(avl);
        }
        else
        {
            avl = Right(avl);
        }    
    }
    return avl;
}
 
AVL_TREE* Add(AVL_TREE* avl, int value, int key)
{
    if (!avl)
    {
        avl = new AVL_TREE;
        avl->value = value;
        avl->key = key;
        avl->left = NULL;
        avl->right = NULL;
        return avl;
    }
    else if (key < avl->key)
    {
        avl->left = Add(avl->left, value, key);
        avl = Balance(avl);
    }
    else if (key >= avl->key)
    {
        avl->right = Add(avl->right, value, key);
        avl = Balance(avl);
    }
    return avl;
}
 
void Prin(AVL_TREE* avl, char simvol, int a)
{
    if (!avl)
    {
        return;
    }
    else
    {
        a += 5;
        Prin(avl -> right, '/', a);
        for (int i = 0; i < a; i++)
        {
            cout << " ";
        }
        cout << simvol << avl -> key << "[" << avl -> value << "]" << endl;
        Prin(avl -> left, '\\', a);
        a -= 5;
    }
}

AVL_TREE* Delet_znach(AVL_TREE* avl, int key)
{
    if(!avl)
    {
        return avl;
    }
    else
    {
        if(avl -> key == key)
        {
            boo = true;
            AVL_TREE* arr;
            if (avl -> right == NULL)
            {
                arr = avl -> left;
            }
            else
            {
                AVL_TREE* att;
                att = avl -> right;
                if(att -> left == NULL)
                {
                    att -> left = avl -> left;
                    arr = att;
                }
                else
                {
                    AVL_TREE* agg;
                    agg = att -> left;
                    while (agg -> left != NULL)
                    {
                        att = agg;
                        agg = att -> left;
                    }
                    att -> left = agg -> right;
                    agg -> left = avl -> left;
                    agg -> right = avl -> right;
                    arr = agg;
                }
            }
            delete avl;
            return arr;
        }
        else if (key < avl -> key)
        {
            avl->left = Delet_znach(avl -> left, key);
        }
        else if (key >= avl -> key)
        {
            avl->right = Delet_znach(avl -> right, key);
        }
        return avl;
    }
}

void Delet_AVL_TREE(AVL_TREE* avl)
{
   if (!avl)
    {
        return;
    }
    else
    {
        Delet_AVL_TREE(avl -> left);
        Delet_AVL_TREE(avl -> right);
        delete avl;
    }
}

int main()
{
    setlocale (LC_ALL, "rus");
    int value;
    int key;
    int a = 0;	
    int menu;
    AVL_TREE* avl = NULL;
    do
    {
        cout << "1.Добавить значение и ключ." << endl;
        cout << "2.Вывести дерево." << endl;
        cout << "3.Удалить ключ." << endl;
        cout << "4.Вывести значение по ключу." << endl;
        cout << "5.Выход." << endl;
        cin >> menu;
        switch (menu)
        {
            case 1:
                cout << "Введите значение: "; 
                cin >> value;
                cout << "Введите ключ: ";
                cin >> key;
                avl = Add(avl, value, key);
                break;
            case 2:
                cout << "-------------------- Дерево --------------------" << endl;
                Prin(avl, ' ', a);
                cout << "------------------------------------------------" << endl;
                break;
            case 3:
                cout << "Какой ключ удалить: ";
                cin >> key;
                avl = Delet_znach(avl,  key);
                avl = Balan(avl);
                if (boo == false)
                {
                    cout << "Значение с таким ключом не найдино!"<< endl;
                }
                boo = false;
                break;
            case 4:
                cout << "Какое значение по ключу вывести.";
                cin >> key;
                Output(avl, key);
                if (boo == false)
                {
                    cout << "Значение с таким ключом не найдино!"<< endl;
                }
                boo = false;
            case 5:
                Delet_AVL_TREE(avl);
                avl = NULL;
                break;
        }
    } while (menu != 5);
    return 0;
}


