#include "sort.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define STDLIB_HEAPSORT
#define STDLIB_MERGESORT
#define STDLIB_QSORT

static int _check(int array[], unsigned int size);

int compare(const void * a, const void * b)
{
    return *(int *)a - *(int *)b;
}

int main(int argc, char * argv[])
{
    clock_t start, end, sum;
    int * array;
    unsigned int size, looptime;
    int ret;

    printf(">> array size: ");
    ret = scanf("%u", &size);
    assert(ret == 1);
    printf("   loop time:  ");
    ret = scanf("%u", &looptime);
    assert(ret == 1);
    printf("\n");

    array = (int *)malloc(sizeof(int) * size);
    assert(array != NULL);

    srand((unsigned int)time(NULL));

    sum = 0;
    for (int loop = 0; loop < looptime; loop++)
    {
        for (int i = 0; i < size; i++)
            array[i] = ((rand() % 2) ? -1 : 1) * rand() % size;
        start = clock();
        SelectionSort(array, size);
        end = clock();
        ret = _check(array, size);
        assert(ret == 0);
        sum += (end - start);
    }
    printf("   selection sort: %lf\n", (double)sum / CLOCKS_PER_SEC / looptime);

    sum = 0;
    for (int loop = 0; loop < looptime; loop++)
    {
        for (int i = 0; i < size; i++)
            array[i] = ((rand() % 2) ? -1 : 1) * rand() % size;
        start = clock();
        BubbleSort(array, size);
        end = clock();
        ret = _check(array, size);
        assert(ret == 0);
        sum += (end - start);
    }
    printf("   bubble sort:    %lf\n", (double)sum / CLOCKS_PER_SEC / looptime);

    sum = 0;
    for (int loop = 0; loop < looptime; loop++)
    {
        for (int i = 0; i < size; i++)
            array[i] = ((rand() % 2) ? -1 : 1) * rand() % size;
        start = clock();
        InsertionSort(array, size);
        end = clock();
        ret = _check(array, size);
        assert(ret == 0);
        sum += (end - start);
    }
    printf("   insertion sort: %lf\n", (double)sum / CLOCKS_PER_SEC / looptime);

    sum = 0;
    for (int loop = 0; loop < looptime; loop++)
    {
        for (int i = 0; i < size; i++)
            array[i] = ((rand() % 2) ? -1 : 1) * rand() % size;
        start = clock();
        ShellSort(array, size);
        end = clock();
        ret = _check(array, size);
        assert(ret == 0);
        sum += (end - start);
    }
    printf("   shell sort:     %lf\n", (double)sum / CLOCKS_PER_SEC / looptime);

    sum = 0;
    for (int loop = 0; loop < looptime; loop++)
    {
        for (int i = 0; i < size; i++)
            array[i] = ((rand() % 2) ? -1 : 1) * rand() % size;
        start = clock();
        HeapSort(array, size);
        end = clock();
        ret = _check(array, size);
        assert(ret == 0);
        sum += (end - start);
    }
    printf("   heap sort:      %lf\n", (double)sum / CLOCKS_PER_SEC / looptime);

    sum = 0;
    for (int loop = 0; loop < looptime; loop++)
    {
        for (int i = 0; i < size; i++)
            array[i] = ((rand() % 2) ? -1 : 1) * rand() % size;
        start = clock();
        MergeSort(array, size);
        end = clock();
        ret = _check(array, size);
        assert(ret == 0);
        sum += (end - start);
    }
    printf("   merge sort:     %lf\n", (double)sum / CLOCKS_PER_SEC / looptime);

    sum = 0;
    for (int loop = 0; loop < looptime; loop++)
    {
        for (int i = 0; i < size; i++)
            array[i] = ((rand() % 2) ? -1 : 1) * rand() % size;
        start = clock();
        QuickSort(array, size);
        end = clock();
        ret = _check(array, size);
        assert(ret == 0);
        sum += (end - start);
    }
    printf("   quick sort:     %lf\n", (double)sum / CLOCKS_PER_SEC / looptime);

    sum = 0;
    for (int loop = 0; loop < looptime; loop++)
    {
        for (int i = 0; i < size; i++)
            array[i] = ((rand() % 2) ? -1 : 1) * rand() % size;
        start = clock();
        BucketSort(array, size);
        end = clock();
        ret = _check(array, size);
        assert(ret == 0);
        sum += (end - start);
    }
    printf("   bucket sort:    %lf\n", (double)sum / CLOCKS_PER_SEC / looptime);

    sum = 0;
    for (int loop = 0; loop < looptime; loop++)
    {
        for (int i = 0; i < size; i++)
            array[i] = ((rand() % 2) ? -1 : 1) * rand() % size;
        start = clock();
        RadixSort(array, size);
        end = clock();
        ret = _check(array, size);
        assert(ret == 0);
        sum += (end - start);
    }
    printf("   radix sort:     %lf\n", (double)sum / CLOCKS_PER_SEC / looptime);

#ifdef STDLIB_HEAPSORT
    sum = 0;
    for (int loop = 0; loop < looptime; loop++)
    {
        for (int i = 0; i < size; i++)
            array[i] = ((rand() % 2) ? -1 : 1) * rand() % size;
        start = clock();
        heapsort(array, size, sizeof(int), compare);
        end = clock();
        ret = _check(array, size);
        assert(ret == 0);
        sum += (end - start);
    }
    printf("   [heapsort]:     %lf\n", (double)sum / CLOCKS_PER_SEC / looptime);
#endif /* STDLIB_HEAPSORT */

#ifdef STDLIB_MERGESORT
    sum = 0;
    for (int loop = 0; loop < looptime; loop++)
    {
        for (int i = 0; i < size; i++)
            array[i] = ((rand() % 2) ? -1 : 1) * rand() % size;
        start = clock();
        mergesort(array, size, sizeof(int), compare);
        end = clock();
        ret = _check(array, size);
        assert(ret == 0);
        sum += (end - start);
    }
    printf("   [mergesort]:    %lf\n", (double)sum / CLOCKS_PER_SEC / looptime);
#endif /* STDLIB_MERGESORT */

#ifdef STDLIB_QSORT
    sum = 0;
    for (int loop = 0; loop < looptime; loop++)
    {
        for (int i = 0; i < size; i++)
            array[i] = ((rand() % 2) ? -1 : 1) * rand() % size;
        start = clock();
        qsort(array, size, sizeof(int), compare);
        end = clock();
        ret = _check(array, size);
        assert(ret == 0);
        sum += (end - start);
    }
    printf("   [qsort]:        %lf\n", (double)sum / CLOCKS_PER_SEC / looptime);
#endif /* STDLIB_QSORT */

    free(array);

    return 0;
}

static int _check(int array[], unsigned int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (array[i] > array[i + 1])
            return -1;
    }
    return 0;
}
