/**
 * implementation:
 * 0. binary max heap
 */

#include "heap.h"
#include <stdlib.h>

static void _moveup(heap H, int this)
{
    int X;
    int parent;

    X = H->data[this];
    for (; this > 0; this = parent)
    {
        parent = (this + 1) / 2 - 1;
        if (X > H->data[parent])
            H->data[this] = H->data[parent];
        else
            break;
    }
    H->data[this] = X;
}

static void _movedown(heap H, int this)
{
    int X;
    int child;

    X = H->data[this];
    for (; this * 2 + 1 < H->stock; this = child)
    {
        child = this * 2 + 1;
        if (child + 1 < H->stock && H->data[child + 1] > H->data[child])
            child ++;
        if (X < H->data[child])
            H->data[this] = H->data[child];
        else
            break;
    }
    H->data[this] = X;
}

heap creatHeap(unsigned int size)
{
    heap H;

    H = (heap)malloc(sizeof(struct heap_record));
    if (H != NULL)
    {
        H->size = size;
        H->stock = 0;
        H->data = (int *)malloc(sizeof(int) * size);
        if (H->data == NULL)
        {
            free(H);
            H = NULL;
        }
    }

    return H;
}

heap buildHeap(int * data, unsigned int size, unsigned int stock)
{
    heap H;

    H = (heap)malloc(sizeof(struct heap_record));
    if (H != NULL)
    {
        H->size = size;
        H->stock = stock;
        H->data = data;

        for (int i = H->stock / 2 - 1; i >= 0; i--)
            _movedown(H, i);
    }

    return H;
}

int insertElement(heap H, int X)
{
    int this;

    if (H->stock == H->size)
        return -1;

    this = H->stock;
    H->data[this] = X;
    (H->stock)++;

    _moveup(H, this);

    return 0;
}

int modifyElement(heap H, int X, int delta)
{
    int this;

    for (this = 0; this < H->stock; this++)
    {
        if (H->data[this] == X)
            break;
    }

    if (this >= H->stock)
        return -1;

    H->data[this] += delta;

    if (delta > 0)
        _moveup(H, this);
    else
        _movedown(H, this);

    return 0;
}

int deleteElement(heap H)
{
    int ret;

    if (H->stock == 0)
        return INT_NULL;

    ret = H->data[0];
    H->data[0] = H->data[H->stock - 1];
    (H->stock)--;

    if (H->stock > 1)
        _movedown(H, 0);

    return ret;
}

void destroyHeap(heap H)
{
    free(H->data);
    free(H);
}
