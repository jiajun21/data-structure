/**
 * implementation:
 * 0. binary search tree
 * 1. use dummy head
 */

#include "tree.h"
#include <stdlib.h>

#ifdef NO_RECURSIVE
/* nothing */
#else
static nodeptr _insertElement(nodeptr root, int X, int * pflag)
{
    nodeptr new;

    if (root == NULL)
    {
        new = (nodeptr)malloc(sizeof(struct node));
        if (new == NULL)
            *pflag = -1;
        else
        {
            *pflag = 0;
            new->data = X;
            new->left = NULL;
            new->right = NULL;
        }

        return new;
    }

    if (X < root->data)
        root->left = _insertElement(root->left, X, pflag);
    else
        root->right = _insertElement(root->right, X, pflag);

    return root;
}

static nodeptr _findElement(nodeptr root, int X)
{
    nodeptr ret;

    if (root == NULL)
        return NULL;

    if (X == root->data)
        ret = root;
    else if (X < root->data)
        ret = _findElement(root->left, X);
    else
        ret = _findElement(root->right, X);

    return ret;
}

static nodeptr _deleteElement(nodeptr root, int X, int * pflag)
{
    nodeptr ret, this;

    if (root == NULL)
    {
        *pflag = -1;
        return NULL;
    }

    if (X == root->data)
    {
        *pflag = 0;
        if (root->left && root->right)
        {
            this = root->right;

            while (this->left != NULL)
                this = this->left;

            root->data = this->data;
            root->right = _deleteElement(root->right, this->data, pflag);
            ret = root;
        }
        else
        {
            if (!(root->left) && root->right)
                ret = root->right;
            else if (root->left && !(root->right))
                ret = root->left;
            else
                ret = NULL;
            free(root);
        }

        return ret;
    }
    else if (X < root->data)
        root->left = _deleteElement(root->left, X, pflag);
    else
        root->right = _deleteElement(root->right, X, pflag);

    return root;
}
#endif /* NO_RECURSIVE */

static void _destroyTree(nodeptr root)
{
    if (root != NULL)
    {
        _destroyTree(root->left);
        _destroyTree(root->right);
        free(root);
    }
}

tree createTree(void)
{
    tree T;

    T = (tree)malloc(sizeof(struct tree_record));
    if (T != NULL)
        T->root = NULL;

    return T;
}

#ifdef NO_RECURSIVE
int insertElement(tree T, int X)
{
    nodeptr new, prev, this;

    new = (nodeptr)malloc(sizeof(struct node));
    if (new == NULL)
        return -1;
    new->data = X;
    new->left = NULL;
    new->right = NULL;

    prev = NULL;
    this = T->root;

    while (this != NULL)
    {
        prev = this;
        if (X < this->data)
            this = this->left;
        else
            this = this->right;
    }

    if (prev == NULL)
        T->root = new;
    else
    {
        if (X < prev->data)
            prev->left = new;
        else
            prev->right = new;
    }

    return 0;
}

nodeptr findElement(tree T, int X)
{
    nodeptr this;

    this = T->root;
    while (this != NULL)
    {
        if (X == this->data)
            break;
        else if (X < this->data)
            this = this->left;
        else
            this = this->right;
    }

    return this;
}

int deleteElement(tree T, int X)
{
    nodeptr prev, this, mark;

    /* first find element X */
    prev = NULL;
    this = T->root;

    while (this != NULL)
    {
        if (X == this->data)
            break;
        else
        {
            prev = this;
            if (X < this->data)
                this = this->left;
            else
                this = this->right;
        }
    }

    if (this == NULL)
        return -1;

    /* then delete node X */
    if (this->left && this->right)
    {
        mark = this;
        prev = this;
        this = this->right;

        while (this->left != NULL)
        {
            prev = this;
            this = this->left;
        }

        mark->data = this->data;
        if (this == prev->left)
            prev->left = this->right;
        else
            prev->right = this->right;
    }
    else if (!(this->left) && this->right)
    {
        if (prev == NULL)
            T->root = this->right;
        else if (this == prev->left)
            prev->left = this->right;
        else
            prev->right = this->right;
    }
    else if (this->left && !(this->right))
    {
        if (prev == NULL)
            T->root = this->left;
        else if (this == prev->left)
            prev->left = this->left;
        else
            prev->right = this->left;
    }
    else
    {
        if (prev == NULL)
            T->root = NULL;
        else if (this == prev->left)
            prev->left = NULL;
        else
            prev->right = NULL;
    }

    free(this);

    return 0;
}
#else
int insertElement(tree T, int X)
{
    int flag;

    T->root = _insertElement(T->root, X, &flag);

    return flag;
}

nodeptr findElement(tree T, int X)
{
    nodeptr ret;

    ret = _findElement(T->root, X);

    return ret;
}

int deleteElement(tree T, int X)
{
    int flag;

    T->root = _deleteElement(T->root, X, &flag);

    return flag;
}
#endif /* NO_RECURSIVE */

void destroyTree(tree T)
{
    _destroyTree(T->root);
    free(T);
}
