#include <iostream>
#include <stdlib.h>

using namespace std;
class   Tree
{
    public:
       Tree(){
       };
        Tree(int data): data_(data), parent(NULL), left(NULL), right(NULL)
        {

        }
        Tree(int data, Tree *parent, Tree   *left, Tree *right)
        {

        }
        int     data_;
        Tree    *parent;
        Tree    *left;
        Tree    *right;


};

void    transpant_algo(Tree *&head, Tree    *u, Tree    *v)
{
    Tree    *p = u->parent;
    if (p == NULL)
        head = v;
    else if (p->left == u)
        p->left = v;
    else
        p->right = v;
    if (v != NULL)
    {
        v->parent = u->parent;
    }
}
    
Tree    *minimum(Tree   *&head)
{
    Tree    *current = head;

    while(current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

void    delete_(Tree    *&head,  Tree *z)
{
    if(z->left == NULL)
        transpant_algo(head, z, z->right);
    else if (z->right == NULL)
        transpant_algo(head, z, z->left);
    else{
        Tree    *y = minimum(z->right);
        if (y->parent != z)
        {
            transpant_algo(head, y, y->right);
            y->right = z->right;
            y->right->parent = y; 
        }
        transpant_algo(head, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

void    insert(Tree *&head, Tree *new_ele)
{
    Tree    *y = NULL;
    Tree    *tmp = head;
    while (tmp != NULL)
    {
        y = tmp;
        if (new_ele->data_ < tmp->data_)
            tmp    = tmp->left;
        else
            tmp = tmp->right;
    }
    new_ele->parent = y;
    if (y == NULL)
    {
       head = new_ele;
    }
    else if (new_ele->data_ < y->data_)
        y->left = new_ele;
    else
        y->right = new_ele;
}

Tree    *get_parent(Tree    *head ,int value)
{
    if (head == NULL)
        return NULL;
    if (head->left->data_ == value || head->right->data_ == value)
        return head;
    if (value < head->data_)
        return  get_parent(head->left, value);
    else 
        return get_parent(head->right, value);
}

void    inorder_tree(Tree   *head)
{
    if (head == NULL)
        return ;
    inorder_tree(head->left);
    cerr << head->data_ << endl;
    inorder_tree(head->right);
    delete head;
}

int main()
{
    Tree    *head;
    head = NULL;

    int     value = 18;
    Tree    *new_elem = new Tree(value);
    insert(head, new_elem);
    Tree    *ybncl = new Tree(69);
    insert(head, ybncl);
    Tree    *helmakh = new Tree(9);
    insert(head, helmakh);
    Tree    *snagat = new Tree(12);
    insert(head, snagat);
    delete_(head, snagat);

    inorder_tree(head);
}