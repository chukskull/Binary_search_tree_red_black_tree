#include <iostream>
#include <stdlib.h>
#define RED 1
#define BLCK 0
#define COUNT 10

using namespace std;
class Tree
{
public:
    int data_;
    Tree *parent;
    Tree *left;
    Tree *right;
    int color;
    Tree()
    {
        this->color = BLCK;
    }
    Tree(int data) : data_(data){};
};

Tree *nill = new Tree();

void print2DUtil(Tree *root, int space)
{
    if (root == nill)
        return;

    space += COUNT;
    print2DUtil(root->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    if (root->color == RED)
        cout << "\033[1;31m" << root->data_ << "\033[0m" << endl;
    else
        cerr << "\033[1;34m" << root->data_ << "\033[0m" << endl;
    print2DUtil(root->left, space);
}

void print2D(Tree *root)
{
    print2DUtil(root, 0);
}

void inorder_tree(Tree *&head)
{
    if (head == nill)
        return;
    inorder_tree(head->left);
    cerr << head->data_ << " " << head->color << endl;
    inorder_tree(head->right);
}

void left_rotate(Tree *&head, Tree *x)
{
    Tree *y = x->right;

    x->right = y->left;
    if (y->left != nill)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nill)
        head = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void right_rotate(Tree *&head, Tree *x)
{
    Tree *y = x->left;

    x->left = y->right;
    if (y->right != nill)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nill)
        head = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void transpant_algo(Tree *&head, Tree *u, Tree *v)
{
    if (u->parent == nill)
        head = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

Tree *minimum(Tree *head)
{
    Tree *current = head;

    while (current->left != nill)
    {
        current = current->left;
    }
    return current;
}

void RB_deletion_Fixup(Tree *&head, Tree *x)
{
    while (x != head && x->color == BLCK)
    {
        if (x == x->parent->left)
        {
            Tree *w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLCK;
                x->parent->color = RED;
                left_rotate(head, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLCK && w->right->color == BLCK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLCK)
                {

                    w->left->color = BLCK;
                    w->color = RED;
                    right_rotate(head, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLCK;
                w->right->color = BLCK;
                left_rotate(head, x->parent);
                x = head;
            }
        }
        else
        {
            Tree *w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLCK;
                x->parent->color = RED;
                right_rotate(head, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLCK && w->left->color == BLCK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLCK)
                {
                    w->right->color = BLCK;
                    w->color = RED;
                    left_rotate(head, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLCK;
                w->left->color = BLCK;
                right_rotate(head, x->parent);
                x = head;
            }
        }
    }
    x->color = BLCK;
}

Tree *search_node(Tree *&head, int key)
{
    Tree *curr = head;
    while (curr != nill && key != curr->data_)
    {
        if (key < curr->data_)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return curr;
}

Tree *maximum(Tree *&head)
{
    Tree *curr = head;
    while (curr->right != nill)
    {
        curr = curr->right;
    }
    return curr;
}

void node_delete(Tree *&head, int key)
{
    Tree *y;
    Tree *x;
    int color;

    Tree *z = search_node(head, key);
    y = z;
    color = y->color;
    if (z->left == nill)
    {
        x = z->right;
        transpant_algo(head, z, z->right);
    }
    else if (z->right == nill)
    {
        x = z->left;
        transpant_algo(head, z, z->left);
    }
    else
    {
        Tree *y = minimum(z->right);
        cerr << y->left->data_ << endl;
        color = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else
        {
            transpant_algo(head, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transpant_algo(head, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (color == BLCK)
    {
        print2D(head);
        RB_deletion_Fixup(head, x);
    }
    // delete z;
}
// case 1: if uncle is red we are just recoloring the parent and uncle as a BLCK and grand parent as black and set elem to grand_parent because his red xD
void RB_insert_Fixup(Tree *&head, Tree *new_elem)
{
    while (new_elem->parent->color == RED)
    {
        if (new_elem->parent == new_elem->parent->parent->left)
        {
            Tree *y = new_elem->parent->parent->right;
            if (y && y->color == RED)
            {
                new_elem->parent->color = BLCK;
                y->color = BLCK;
                new_elem->parent->parent->color = RED;
                new_elem = new_elem->parent->parent;
            }
            else
            {
                if (new_elem == new_elem->parent->right)
                {
                    new_elem = new_elem->parent;
                    left_rotate(head, new_elem);
                }
                new_elem->parent->color = BLCK;
                new_elem->parent->parent->color = RED;
                right_rotate(head, new_elem->parent->parent);
            }
        }
        else
        {
            Tree *y = new_elem->parent->parent->left;
            if (y && y->color == RED)
            {
                new_elem->parent->color = BLCK;
                y->color = BLCK;
                new_elem->parent->parent->color = RED;
                new_elem = new_elem->parent->parent;
            }
            else
            {
                if (new_elem == new_elem->parent->left)
                {
                    new_elem = new_elem->parent;
                    right_rotate(head, new_elem);
                    Tree *new_elem_2 = new_elem->parent;
                    print2D(head);
                }
                new_elem->parent->color = BLCK;
                new_elem->parent->parent->color = RED;
                left_rotate(head, new_elem->parent->parent);
            }
        }
    }
    head->color = BLCK;
}

void node_insert(Tree *&head, Tree *new_ele)
{
    Tree *y = nill;
    Tree *tmp = head;
    while (tmp != nill)
    {
        y = tmp;
        if (new_ele->data_ < tmp->data_)
        {
            tmp = tmp->left;
        }
        else
            tmp = tmp->right;
    }
    new_ele->parent = y;
    if (y == nill)
        head = new_ele;
    else if (new_ele->data_ < y->data_)
        y->left = new_ele;
    else
        y->right = new_ele;
    new_ele->left = nill;
    new_ele->right = nill;
    new_ele->color = RED;
    RB_insert_Fixup(head, new_ele);
}

Tree *get_parent(Tree *head, int value)
{
    if (head == nill)
        return nill;
    if ((head->left != nill && head->left->data_ == value) || (head->right != nill && head->right->data_ == value))
        return head;
    if (value < head->data_)
        return get_parent(head->left, value);
    else
        return get_parent(head->right, value);
}

int main()
{
    Tree *head;
    Tree *nill;
    head = nill;

    for (size_t i = 0; i < 12; i++)
    {
        node_insert(head, new Tree(i));
    }

    print2D(head);
    for (size_t i = 0; i < 12; i++)
    {
        node_delete(head, i);
    }

    return 0;
}