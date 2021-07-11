#include "queue.h"
#include <stdio.h>
#include <assert.h>

void printQueue(queue Q);

int main(int argc, char * argv[])
{
    queue Q;
    unsigned int size;
    int ret, option, data;

    printf(">> queue size: ");
    ret = scanf("%u", &size);
    assert(ret == 1);
    printf("\n");

    Q = createQueue(size);
    assert(Q != NULL);

    printQueue(Q);
    printf("\n");

    while (1)
    {
        printf(">> 0. enqueue\n");
        printf("   1. dequeue\n");
        printf("   2. quit\n");
        printf(">> ");
        ret = scanf("%d", &option);
        assert(ret == 1);

        if (option == 2)
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
            ret = enqueue(Q, data);
            if (ret == -1)
                printf("   full queue\n");
            break;
        case 1:
            data = dequeue(Q);
            if (data == INT_NULL)
                printf("   empty queue\n");
            else
                printf("   dequeue %d\n", data);
            break;
        default:
            break;
        }

        printQueue(Q);
        printf("\n");
    }

    destroyQueue(Q);

    return 0;
}

void printQueue(queue Q)
{
    printf("[");
    if (Q->stock != 0)
    {
        for (int i = Q->front; i != Q->rear; i = (i + 1) % Q->size)
        {
            printf("%d - ", Q->data[i]);
        }
        printf("%d", Q->data[Q->rear]);
    }
    printf("]<-\n");
}
