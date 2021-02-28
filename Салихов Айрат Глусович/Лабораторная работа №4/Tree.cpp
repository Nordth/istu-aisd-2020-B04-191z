#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    int key;
    int value;
    int height = 1;

    Node(int key, int value) {
        this->key = key;
        this->value = value;
    }
};


struct Tree {
    int size = 0;

    int height(Node* n) {
        if (n == nullptr) {
            return 0;
        }
        return n->height;
    }

    int maxHeight(Node* left, Node* right) {
        if (height(left) > height(right)) {
            return height(left);
        }
        return height(right);
    }

    void calcHeight(Node* root) {
        if (!root) return;
        root->height = maxHeight(root->left, root->right) + 1;
    }

    int getBalance(Node* root) {
        return height(root->left) - height(root->right);
    }

    Node* leftRotate(Node* n) {
            Node* right = n->right;
            n->right = right->left;
            right->left = n;
            calcHeight(n);
            calcHeight(right);
            return right;
    }

    Node* rightRotate(Node* n) {
        Node* left = n->left;
        n->left = left->right;
        left->right = n;
        calcHeight(n);
        calcHeight(left);
        return left;
    }

    /*
        Балансировка
        если у дерева вид такой /
        нужен правый поворот, так же происходит проверка что если вид
        такой < то нужно сначала его привексти левым поворотом левого поддерева к такому /
        чтобы получить такой /\
        если у дерева вид такой \
        то нужен левый повоорот, и проверка что если вид такой >
        то сначала приведем его к такому правым поворотом правого поддерева \
        а потом уже левый поворот и в итоге будет такой /\
        баланс - разница высот двух поддеревьев (левого минус правого)
        если баланс по модулю больше либо равен два значит дерево
        имеет вид один из: < > / \
        и ему нужна балансировка
    */
    Node* balance(Node* root) {
        if (root == nullptr) {
            return nullptr;
        }
        int balance = getBalance(root);
        if (balance < 2 && balance > -2) return root;
        if (balance >= 2) {
            if (getBalance(root->left) <= -1) {
                root->left = leftRotate(root->left);
            }
            return rightRotate(root);
        } else if (balance <=-2) {
            if (getBalance(root->right) >= 1) {
                root->right = rightRotate(root->right);
            }
            return leftRotate(root);
        }
        return root;
    }

    Node* min(Node* root) {
        if (!root) return nullptr;
        if (root->left == nullptr) {
            return root;
        }
        return min(root->left);
    }

    Node* max(Node* root) {
        if (!root) return nullptr;
        if (root->right == nullptr) {
            return root;
        }
        return max(root->right);
    }

    //добавляем ноду рекурсивно
    /*
        если переданная нода нулл то возвращаем новую ноду
        иначе если ключ меньше текущей - то для текущей левой ветви
        пытаемся вставить этот ключ (рекурсивно дойдем доконца)
        если больше - аналогично
    */
    Node* add(Node* root, int key, int value) {
        if (root == nullptr) {
            size++;
            return new Node(key, value);
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
        calcHeight(root);
        root = balance(root);
        return root;
    }

    //ищем ноду рекурсивно
    //возвращаем если ключ переданной ноды и переданный ключ совпадают
    //иначе если переданный меньше возвращаем результат поиска в левом дереве
    //ексли больше - в правом
    Node* find(Node* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }
        if (key < root->key) {
            return find(root->left, key);
        }
        if (key > root->key) {
            return find(root->right, key);
        }
        return root;
    }

    /*
        удаляем так же рекурсивно
        если ключ больше - меньше идем в нужное поддерево
        если нашли нужный ключ ищем минимальную ноду в его правом поддереве
        и максимальную в левом
        если обе нулл, то эта нода последняя
        иначе берем первую найденную
        для текущей устанвливаем ключ первой найденной и значение ее же
        и запускуаем удаление для нужного поддерева для этого нового ключа
        (в итоге он из самого низа переместится таким образом на место текущей ноды)
        а в самом низу такой ключ исчезнет
    */
    Node* remove(Node* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }
        if (key < root->key) {
            root->left = remove(root->left, key);
        }
        else if (key > root->key) {
            root->right = remove(root->right, key);
        }
        else if (key == root->key) {
            Node* minN = min(root->right);
            Node* maxN = max(root->left);
            Node* replace = nullptr;
            Node* toRemove = nullptr;
            if (minN) {
                toRemove = root->right;
                replace = minN;
                root->key = replace->key;
                root->value = replace->value;
                root->right = remove(toRemove, replace->key);
                calcHeight(root->right);
                root->right = balance(root->right);
            } else if (maxN) {
                toRemove = root->left;
                replace = maxN;
                root->key = replace->key;
                root->value = replace->value;
                root->left = remove(toRemove, replace->key);
                calcHeight(root->left);
                root->left = balance(root->left);
            } else {
                size--;
                return nullptr;
            }
        }
        calcHeight(root);
        root = balance(root);
        return root;
    }

    void print(Node* n) {
        print(n, 0);
    }

    void print(Node* n, int count) {
        if (!n) return;
        print(n->right, count+1);
        for (int i = 0; i < count; i++) {
            cout << "   ";
        }
        cout << "[" << n->key << " _ " << n->value << "]" << endl;
        print(n->left, count+1);
    }

    void keys(Node* n) {
        if (!n) return;
        keys(n->left);
        cout << n->key << " ";
        keys(n->right);
    }
};

int randomKey() {
    return rand()%20;
}

int main() {
    srand(time(0));
    cout << "Hello world" << endl;
    Tree tree;
    Node* root = nullptr;
    string s;
    int size = 15;

    for (int i = 0; i<size; i++) {
        root = tree.add(root, i, i);
    }
    tree.print(root);
    tree.keys(root);
    cout << endl << tree.size << endl;
    for (int i = 0; i<5; i++) {
        root = tree.remove(root, i);
    }
    tree.print(root);
    tree.keys(root);
    cout << endl << tree.size << endl;

    while (true) {
        cout << "1. add\n2. remove\n3. find\n4. print\n";
        cin >> s;
        if (s == "add") {
            cout << "Key:";
            int key = 0;
            int value = 0;
            cin >> key;
            cout << "value:";
            cin >> value;
            root = tree.add(root,key,value);
        } else if (s == "remove") {
            cout << "Key:";
            int key = 0;
            int value = 0;
            cin >> key;
            root = tree.remove(root,key);
        } else if (s == "find") {
            cout << "Key:";
            int key = 0;
            int value = 0;
            cin >> key;
            root = tree.add(root,key,value);
            Node* n = tree.find(root, key);
            cout << "Found:" << n;
            if (n) {
                cout << "Value: " << n->value << endl;
            }
        } else if (s == "print") {
            tree.print(root);
            tree.keys(root);
            cout << endl << tree.size << endl;
        } else {
            return 0;
        }
    }

    return 0;
}