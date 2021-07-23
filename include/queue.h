#ifndef _QUEUE_H_
#define _QUEUE_H_

#define INT_NULL -1

typedef struct queue_record * queue;

struct queue_record
{
    unsigned int size;
    unsigned int stock;
    int front;
    int rear;
    int * data;
};

queue createQueue(unsigned int size);
int enqueue(queue Q, int X);
int dequeue(queue Q);
void destroyQueue(queue Q);

#endif
