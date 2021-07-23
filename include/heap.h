#ifndef _HEAP_H_
#define _HEAP_H_

#define INT_NULL -1

typedef struct heap_record * heap;

struct heap_record
{
    unsigned int size;
    unsigned int stock;
    int * data;
};

heap creatHeap(unsigned int size);
heap buildHeap(int * data, unsigned int size, unsigned int stock);
int insertElement(heap H, int X);
int modifyElement(heap H, int X, int delta);
int deleteElement(heap H);
void destroyHeap(heap H);

#endif