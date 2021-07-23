#ifndef _TREE_H_
#define _TREE_H_

#define NO_RECURSIVE

typedef struct tree_record * tree;
typedef struct node * nodeptr;

struct tree_record
{
    nodeptr root;
};

struct node
{
    int data;
    nodeptr left;
    nodeptr right;
};

tree createTree(void);
int insertElement(tree T, int X);
nodeptr findElement(tree T, int X);
int deleteElement(tree T, int X);
void destroyTree(tree T);

#endif
