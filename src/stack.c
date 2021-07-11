/**
 * implementation:
 * 0. stack array grows from small index to large
 * 1. pop/top INT_NULL if empty
 */

#include "stack.h"
#include <stdlib.h>

stack createStack(unsigned int size)
{
    stack S;

    S = (stack)malloc(sizeof(struct stack_record));
    if (S != NULL)
    {
        S->size = size;
        S->top = -1;
        S->data = (int *)malloc(sizeof(int) * S->size);
        if (S->data == NULL)
        {
            free(S);
            S = NULL;
        }
    }

    return S;
}

int push(stack S, int X)
{
    if (S->top == S->size - 1)
        return -1;

    (S->top)++;
    S->data[S->top] = X;

    return 0;
}

int pop(stack S)
{
    int ret;

    if (S->top == -1)
        return INT_NULL;

    ret = S->data[S->top];
    (S->top)--;

    return ret;
}

int top(stack S)
{
    if (S->top == -1)
        return INT_NULL;

    return S->data[S->top];
}

void destroyStack(stack S)
{
    free(S->data);
    free(S);
}
