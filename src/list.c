/**
 * implementation:
 * 0. use dummy head
 * 1. node order is from small to large
 * 2. delete only the first match
 */

#include "list.h"
#include <stdlib.h>

list createList(void)
{
    list L;

    L = (list)malloc(sizeof(struct node));
    if (L != NULL)
    {
        L->data = -1;
        L->next = NULL;
    }

    return L;
}

int insertElement(list L, int X)
{
    nodeptr new, prev, this;

    new = (nodeptr)malloc(sizeof(struct node));
    if (new == NULL)
        return -1;
    new->data = X;
    new->next = NULL;

    prev = L;
    this = L->next;

    while (this != NULL)
    {
        if (this->data >= X)
            break;
        prev = this;
        this = this->next;
    }

    prev->next = new;
    new->next = this;

    return 0;
}

nodeptr findElement(list L, int X)
{
    nodeptr this;

    this = L->next;

    while (this != NULL)
    {
        if (this->data == X)
            break;
        this = this->next;
    }

    return this;
}

int deleteElement(list L, int X)
{
    nodeptr prev, this;
    int deletion;

    prev = L;
    this = L->next;
    deletion = 0;

    while (this != NULL)
    {
        if (this->data == X)
        {
            prev->next = this->next;
            free(this);
            deletion = 1;
            break;
        }
        prev = this;
        this = this->next;
    }

    if (deletion)
        return 0;
    else
        return -1;
}

void destroyList(list L)
{
    nodeptr this;

    this = L->next;

    while (this != NULL)
    {
        L->next = this->next;
        free(this);
        this = L->next;
    }
    free(L);
}
