#include "heap.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

void printHeap(heap H);

/* usage: ./test_heap_2 <size> */
int main(int argc, char * argv[])
{
    heap H;
    int * data;
    unsigned int size, stock;

    assert(argc == 2);
    size = atoi(argv[1]);

    data = (int *)malloc(sizeof(int) * size);
    assert(data != NULL);

    srand((unsigned int)time(NULL));

    stock = rand() % (size + 1);

    for (int i = 0; i < stock; i++)
        data[i] = rand() % 100;

    printf("heap size:  %d\n", size);
    printf("heap stock: %d\n\n", stock);

    printf("before build: \n");
    H = (heap)malloc(sizeof(struct heap_record));
    assert(H != NULL);
    H->size = size;
    H->stock = stock;
    H->data = data;
    printHeap(H);
    printf("\n");
    free(H);

    H = buildHeap(data, size, stock);
    printf("after build: \n");
    printHeap(H);
    printf("\n");

    destroyHeap(H);

    return 0;
}

static int _getItemWidth(int data)
{
    int ret;

    ret = 1;

    if (data < 0)
    {
        ret += 1;
        data = -1 * data;
    }

    while (data > 9)
    {
        data /= 10;
        ret += 1;
    }

    return ret;
}

static int _getMaxItemWidth(heap H)
{
    int ret, width;

    ret = 0;
    for (int i = 0; i < H->stock; i++)
    {
        width = _getItemWidth(H->data[i]);
        if (width > ret)
            ret = width;
    }

    return ret;
}

void printHeap(heap H)
{
    int depth, width;
    int start_space, inner_space;

    depth = 0;
    while ((1 << depth) - 1 < H->stock)
        depth ++;

    width = _getMaxItemWidth(H);

    for (int i = 1; i <= depth; i++)
    {
        start_space = ((1 << (depth - i)) * (width + 1) - 1) / 2 - width / 2;
        inner_space = (1 << (depth - i)) * (width + 1) - width;

        if (start_space != 0)
            printf("%*c", start_space, ' ');
        for (int j = (1 << (i - 1)) - 1; j < (1 << i) - 2; j++)
        {
            if (j >= H->stock)
                printf("%*c%*c", -1 * width, '#', inner_space, ' ');
            else
                printf("%*d%*c", -1 * width, H->data[j], inner_space, ' ');
        }
        if (((1 << i) - 2) >= H->stock)
            printf("%*c\n", -1 * width, '#');
        else
            printf("%*d\n", -1 * width, H->data[(1 << i) - 2]);
    }
}
