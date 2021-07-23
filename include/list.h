#ifndef _LIST_H_
#define _LIST_H_

typedef struct node * nodeptr;
typedef struct node * list;

struct node
{
    int data;
    nodeptr next;
};

list createList(void);
int insertElement(list L, int X);
nodeptr findElement(list L, int X);
int deleteElement(list L, int X);
void destroyList(list L);

#endif
