#include "heap.h"
#include <stdio.h>
#include <assert.h>

void printHeap(heap H);

int main(int argc, char * argv[])
{
    heap H;
    unsigned int size;
    int ret, option, data1, data2;

    printf(">> heap size: ");
    ret = scanf("%u", &size);
    assert(ret == 1);
    printf("\n");

    H = creatHeap(size);
    assert(H != NULL);

    printHeap(H);
    printf("\n");

    while (1)
    {
        printf(">> 0. insert\n");
        printf("   1. modify\n");
        printf("   2. delete\n");
        printf("   3. quit\n");
        printf(">> ");
        ret = scanf("%d", &option);
        assert(ret == 1);

        if (option == 3)
            break;

        if (option == 0)
        {
            printf(">> Data: ");
            ret = scanf("%d", &data1);
            assert(ret == 1);
        }
        else if (option == 1)
        {
            printf(">> Data: ");
            ret = scanf("%d", &data1);
            assert(ret == 1);
            printf("   Delta: ");
            ret = scanf("%d", &data2);
            assert(ret == 1);
        }

        switch (option)
        {
        case 0:
            ret = insertElement(H, data1);
            if (ret == -1)
                printf("   full heap\n");
            break;
        case 1:
            ret = modifyElement(H, data1, data2);
            if (ret == -1)
                printf("   no %d\n", data1);
            else
                printf("   modify %d to %d + %d\n", data1, data1, data2);
            break;
        case 2:
            ret = deleteElement(H);
            if (ret == INT_NULL)
                printf("   empty heap\n");
            else
                printf("   max is %d\n", ret);
            break;
        default:
            break;
        }

        printHeap(H);
        printf("\n");
    }

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
