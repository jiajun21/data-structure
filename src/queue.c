/**
 * implementation:
 * 0. circular queue
 * 1. enqueue at rear/dequeue at front
 * 2. dequeue INT_NULL if empty
 */

#include "queue.h"
#include <stdlib.h>

queue createQueue(unsigned int size)
{
    queue Q;

    Q = (queue)malloc(sizeof(struct queue_record));
    if (Q != NULL)
    {
        Q->size = size;
        Q->stock = 0;
        Q->front = 0;
        Q->rear = -1;
        Q->data = (int *)malloc(sizeof(int) * Q->size);
        if (Q->data == NULL)
        {
            free(Q);
            Q = NULL;
        }
    }

    return Q;
}

int enqueue(queue Q, int X)
{
    if (Q->stock == Q->size)
        return -1;

    Q->rear = (Q->rear + 1) % Q->size;
    Q->data[Q->rear] = X;
    (Q->stock)++;

    return 0;
}

int dequeue(queue Q)
{
    int ret;

    if (Q->stock == 0)
        return INT_NULL;

    ret = Q->data[Q->front];
    Q->front = (Q->front + 1) % Q->size;
    (Q->stock)--;

    return ret;
}

void destroyQueue(queue Q)
{
    free(Q->data);
    free(Q);
}
