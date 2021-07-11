#include "sort.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

void printArray(int array[], unsigned int size);

int main(int argc, char * argv[])
{
    int * array;
    unsigned int size;
    int ret, option;

    printf(">> array size: ");
    ret = scanf("%u", &size);
    assert(ret == 1);
    printf("\n");

    array = (int *)malloc(sizeof(int) * size);
    assert(array != NULL);

    srand((unsigned int)time(NULL));

    while (1)
    {
        for (int i = 0; i < size; i++)
            array[i] = rand() % 1000;

        printf(">> 0. seletion\n");
        printf("   1. bubble\n");
        printf("   2. insertion\n");
        printf("   3. shell\n");
        printf("   4. heap\n");
        printf("   5. merge\n");
        printf("   6. quick\n");
        printf("   7. bucket\n");
        printf("   8. radix\n");
        printf("   9. quit\n");
        printf(">> ");
        ret = scanf("%d", &option);
        assert(ret == 1);

        if (option == 9)
            break;

        printArray(array, size);
        printf("\n");

        switch (option)
        {
        case 0:
            SelectionSort(array, size);
            break;
        case 1:
            BubbleSort(array, size);
            break;
        case 2:
            InsertionSort(array, size);
            break;
        case 3:
            ShellSort(array, size);
            break;
        case 4:
            HeapSort(array, size);
            break;
        case 5:
            MergeSort(array, size);
            break;
        case 6:
            QuickSort(array, size);
            break;
        case 7:
            BucketSort(array, size);
            break;
        case 8:
            RadixSort(array, size);
            break;
        default:
            break;
        }

        printf("\n");
    }

    free(array);

    return 0;
}

void printArray(int array[], unsigned int size)
{
    for (int i = 0; i < size - 1; i++)
        printf("%d ", array[i]);
    printf("%d\n", array[size - 1]);
}
