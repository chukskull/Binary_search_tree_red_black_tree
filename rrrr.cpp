void RB_insert_Fixup(Tree*& root, Tree* x) {
    while (x->parent && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            Tree* y = x->parent->parent->right;
            if (y->color == RED) {
                x->parent->color = NIG;
                y->color = NIG;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) {
                    x = x->parent;
                    left_rotate(root, x);
                }
                x->parent->color = NIG;
                x->parent->parent->color = RED;
                right_rotate(root, x->parent->parent);
            }
        } else {
            Tree* y = x->parent->parent->left;
            if (y->color == RED) {
                x->parent->color = NIG;
                y->color = NIG;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    right_rotate(root, x);
                }
                x->parent->color = NIG;
                x->parent->parent->color = RED;
                left_rotate(root, x->parent->parent);
            }
        }
    }
    root->color = NIG;
}


void insert(Tree*& root, Tree *newTree) {
    newTree->color = RED;
    newTree->left = newTree->right = newTree->parent = NULL;
    if (root == NULL) {
        newTree->color = NIG;
        root = newTree;
        return;
    }
    Tree* current = root;
    Tree* parent = NULL;
    while (current != NULL) {
        parent = current;
        if (newTree->data_ < current->data_)
            current = current->left;
        else
            current = current->right;
    }
    newTree->parent = parent;
    if (newTree->data_ < parent->data_)
        parent->left = newTree;
    else
        parent->right = newTree;
    RB_insert_Fixup(root, newTree);
}


void    RB_insert_Fixup(Tree *&head, Tree *new_elem)
{
    while(new_elem->parent && new_elem->parent->color == RED)
    {
        // cerr <<" heerrr" <<new_elem->data_<< endl;
        if (new_elem->parent == new_elem->parent->parent->left)
        {
            Tree    *y = new_elem->parent->parent->right;
            if (y->color == RED)
            {
                cerr << "oop sucks " << endl;
                new_elem->parent->color = NIG;
                y->color = NIG;
                new_elem->parent->parent->color = RED;
                new_elem = new_elem->parent->parent;
            }
            else if (new_elem == new_elem->parent->right)
            {
                new_elem = new_elem->parent;
                left_rotate(head, new_elem);
            }
            cerr << new_elem->parent << endl;
            new_elem->parent->color = NIG;
            new_elem->parent->parent->color = RED;
            right_rotate(head, new_elem->parent->parent);
        }
        else
        {
            Tree    *y = new_elem->parent->parent->left;
            if (y->color == RED)
            {
                new_elem->parent->color = NIG;
                y->color = NIG;
                new_elem->parent->parent->color = RED;
                new_elem = new_elem->parent->parent;
            }
            else if (new_elem == new_elem->parent->left)
            {
                new_elem = new_elem->parent;
                right_rotate(head, new_elem);
            }
            new_elem->parent->color = NIG;
            new_elem->parent->parent->color = RED;
            left_rotate(head, new_elem->parent->parent);
        }
    }
    // cerr << "here " << endl;
    head->color = NIG;
}