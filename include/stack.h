#ifndef _STACK_H_
#define _STACK_H_

#define INT_NULL -1

typedef struct stack_record * stack;

struct stack_record
{
    unsigned int size;
    int top;
    int * data;
};

stack createStack(unsigned int size);
int push(stack S, int X);
int pop(stack S);
int top(stack S);
void destroyStack(stack S);

#endif
