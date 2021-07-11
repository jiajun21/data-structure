/**
 * implementation:
 * 0. sort result is small to large
 */

#include "sort.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifdef DEBUG
#include <stdio.h>
static void _printArray(int array[], unsigned int size)
{
    for (int i = 0; i < size - 1; i++)
        printf("%d ", array[i]);
    printf("%d\n", array[size - 1]);
}
#endif /* DEBUG */

static void _movedown(int * array, unsigned int size, int this)
{
    int X;
    int child;

    X = array[this];
    for (; this * 2 + 1 < size; this = child)
    {
        child = this * 2 + 1;
        if (child + 1 < size && array[child + 1] > array[child])
            child ++;
        if (X < array[child])
            array[this] = array[child];
        else
            break;
    }
    array[this] = X;
}

static void _MergeSort(int array[], int new_array[], int left, int right)
{
    int mid, this, i, j;

    if (left < right)
    {
        mid = (left + right) / 2;

        _MergeSort(array, new_array, left, mid);
        _MergeSort(array, new_array, mid + 1, right);

        // for (this = left; this <= right; this++)
        //     new_array[this] = array[this];
        memcpy(new_array + left, array + left, (right - left + 1) * sizeof(int));

        for (this = left, i = left, j = mid + 1; i <= mid && j <= right; this++)
        {
            if (new_array[i] <= new_array[j])
                array[this] = new_array[i++];
            else
                array[this] = new_array[j++];
        }

        // for (; i <= mid; )
        //     array[this++] = new_array[i++];
        // for (; j <= right; )
        //     array[this++] = new_array[j++];
        memcpy(array + this, new_array + i, (mid - i + 1) * sizeof(int));
        memcpy(array + this, new_array + j, (right - j + 1) * sizeof(int));
    }
}

/**
 * pivoit candidates: left, mid, right
 * 0. sort candidates
 * 1. pivot is real mid
 * 2. move pivot to right - 1
 */
static int _preparePivot(int array[], unsigned int size)
{
    int left, mid, right;
    int pivot, tmp;

    left = 0;
    mid = (size - 1) / 2;
    right = size - 1;

    if (array[mid] < array[left])
    {
        tmp = array[mid];
        array[mid] = array[left];
        array[left] = tmp;
    }
    if (array[right] < array[mid])
    {
        tmp = array[right];
        array[right] = array[mid];
        if (tmp < array[left])
        {
            array[mid] = array[left];
            array[left] = tmp;
        }
        else
            array[mid] = tmp;
    }

    pivot = array[mid];
    array[mid] = array[right - 1];
    array[right - 1] = pivot;

    return pivot;
}

static void _QuickSort(int array[], unsigned int size)
{
    int left, right;
    int pivot, tmp;

    if (size <= QUICKSORT_THRESHOLD)
        InsertionSort(array, size);
    else
    {
        pivot = _preparePivot(array, size);

        left = 0;
        right = size - 2;

        while (1)
        {
            while (array[++left] < pivot);
            while (array[--right] > pivot);

            if (left >= right) break;

            tmp = array[left];
            array[left] = array[right];
            array[right] = tmp;
        }

        array[size - 2] = array[left];
        array[left] = pivot;

        QuickSort(array, left);
        QuickSort(array + left + 1, size - left - 1);
    }
}

#define _getBucketIndex(value, min, max, bucket_num) \
    (int)floor((double)((value) - (min)) / ((max) - (min) + 1) * (bucket_num))

int SelectionSort(int array[], unsigned int size)
{
    int min_index;
    int tmp;

    if (size == 0)
        return -1;
    if (size == 1)
        return 0;

    for (int i = 0; i < size - 1; i++)
    {
        min_index = i;
        for (int j = i + 1; j < size; j++)
        {
            if (array[j] < array[min_index])
                min_index = j;
        }
        if (min_index != i)
        {
            tmp = array[min_index];
            array[min_index] = array[i];
            array[i] = tmp;
        }
#ifdef DEBUG
        _printArray(array, size);
#endif /* DEBUG */
    }

    return 0;
}

int BubbleSort(int array[], unsigned int size)
{
    int min;

    if (size == 0)
        return -1;
    if (size == 1)
        return 0;

    for (int i = 0; i < size - 1; i++)
    {
        min = array[size - 1];
        for (int j = size - 2; j >= i; j--)
        {
            if (array[j] > min)
                array[j + 1] = array[j];
            else
            {
                array[j + 1] = min;
                min = array[j];
            }
        }
        array[i] = min;
#ifdef DEBUG
        _printArray(array, size);
#endif /* DEBUG */
    }

    return 0;
}

int InsertionSort(int array[], unsigned int size)
{
    int index;
    int tmp;

    if (size == 0)
        return -1;
    if (size == 1)
        return 0;

    for (int i = 1; i < size; i++)
    {
        tmp = array[i];
        for (index = i - 1; index >= 0; index--)
        {
            if (array[index] > tmp)
                array[index + 1] = array[index];
            else
                break;
        }
        array[index + 1] = tmp;
#ifdef DEBUG
        printf("        insertion_sort: ");
        _printArray(array, size);
#endif /* DEBUG */
    }

    return 0;
}

int ShellSort(int array[], unsigned int size)
{
    unsigned int increment;
    int index;
    int tmp;

    if (size == 0)
        return -1;
    if (size == 1)
        return 0;

    for (increment = size / 2; increment > 0; increment /= 2)
    {
        for (int i = increment; i < size; i++)
        {
            tmp = array[i];
            for (index = i - increment; index >= 0; index -= increment)
            {
                if (array[index] > tmp)
                    array[index + increment] = array[index];
                else
                    break;
            }
            array[index + increment] = tmp;
        }
#ifdef DEBUG
        printf("increment: %u\n", increment);
        _printArray(array, size);
#endif /* DEBUG */
    }

    return 0;
}

int HeapSort(int array[], unsigned int size)
{
    unsigned int heap_size;
    int tmp;

    if (size == 0)
        return -1;
    if (size == 1)
        return 0;

    heap_size = size;
    for (int i = heap_size / 2 - 1; i >= 0; i--)
        _movedown(array, heap_size, i);

    while (heap_size > 1)
    {
        tmp = array[0];
        array[0] = array[heap_size - 1];
        array[heap_size - 1] = tmp;
        heap_size --;
        _movedown(array, heap_size, 0);
#ifdef DEBUG
        _printArray(array, size);
#endif /* DEBUG */
    }

    return 0;
}

int MergeSort(int array[], unsigned int size)
{
    int * new_array;

    if (size == 0)
        return -1;
    if (size == 1)
        return 0;

    new_array = (int *)malloc(sizeof(int) * size);

    if (new_array == NULL)
        return -1;

    _MergeSort(array, new_array, 0, size - 1);

    free(new_array);
#ifdef DEBUG
    _printArray(array, size);
#endif /* DEBUG */

    return 0;
}

int QuickSort(int array[], unsigned int size)
{
    if (size == 0)
        return -1;
    if (size == 1)
        return 0;

    _QuickSort(array, size);
#ifdef DEBUG
    printf("    quick_sort: ");
    _printArray(array, size);
#endif /* DEBUG */

    return 0;
}

int BucketSort(int array[], unsigned int size)
{
    int * new_array;
    int * bucket_volume;
    int bucket_num;
    int bucket_index;
    int min, max;

    if (size == 0)
        return -1;
    if (size == 1)
        return 0;

    new_array = (int *)malloc(sizeof(int) * size);
    if (new_array == NULL)
        return -1;

    bucket_num = (int)ceil(size * BUCKETSORT_RATIO);
    bucket_volume = (int *)malloc(sizeof(int) * bucket_num);
    if (bucket_volume == NULL)
    {
        free(new_array);
        return -1;
    }
    for (int i = 0; i < bucket_num; i++)
        bucket_volume[i] = 0;

    min = max = array[0];
    for (int i = 1; i < size; i++)
    {
        if (array[i] < min)
            min = array[i];
        else if (array[i] > max)
            max = array[i];
    }

    for (int i = 0; i < size; i++)
    {
        bucket_index = _getBucketIndex(array[i], min, max, bucket_num);
        bucket_volume[bucket_index]++;
    }

    for (int i = 1; i < bucket_num; i++)
        bucket_volume[i] += bucket_volume[i - 1];

    for (int i = 0; i < size; i++)
    {
        bucket_index = _getBucketIndex(array[i], min, max, bucket_num);
        new_array[--bucket_volume[bucket_index]] = array[i];
    }

#ifdef DEBUG
    _printArray(new_array, size);
#endif /* DEBUG */
    for (int i = 0; i < bucket_num - 1; i++)
        QuickSort(new_array + bucket_volume[i], bucket_volume[i + 1] - bucket_volume[i]);
    QuickSort(new_array + bucket_volume[bucket_num - 1], size - bucket_volume[bucket_num - 1]);

    for (int i = 0; i < size; i++)
        array[i] = new_array[i];

    free(bucket_volume);
    free(new_array);
#ifdef DEBUG
    _printArray(array, size);
#endif /* DEBUG */

    return 0;
}

int RadixSort(int array[], unsigned int size)
{
    int * new_array;
    int bucket[10];
    int min, max;
    int max_digit;
    int radix;

    new_array = (int *)malloc(sizeof(int) * size);
    if (new_array == NULL)
        return -1;

    min = max = array[0];
    for (int i = 1; i < size; i++)
    {
        if (array[i] < min)
            min = array[i];
        else if (array[i] > max)
            max = array[i];
    }

    for (int i = 0; i < size; i++)
        array[i] -= min;
    max -= min;

    for (max_digit = 1; max > 9; max_digit++)
        max /= 10;

    radix = 1;
    for (int i = 0; i < max_digit; i++)
    {
        for (int j = 0; j < 10; j++)
            bucket[j] = 0;

        for (int j = 0; j < size; j++)
            bucket[array[j] / radix % 10]++;

        for (int j = 1; j < 10; j++)
            bucket[j] += bucket[j - 1];

        /* reverse order is necessary */
        for (int j = size - 1; j >= 0; j--)
            new_array[--bucket[array[j] / radix % 10]] = array[j];

        for (int j = 0; j < size; j++)
            array[j] = new_array[j];

        radix *= 10;
#ifdef DEBUG
        _printArray(array, size);
#endif /* DEBUG */
    }

    for (int i = 0; i < size; i++)
        array[i] += min;
#ifdef DEBUG
        _printArray(array, size);
#endif /* DEBUG */

    free(new_array);

    return 0;
}
