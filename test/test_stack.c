#include "stack.h"
#include <stdio.h>
#include <assert.h>

void printStack(stack S);

int main(int argc, char * argv[])
{
    stack S;
    unsigned int size;
    int ret, option, data;

    printf(">> stack size: ");
    ret = scanf("%u", &size);
    assert(ret == 1);
    printf("\n");

    S = createStack(size);
    assert(S != NULL);

    printStack(S);
    printf("\n");

    while (1)
    {
        printf(">> 0. push\n");
        printf("   1. pop\n");
        printf("   2. top\n");
        printf("   3. quit\n");
        printf(">> ");
        ret = scanf("%d", &option);
        assert(ret == 1);

        if (option == 3)
            break;

        if (option == 0)
        {
            printf(">> Data: ");
            ret = scanf("%d", &data);
            assert(ret == 1);
        }

        switch (option)
        {
        case 0:
            ret = push(S, data);
            if (ret == -1)
                printf("   full stack\n");
            break;
        case 1:
            data = pop(S);
            if (data == INT_NULL)
                printf("   empty stack\n");
            else
                printf("   pop %d\n", data);
            break;
        case 2:
            data = top(S);
            if (data == INT_NULL)
                printf("   empty stack\n");
            else
                printf("   top is %d\n", data);
            break;
        default:
            break;
        }

        printStack(S);
        printf("\n");
    }

    destroyStack(S);

    return 0;
}

void printStack(stack S)
{
    printf("null");
    for (int i = 0; i <= S->top; i++)
    {
        if (i == S->top)
            printf(" <= [%d]", S->data[S->top]);
        else
            printf(" <= %d", S->data[i]);
    }
    printf("\n");
}