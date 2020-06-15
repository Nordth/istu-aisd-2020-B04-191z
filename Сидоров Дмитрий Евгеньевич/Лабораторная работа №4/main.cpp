#include <iostream>
using namespace std;

struct node {
    int key;
    int8_t height;
    node* left;
    node* right;

    node(int new_key) { key = new_key; left = right = 0; height = 1; }
};

int8_t max_ab(int8_t a, int8_t b) {
    return (a > b) ? a : b;
}

int8_t node_h(node* nd)
{
    if (nd==NULL) return 0;
    else return nd->height;
}


int8_t b_f(node* nd)
{
    return node_h(nd->left) - node_h(nd->right);
}

node* node_r_r(node* nd) {
    node* _left = nd->left;
    nd->left = _left->right;
    _left->right = nd;
    nd->height = max_ab(node_h(nd->left), node_h(nd->right))+1;
    _left->height = max_ab(node_h(_left->left), nd->height)+1;
    return _left;
}

node* node_l_r(node* nd) {
    node* _right = nd->right;
    nd->right = _right->left;
    _right->left = nd;
    nd->height= max_ab(node_h(nd->left), node_h(nd->right)) + 1;
    _right->height = max_ab(node_h(_right->right), nd->height) + 1;
    return _right;
}


node* balance(node* nd) {
	nd->height = max_ab(node_h(nd->right),node_h(nd->left))+1;
	if( b_f(nd)==-2 ) {
		if( b_f(nd->right) > 0 )
			nd->right = node_r_r(nd->right);
		return node_l_r(nd);
	}
	if( b_f(nd)==2 ) {
		if( b_f(nd->left) < 0  )
			nd->left = node_l_r(nd->left);
		return node_r_r(nd);
	}
	return nd;
}

node* add(node* nd, int new_key)
{
    if (nd == NULL) return new node(new_key);
    if (new_key < nd->key) nd->left = add(nd->left, new_key);
    else if (new_key > nd->key) nd->right = add(nd->right, new_key);
    return balance(nd);
}

node* max_node(node* nd) {
    if (!nd->right) return nd;
    return max_node(nd->right);
}

node* min_node ( node* nd) {
    if(!nd->left) return nd;
    return min_node (nd->left);
}


node* find_node(node* nd, int k) {
    if (!nd) return 0;
    if (k < nd->key) find_node(nd->left, k);
    else if (k > nd->key) find_node(nd->right, k);
    else return nd;
}


node* del_node(node* nd, int k) {
      int maxx;
      if (!nd) return 0;
      if (k < nd->key) nd->left=del_node(nd->left, k);
      else if (k > nd->key) nd->right=del_node(nd->right, k);
      else{
      node* _left = nd->left;
      node* _right = nd->right;
      delete nd;
      if (!_right and !_left) return NULL;
      else if (!_right) return _left;
      else if (!_left) return _right;
      else //if (node->left->height>node->right->height)
      {
      node* max_n = max_node(_left);
      //maxx=max_n->key;
      if (_left==max_n) {
            max_n->right=_right;
            return max_n;
            }
      else if (max_n->left!=0) {
            _left->right=max_n->left;
            max_n->left->left=_left ;
            max_n->right = _right;
            return max_n;
            }
      else {
            _left->right=max_n->left;
            max_n->left=_left;
            max_n->right=_right;
            return max_n;
            }
      }
    }
    return balance(nd);
}

void printTree(node * nd) {
    if (!nd) return;
    printTree(nd->left);
    cout << "   " << nd->key <<" ("<<int(nd->height)<<")    ";
    printTree(nd->right);
    cout<<endl;
}

node * mergeTree (node * nd1, node * nd2) {
     if (nd2==NULL) return nd1;
     mergeTree (nd1, nd2->left);
     nd1=add(nd1, nd2->key);
     mergeTree (nd1, nd2->right);

}


int main()
{
    node* head1 = NULL;
    node* head2 = NULL;
    int k;

    head1 = add(head1, 15);
    head1 = add(head1, 21);
    head1 = add(head1, 34);
    head1 = add(head1, 11);
    head1 = add(head1, 16);
    head1 = add(head1, 18);
    head1 = add(head1, 20);
    head1 = add(head1, 14);
    head1 = add(head1, 13);
    cout<<"Source AVL-Tree :"<<endl;
    printTree(head1);

    cout<<endl <<"Enter a key to del >>  ";
    cin >> k;
    head1=del_node(head1, k);
    cout<<"AVL-Tree after del :"<<endl;
    printTree(head1);

    head2 = add(head2, 33);
    head2 = add(head2, 3);
    head2 = add(head2, 43);
    head2 = add(head2, 23);
    head2 = add(head2, 7);
    head2 = add(head2, 27);
    cout<<"Additional AVL-Tree :"<<endl;
    printTree(head2);

    mergeTree(head1, head2);
    cout<<"United AVL-Tree :"<<endl;
    printTree(head1);
    return 0;
}
