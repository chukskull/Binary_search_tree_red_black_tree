#include <iostream>
#include <stdlib.h>
#define RED 1
#define BLCK 0
#define COUNT 10
using namespace std;
class Tree
{
    public:
        int     data_;
        Tree    *parent;
        Tree    *left;
        Tree    *right;
        int     color;
        // constructor to initialize data_ and pointers
        Tree(int data) : data_(data), parent(NULL), left(NULL), right(NULL) {}
};


void print2DUtil(Tree * root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
 
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    cerr << root->data_ << endl;
    // Process left child
    print2DUtil(root->left, space);
}


void print2D(Tree *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}
void    inorder_tree(Tree   *&head)
{
    if (head == NULL)
        return ;
    inorder_tree(head->left);
    cerr << head->data_ << " " << head->color << endl;
    inorder_tree(head->right);
    // delete head;
}

void    left_rotate(Tree *&head, Tree *x)
{
    Tree    *y = x->right;
;
    
    cerr <<" shiiiiiit " << x->data_ << endl;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        head = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
    
}

void    right_rotate(Tree   *&head, Tree *x)
{
    Tree    *y = x->left;

    cerr <<"right rotate "<< y->data_ << endl;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        head = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
    
}
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
    
Tree    *minimum(Tree   *head)
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
//case 1: if uncle is red we are just recoloring the parent and uncle as a black and grand parent as black and set elem to grand_parent because his red xD
void    RB_insert_Fixup(Tree *&head, Tree *new_elem)
{
    cerr <<"this is the element " <<new_elem->data_ <<  endl;
    while(new_elem->parent && new_elem->parent->color == RED)
    {
        // cerr <<" heerrr" <<new_elem->data_<< endl;
        if (new_elem->parent == new_elem->parent->parent->left)
        {
            Tree    *y = new_elem->parent->parent->right;
            if ( y && y->color == RED)
            {
                // cerr << "oop sucks " << endl;
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
            Tree    *y = new_elem->parent->parent->left;
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
                    cerr <<" AVALANCHE " <<new_elem_2->data_ << endl;
                    print2D(head);
                }
                new_elem->parent->color = BLCK;
                new_elem->parent->parent->color = RED;
                cerr << "ur lips soft like winter " <<new_elem->parent->parent->data_ << endl;
                left_rotate(head, new_elem->parent->parent);
            }
        }
    }
    // cerr << "here " << endl;
    head->color = BLCK;
}

void    insert(Tree *&head, Tree *new_ele)
{
    Tree    *y = NULL;
    Tree    *tmp = head;
    new_ele->left = NULL;
    new_ele->right = NULL;
    new_ele->parent = NULL;
    new_ele->color = RED;
    if (head == NULL)
    {
        new_ele->color = BLCK;
        head = new_ele;
       return ;
    }
    while (tmp != NULL)
    {
        y = tmp;
        if (new_ele->data_ < tmp->data_)
            tmp    = tmp->left;
        else
            tmp = tmp->right;
    }
    new_ele->parent = y;
    if (new_ele->data_ < y->data_)
        y->left = new_ele;
    else
        y->right = new_ele;
    cerr << "----" << endl;
    cerr << endl;
    cerr << endl;
    print2D(head);
    cerr << endl;
    inorder_tree(head);
    RB_insert_Fixup(head, new_ele);
}

Tree    *get_parent(Tree *head, int value)
{
    if (head == NULL)
        return NULL;
    if ((head->left != NULL && head->left->data_ == value) || (head->right != NULL && head->right->data_ == value))
        return head;
    if (value < head->data_)
        return get_parent(head->left, value);
    else
        return get_parent(head->right, value);
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
    Tree    *lol = new Tree(99);
    insert(head, lol);
    Tree    *lol2 = new Tree(55);
    insert(head, lol2);
    Tree    *lol3 = new Tree(11);
    insert(head, lol3);
    Tree *karafi = new Tree(21);
    insert(head, karafi);
    Tree *karafi2 = new Tree(25);
    insert(head, karafi2);
    Tree *karafi3 = new Tree(22);
    insert(head, karafi3);
    print2D(head);
    // print2D(head);
    // inorder_tree(head);
    delete_(head, new_elem);
    // print2D(head);

    return 0;
}